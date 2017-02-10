// an adjacency list representation of graph
//

#include <array>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace clrs {

namespace graph {

class node {

public:
  node() : id(-1), dist(0), prev(nullptr){};
  explicit node(int id) : id(id), dist(0), prev(nullptr) {}
  virtual ~node() {}
  int id;
  int dist;
  node *prev;
};

class dfs_node : public node {

public:
  explicit dfs_node(int id) : node(id), discovery_time(0), finish_time(0) {}
  dfs_node() : discovery_time(0), finish_time(0) {}
  virtual ~dfs_node() {}
  int discovery_time;
  int finish_time;
};

ostream &operator<<(ostream &stream, const node &n) {
  stream << "id: " << n.id << ", dist: " << n.dist << ", prev: ";
  if (n.prev)
    stream << n.prev->id;
  else
    stream << "null";
}

ostream &operator<<(ostream &stream, const dfs_node &n) {
  stream << "id: " << n.id << ", dist: " << n.dist
         << ", dtime: " << n.discovery_time
         << ", finish time: " << n.finish_time << ", prev: ";
  if (n.prev)
    stream << n.prev->id;
  else
    stream << "null";
}

template <class T> class adjacency_list {
public:
  adjacency_list() {}
  explicit adjacency_list(T &&head) : head(head) {}
  ~adjacency_list() {}
  T head;
  vector<T> adj_list;
};

template <class T>
ostream &operator<<(ostream &stream, const adjacency_list<T> &l) {
  stream << "T: " << l.head << ", list: [";
  for (auto &t : l.adj_list) {
    stream << "(" << t << ")--> ";
  }
  stream << " ]";
}

template <class T, int V> class fixed_graph {
public:
  fixed_graph() {}
  ~fixed_graph() {}
  void add(T &&u, T &&v) {
    assert(u.id < V);
    if (graph[u.id].adj_list.empty()) {
      graph[u.id].head.id = u.id;
      graph[u.id].head.dist = u.dist;
    }
    graph[u.id].adj_list.push_back(forward<T>(v));
  }

  array<adjacency_list<T>, V> graph;
};

template <class T, int V>
ostream &operator<<(ostream &stream, const fixed_graph<T, V> &g) {
  for (auto &l : g.graph) {
    stream << l << "\n";
  }
}

void set_visited(vector<bool> &visited, int i) {
  // cout << "node " << i << " is now visited\n";
  visited[i] = true;
}

template <class T, int V> void dump_graph(fixed_graph<T, V> &g) {
  cout << "--------------------\n";
  cout << g;
  cout << "--------------------\n";
}
}
}
