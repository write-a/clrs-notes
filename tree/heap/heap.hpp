// Data structure: Binary Heap

// Representation: Array

// Description: A complete(except for the lowest level which is filled
// from the left) binary tree that maintains the invariant that for min heap
// the parent node's value is always no bigger than those of its children's and
// for max heap no smaller.

// Symbol: A (convention in this notes)

// Definitions:
//  A.length: Size of the array, A[0..A.length] is all the array elements
//  A.heap_size: Size of the heap, A[0..A.heap_size] is all the elements.
//               In our implementation, we don't make the distinction of the
//               two because we'll always keep the whole array as a heap.
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
// heap.  One can also use the ready-made std::priority_queue.
// This is just an exercise for understanding the data structure

#include <algorithm>
#include <deque>
#include <functional>

namespace clrs {
namespace tree {
using std::deque;
// TODO: replace all int i with proper iterators
template <class T, class Comparator = std::less<T>> class binary_heap {
  // if it's the default less comparator, then it's a min heap
  // std::greater for max heap
public:
  // This procedure is called to bring the invariant back.  It's assumed that
  // when it's called on node i, the invariants of the sub trees rooted at
  // left_child(i) and right_child(i) are not broken but the node i may have
  // to be "float down" the tree.
  // Analysis: This procedure is bounded by the height of the heap thus
  // finishes in O(lgN) time.
  void heapify(int i) {
    int lchild = left_child(i);
    int rchild = right_child(i);
    // When the invariant is broken, we need to make a 3-way comparison among
    // left_child(i), right_child(i) and i itself.
    int smallest = i;
    if (lchild < _v.length() && Comparator()(_v[lchild], _v[i])) {
      smallest = lchild;
    }
    if (rchild < _v.length() && Comparator()(_v[rchild], _v[smallest])) {
      smallest = rchild;
    }
    if (smallest != i) {
      this->swap(i, smallest);
      // keep flowing it down
      heapify(smallest); // TODO: a non recursive solution?
    }
    // otherwise we are already a min or max heap
  }

  // This procedure organizes an unordered array into a heap.
  // It looks like an O(NlgN) procedure.  But in fact it's O(N). (Each level
  // has fewer nodes when we are approaching to the root).
  // See detailed analysis on P.157-159 of CLRS
  void make_heap() {
    // We just need to take care of the first half of the array because
    // the second half is all leafs.  Each leaf itself is already a 1-element
    // heap so the invariant holds trivially.  While taking care of the leafs'
    // parents (all in the first half), any necessary "float down" will happen.
    for (int i = _v.length() / 2; i >= 0; --i) {
      heapify(i); // TODO: use a non recursive solution
    }
  }

  // Put the new element at the end (bottom of the tree) and flow it up
  // This procedure is also bounded by the heap height
  void insert(T &&t) {
    _v.push_back(t);
    for (int i = _v.length() - 1; i > 0; i = parent(i)) {
      auto p = parent(i);
      // if the element is smaller than its parent, we swap it with its parent
      if(Comparator()(_v.back(), _v[p]){
        iter_swap(_v.length() - 1, p);
      }
    }
  }

  T extract_root() {
    if (_v.empty()) {
      throw; // TODO: proper exception class
    }
    T = _v[0];
    _v[0] = _v[_v.length() - 1];
    heapify(0); // The nice thing about the extract_root procedure is that
                // it doesn't know or care about whether it's a min heap or
                // a max heap, everything is hidden in the heapify procedure.
    return std::move(T);
  }

protected:
  inline int parent(int i) {
    // TODO: maybe we should throw if the user asks us the parent of the root
    return (i - 1) / 2;
  }

  inline int left_child(int i) { return 2 * i - 1; }

  inline int right_child(int i) { return 2 * i; }

  inline void swap(int i, int j) { std::iter_swap(_v.at(i), _v.at(j)); }

private:
  deque<T> _v; // for storage
};
}
}
