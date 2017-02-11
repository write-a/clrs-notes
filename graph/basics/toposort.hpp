#pragma once
#include "dfs.hpp"
#include "graph.hpp"
#include <stack>
#include <string>
#include <vector>

namespace clrs {
namespace graph {

using std::string;

class topo_node : public dfs_node {

public:
  topo_node() : dfs_node() {}
  topo_node(int id, const string &name) : dfs_node(id), name(name) {}
  topo_node(const topo_node &other) : dfs_node(other), name(other.name) {}
  virtual ~topo_node() {}
  string name;
};

ostream &operator<<(ostream &stream, const topo_node &n) {
  stream << "id: " << n.id << ", name: " << n.name << ", dist: " << n.dist
         << ", dtime: " << n.discovery_time
         << ", finish time: " << n.finish_time << ", prev: ";
  if (n.prev)
    stream << n.prev->id;
  else
    stream << "null";
}
}
}
