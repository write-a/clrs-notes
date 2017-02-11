#pragma once
#include "graph.hpp"
#include <iostream>

namespace clrs {
namespace graph {
using namespace std;

class dfs_node : public node {

public:
  explicit dfs_node(int id) : node(id), discovery_time(0), finish_time(0) {}
  dfs_node() : node(), discovery_time(0), finish_time(0) {}
  virtual ~dfs_node() {}
  dfs_node(const dfs_node &other)
      : node(other), discovery_time(other.discovery_time),
        finish_time(other.finish_time) {}
  int discovery_time;
  int finish_time;
};

ostream &operator<<(ostream &stream, const dfs_node &n) {
  stream << "id: " << n.id << ", dist: " << n.dist
         << ", dtime: " << n.discovery_time
         << ", finish time: " << n.finish_time << ", prev: ";
  if (n.prev)
    stream << n.prev->id;
  else
    stream << "null";
}
}
}
