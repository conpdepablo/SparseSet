module;

#include <contracts> // pre
#include <utility>   // std::forward
#include <vector>    // std::vector

export module TinyEngine.SparseSet;

export namespace TinyEngine
{
template <typename T>
struct [[nodiscard]] SparseSet
{
  // Ctor
  explicit constexpr SparseSet(std::size_t const capacity)
      : sparse_(capacity)
  {
  }

  // Contains
  [[nodiscard]]
  constexpr auto Contains(std::size_t const id) const noexcept -> bool
  {
    if (id >= sparse_.size())
    {
      return false;
    }

    auto const index = sparse_[id];
    return index < denseId_.size() && denseId_[index] == id;
  }

  // Insert
  template <typename U>
  void Insert(std::size_t const id, U&& value)
  // pre(!Contains(id))
  {
    if (id >= sparse_.size())
    {
      sparse_.resize(id + 1);
    }

    auto const index = dense_.size();

    sparse_[id] = index;
    denseId_.emplace_back(id);
    dense_.emplace_back(std::forward<U>(value));
  }

  // Remove
  void Remove(std::size_t const id)
  // pre(Contains(id))
  {
    auto const index = sparse_[id];
    auto const lastIndex = dense_.size() - 1;
    auto const lastId = denseId_[lastIndex];

    if (index != lastIndex)
    {
      denseId_[index] = lastId;
      std::swap(dense_[index], dense_[lastIndex]);
      sparse_[lastId] = index;
    }

    denseId_.pop_back();
    dense_.pop_back();
  }

  // Get
  [[nodiscard]]
  constexpr auto Get(this auto&& self, std::size_t const id) noexcept
  // pre(self.Contains(id))
  {
    return self.dense_[self.sparse_[id]];
  }

  // clang-format off
  [[nodiscard]] constexpr auto  Size    (                                         ) const noexcept -> std::size_t { return dense_.size(); }
  [[nodiscard]] constexpr auto Capacity (                                         ) const noexcept -> std::size_t { return sparse_.size(); }
  [[nodiscard]] constexpr auto Empty    (                                         ) const noexcept -> bool        { return dense_.empty(); }
  [[nodiscard]] constexpr auto begin    (this auto &&self [[clang::lifetimebound]])       noexcept                { return self.dense_.begin(); }
  [[nodiscard]] constexpr auto end      (this auto &&self [[clang::lifetimebound]])       noexcept                { return self.dense_.end(); }
  // clang-format on

  // Clear
  void Clear() noexcept
  {
    denseId_.clear();
    dense_.clear();
  }

private:
  std::vector<std::size_t> sparse_{ };
  std::vector<std::size_t> denseId_{ };
  std::vector<T> dense_{ };
};
} // namespace TinyEngine
