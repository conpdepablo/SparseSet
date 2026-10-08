#include <cassert>
#include <vector>

import TinyEngine.SparseSet;

using TinyEngine::SparseSet;

void Test_StartsEmpty()
{
  SparseSet<int> set{ 5 };

  assert(set.Size() == 0);
  assert(set.Empty());
  assert(set.Capacity() == 5);
}

void Test_InsertAndContains()
{
  SparseSet<int> set{ 5 };

  set.Insert(2, 42);

  assert(set.Size() == 1);
  assert(!set.Empty());

  assert(set.Contains(2));
  assert(!set.Contains(0));
  assert(!set.Contains(1));
  assert(!set.Contains(3));
  assert(!set.Contains(4));
}

void Test_Get()
{
  SparseSet<int> set{ 5 };

  set.Insert(2, 42);

  assert(set.Get(2) == 42);
}

void Test_ConstGet()
{
  SparseSet<int> set{ 5 };

  set.Insert(2, 42);

  SparseSet<int> const& constSet = set;

  assert(constSet.Get(2) == 42);
}

void Test_DynamicResize()
{
  SparseSet<int> set{ 5 };

  set.Insert(7, 42);

  assert(set.Size() == 1);
  assert(set.Contains(7));
  assert(set.Get(7) == 42);
  assert(set.Capacity() == 8);
}

void Test_DynamicResizePreservesElements()
{
  SparseSet<int> set{ 5 };

  set.Insert(1, 10);
  set.Insert(3, 30);
  set.Insert(10, 100);

  assert(set.Size() == 3);

  assert(set.Contains(1));
  assert(set.Contains(3));
  assert(set.Contains(10));

  assert(set.Get(1) == 10);
  assert(set.Get(3) == 30);
  assert(set.Get(10) == 100);

  assert(set.Capacity() == 11);
}

void Test_Capacity()
{
  SparseSet<int> set{ 5 };

  assert(set.Capacity() == 5);

  set.Insert(10, 100);

  assert(set.Capacity() == 11);
}

void Test_ContainsOutOfRange()
{
  SparseSet<int> set{ 5 };

  assert(!set.Contains(5));
  assert(!set.Contains(100));
  assert(!set.Contains(100000));
}

void Test_Remove()
{
  SparseSet<int> set{ 5 };

  set.Insert(1, 10);
  set.Insert(2, 20);
  set.Insert(3, 30);

  set.Remove(2);

  assert(set.Size() == 2);

  assert(set.Contains(1));
  assert(!set.Contains(2));
  assert(set.Contains(3));

  assert(set.Get(1) == 10);
  assert(set.Get(3) == 30);
}

void Test_RemoveLast()
{
  SparseSet<int> set{ 5 };

  set.Insert(1, 10);
  set.Insert(2, 20);

  set.Remove(2);

  assert(set.Size() == 1);
  assert(set.Contains(1));
  assert(!set.Contains(2));
  assert(set.Get(1) == 10);
}

void Test_RemoveOnlyElement()
{
  SparseSet<int> set{ 5 };

  set.Insert(2, 42);
  set.Remove(2);

  assert(set.Size() == 0);
  assert(set.Empty());
  assert(!set.Contains(2));
}

void Test_ReinsertRemovedId()
{
  SparseSet<int> set{ 5 };

  set.Insert(1, 10);
  set.Insert(2, 20);
  set.Insert(3, 30);

  set.Remove(2);

  assert(!set.Contains(2));

  set.Insert(2, 200);

  assert(set.Size() == 3);
  assert(set.Contains(2));
  assert(set.Get(2) == 200);

  assert(set.Get(1) == 10);
  assert(set.Get(3) == 30);
}

void Test_Clear()
{
  SparseSet<int> set{ 5 };

  set.Insert(1, 10);
  set.Insert(2, 20);
  set.Insert(3, 30);

  set.Clear();

  assert(set.Empty());
  assert(set.Size() == 0);

  assert(!set.Contains(1));
  assert(!set.Contains(2));
  assert(!set.Contains(3));
}

void Test_ClearAndReuse()
{
  SparseSet<int> set{ 5 };

  set.Insert(1, 10);
  set.Insert(2, 20);

  set.Clear();

  set.Insert(2, 200);
  set.Insert(10, 1000);

  assert(set.Size() == 2);

  assert(set.Contains(2));
  assert(set.Contains(10));

  assert(set.Get(2) == 200);
  assert(set.Get(10) == 1000);
}

void Test_Iteration()
{
  SparseSet<int> set{ 5 };

  set.Insert(1, 10);
  set.Insert(2, 20);
  set.Insert(3, 30);

  std::vector<int> values;

  for (auto const value : set)
  {
    values.push_back(value);
  }

  assert(values.size() == 3);
  assert(values[0] == 10);
  assert(values[1] == 20);
  assert(values[2] == 30);
}

int main()
{
  Test_StartsEmpty();
  Test_InsertAndContains();
  Test_Get();
  Test_ConstGet();

  Test_DynamicResize();
  Test_DynamicResizePreservesElements();
  Test_Capacity();
  Test_ContainsOutOfRange();

  Test_Remove();
  Test_RemoveLast();
  Test_RemoveOnlyElement();
  Test_ReinsertRemovedId();

  Test_Clear();
  Test_ClearAndReuse();

  Test_Iteration();
}
