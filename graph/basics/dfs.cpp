#include "graph.hpp"
#include <stack>
#include <vector>

using namespace std;
using namespace clrs::graph;

static int current_time = 0;

template <class T, int V>
void dfs_visit(fixed_graph<T, V> &g, int s, vector<bool> &visited,
               stack<int> &stk) {
  assert(s < g.graph.size());
  g.graph[s].head.discovery_time = current_time;
  dfs_node *predecessor = nullptr;
  g.graph[s].head.prev = predecessor;
  cout << "pushing guard: " << s << "\n";
  stk.push(s + V);
  cout << "pushing : " << s << "\n";
  stk.push(s);
  set_visited(visited, s);
  while (!stk.empty()) {
    auto u = stk.top();
    stk.pop();

    if (u >= V) {
      g.graph[u - V].head.finish_time = ++current_time;
      cout << "popping guard -->: " << u - V << ", f time: " << current_time
           << "\n";
      continue;
    }
    cout << "popping -->: " << u << "\n";

    // set predecessor node
    g.graph[u].head.prev = predecessor;

    // I'm now the predecessor
    predecessor = &g.graph[u].head;

    for (auto &neighbour : g.graph[u].adj_list) {
      if (visited[neighbour.id])
        continue;
      // first time visit, push a task to compute the finish time
      // when this task (denoted by u+V, no such vertice exists) is popped
      // it means all it's adjacency list has been explored and we'll
      // mark it as finished
      cout << "pushing guard : " << neighbour.id << "\n";
      stk.push(neighbour.id + V);
      g.graph[neighbour.id].head.discovery_time = ++current_time;
      cout << "pushing : " << neighbour.id << ", d time: " << current_time
           << "\n";
      stk.push(neighbour.id);
      set_visited(visited, neighbour.id);
      // set discovery current_time
    }
  }
}

template <class T, int V> void dfs(fixed_graph<T, V> &g) {
  stack<int> stk;
  vector<bool> visited(g.graph.size(), false);
  for (auto &l : g.graph) {
    if (!visited[l.head.id])
      dfs_visit(g, l.head.id, visited, stk);
  }
}

int main() {

  fixed_graph<dfs_node, 5> g;
  g.add(dfs_node(0), dfs_node(1));
  g.add(dfs_node(0), dfs_node(4));
  g.add(dfs_node(4), dfs_node(0));
  g.add(dfs_node(4), dfs_node(1));
  g.add(dfs_node(4), dfs_node(3));
  g.add(dfs_node(1), dfs_node(0));
  g.add(dfs_node(1), dfs_node(3));
  g.add(dfs_node(1), dfs_node(4));
  g.add(dfs_node(1), dfs_node(2));
  g.add(dfs_node(2), dfs_node(1));
  g.add(dfs_node(2), dfs_node(3));
  g.add(dfs_node(3), dfs_node(2));
  g.add(dfs_node(3), dfs_node(1));
  g.add(dfs_node(3), dfs_node(4));
  dfs(g);
  dump_graph(g);
}
