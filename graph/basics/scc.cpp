// stronly connected components of DAG
//
// definition:
// maximal subsets of vertices of G such that in each subset (SCC)
// for each pair of vertices u, v, there's a path from u to v and
// vice versa.
//
// algorithm:
// 1. call dfs(G) to compute finishing times u.f for each vertex u
// 2. compute G' (G's transpose, i.e flipping the direction of all edges)
// 3. call dfs(G'), but in the main loop of dfs, consider the vertices
//    in th eorder of decreasing u.f
// 4. output the vertices of each tree in the depth-first forest of 3 as
//    a separate SCC.
//

int main() {

  fixed_graph<topo_node, 8> dag;
  dag.add(topo_node(0, "a"));
  dag.add(topo_node(1, "b"));
  dag.add(topo_node(2, "c"));
  dag.add(topo_node(3, "d"));
  dag.add(topo_node(4, "e"));
  dag.add(topo_node(5, "f"));
  dag.add(topo_node(6, "g"));
  dag.add(topo_node(7, "h"));
  dag.add(topo_node(0, "a"), topo_node(1, "b"));
  dag.add(topo_node(1, "b"), topo_node(2, "c"));
  dag.add(topo_node(1, "b"), topo_node(4, "e"));
  dag.add(topo_node(1, "b"), topo_node(5, "f"));
  dag.add(topo_node(2, "c"), topo_node(3, "d"));
  dag.add(topo_node(2, "c"), topo_node(6, "g"));
  dag.add(topo_node(3, "d"), topo_node(2, "c"));
  dag.add(topo_node(3, "d"), topo_node(7, "h"));
  dag.add(topo_node(4, "e"), topo_node(0, "a"));
  dag.add(topo_node(4, "e"), topo_node(5, "f"));
  dag.add(topo_node(5, "f"), topo_node(6, "g"));
  dag.add(topo_node(6, "g"), topo_node(5, "f"));
  dag.add(topo_node(6, "g"), topo_node(7, "h"));
  dag.add(topo_node(7, "h"), topo_node(7, "h"));
}
