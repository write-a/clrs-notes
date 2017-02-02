// Data structure: Binary Heap

// Representation: Array

// Description: A complete(except for the lowest level which is filled
// from the left) binary tree that maintains the invariant that for min heap
// the parent node's value is always no bigger than those of its children's and
// for max heap no smaller.

// Symbol: A (convention in this notes)

// Definitions:
//  A.length: Size of the array, A[0..A.length] is all the array elements
//  A.heap_size: Size of the heap, A[0..A.heap_size] is all the elements
//  organized in a conceptual binary heap.
//  Height: The height of a node in a heap is the number of edges on the longest
//          simple downward path from the node to a leaf.  The height of the
//          heap
//          is that of the root.

// APIs
// The API is named such that the binary_heap class template can be used
// directly as a min(max) heap(priority queue).
// extract_root: extract_min/max for min/max heap ..........................O(1)
// make_heap : organize an unordered array into a heap in O(1) time.........O(1)
// heapify : maintains the heap invariant, max_heapify for max heap.......O(lgN)

// Applications:
//  - heapsort
//  - priority queue

// In C++ <algorithm> library, the std::make_heap can organize a vector into a
// heap.
// This is just an exercise for understanding the data structure

#include <algorithm>
#include <functional>
#include <vector>

namespace clrs {
namespace tree {
using std::vector;
template <class T, class Comparator = std::less<T>> class binary_heap {
public:
  // This procedure is called to bring the invariant back.  It's assumed that
  // when it's called on node i, the invariants of the sub trees rooted at
  // left_child(i) and right_child(i) are not broken but the node i make have
  // to be "float down" the tree
  // Analysis: This procedure is bounded by the height of the heap thus
  // finishes in O(lgN) time.
  void heapify(int i) {
    int lchild = left_child(i);
    int rchild = right_child(i);
    // When the invariant is broken, we need to make a 3-way comparison among
    // left_child(i), right_child(i) and i itself.
    int largest = i;
    if (lchild < _heap_sz && Comparator()(_v[lchild], _v[i])) {
      largest = lchild;
    }
    if (rchild < _heap_sz && Comparator()(_v[rchild], _v[largest])) {
      largest = rchild;
    }
    if (largest != i) {
      this->swap(i, largest);
      // keep flowing it down
      heapify(largest);
    }
    // otherwise we are already a min or max heap
  }

  // This procedure organizes an unordered array into a heap.
  // It looks like an O(NlgN) procedure.  But in fact it's O(N). (Each level
  // has fewer nodes when we are approaching to the root).
  // See detailed analysis on P.157-159 of CLRS
  void make_heap() {
    _heap_sz = _v.length();
    // We just need to take care of the first half of the array because
    // the second half is all leafs.  Each leaf itself is already a 1-element
    // heap so the invariant holds trivially.  While taking care of the leafs'
    // parents (all in the first half), any necessary "float down" will happen.
    for (int i = _v.length() / 2; i >= 0; --i) {
      heapify(i);
    }
  }

  void insert();
  void extract_root();

protected:
  inline int parent(int i) {
    // TODO: maybe we should throw if the user asks us the parent of the root
    return (i - 1) / 2;
  }
  inline int left_child(int i) { return 2 * i - 1; }
  inline int right_child(int i) { return 2 * i; }
  inline void swap(int i, int j) { std::iter_swap(_v.at(i), _v.at(j)); }

private:
  vector<T> _v; // for storage
  int _heap_sz;
};
}
}
