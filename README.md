# TinyEngine::SparseSet
A small, modern C++26 implementation of a **Sparse Set** container.

The project is part of [TinyEngine](https://github.com/conpdepablo/TinyEngine) and is intended primarily for use in entity-component systems (ECS), where entities are represented by integer IDs and components need fast insertion, removal, lookup, and iteration.

## Features

* C++26 module
* O(1) average `Contains`
* O(1) `Get`
* O(1) `Remove`
* O(1) amortized `Insert`
* Dense, cache-friendly storage
* Constant-time removal using swap-and-pop
* Dynamic growth of the sparse array
* `const`-correct access
* Range-based iteration
* No external runtime dependencies
* Lightweight API

## How it works

The Sparse Set uses three arrays:

```text
sparse
    ID → dense index

denseId
    dense index → ID

dense
    dense index → value
```

For example, after:

```cpp
SparseSet<int> set{5};

set.Insert(2, 42);
set.Insert(4, 100);
set.Insert(1, 200);
```

the internal representation is conceptually:

```text
sparse

ID:      0   1   2   3   4
         ↓   ↓   ↓   ↓   ↓
index:   -   2   0   -   1


denseId

index:   0   1   2
         ↓   ↓   ↓
ID:      2   4   1


dense

index:   0   1   2
         ↓   ↓   ↓
value:  42 100 200
```

This allows an ID to be mapped to its dense storage location in constant time.

## Removal

Elements are removed using **swap-and-pop**.

Given:

```text
denseId: [2, 4, 1]
dense:   [42, 100, 200]
```

removing ID `4` moves the last element into its position:

```text
denseId: [2, 1]
dense:   [42, 200]
```

This makes removal O(1), but **iteration order is not stable after removal**.

## API

### Construction

```cpp
TinyEngine::SparseSet<int> set{100};
```

The constructor argument defines the initial ID range covered by the sparse array.

The sparse array grows automatically when an ID outside the current range is inserted.

### Insert

```cpp
set.Insert(42, 123);
```

Values are inserted using perfect forwarding:

```cpp
set.Insert(42, MyComponent{});
```

### Contains

```cpp
if (set.Contains(42)) {
    // ...
}
```

Returns `false` for IDs outside the current sparse range.

### Get

```cpp
auto& component = set.Get(42);
```

`Get()` preserves const-correctness:

```cpp
SparseSet<MyComponent> const& set = ...;

auto const& component = set.Get(42);
```

### Remove

```cpp
set.Remove(42);
```

Removal is O(1), but does not preserve iteration order.

### Size

Returns the number of elements currently stored:

```cpp
set.Size();
```

### Capacity

Returns the current size of the sparse ID array:

```cpp
set.Capacity();
```

This is **not** the number of elements the container can store.

For example:

```cpp
SparseSet<int> set{5};

set.Capacity(); // 5

set.Insert(10, 42);

set.Capacity(); // 11
```

### Empty

```cpp
if (set.Empty()) {
    // ...
}
```

### Clear

```cpp
set.Clear();
```

Removes all elements while retaining the sparse array.

### Iteration

The container supports range-based iteration:

```cpp
for (auto const& value : set) {
    // ...
}
```

Iteration follows the current dense storage order.

## Complexity

| Operation  |     Complexity |
| ---------- | -------------: |
| `Insert`   | O(1) amortized |
| `Remove`   |           O(1) |
| `Contains` |           O(1) |
| `Get`      |           O(1) |
| `Size`     |           O(1) |
| `Capacity` |           O(1) |
| `Empty`    |           O(1) |
| `Clear`    |           O(n) |
| Iteration  |           O(n) |

`Insert` can require resizing the sparse array when inserting an ID outside its current range.

## Requirements

* C++26 compiler with module support
* CMake
* Ninja recommended

The project is developed and tested primarily with modern Clang/GCC toolchains.

## Building

Configure the project with CMake using one of the available presets:

### GCC

* `g++-debug` — GCC Debug
* `g++-release` — GCC Release

### Clang

* `clang-debug` — Clang Debug
* `clang-release` — Clang Release

### Windows

Windows builds are also supported.

For example, using the `clang-release` preset:

```bash
cmake .. --preset clang-release
cd build/clang-release
cmake --build . -j
```

You can replace `clang-release` with any of the available presets.

## Tests

The project uses CTest with a lightweight test executable and does not require a testing framework.

Run all tests with:

```bash
ctest --test-dir build --output-on-failure
```

## Design Goals

The implementation intentionally keeps the API small.

The main goals are:

1. Fast ID-based lookup.
2. Dense storage for efficient iteration.
3. Constant-time removal.
4. Minimal overhead.
5. Modern C++ design.
6. A simple implementation suitable for ECS-style workloads.

The implementation favors predictable data-oriented behavior over preserving insertion order.

## License

See the repository license for details.
