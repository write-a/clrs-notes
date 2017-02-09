// implement a breath-first-search algorithm

#include "graph.hpp"
#include <cassert>
#include <deque>
#include <set>
#include <iostream>
#include <vector>

using namespace std;
using namespace clrs::graph;

void set_visited(vector<bool>& visited, int i){
    // cout << "node " << i << " is now visited\n";
    visited[i] = true;
}

template<class T, int V>
void bfs(fixed_graph<T,V>& g, int s){
    assert(s < V);
    vector<bool> visited(V, false);
    deque<int> fifo;
    fifo.push_back(s);
    while(!fifo.empty()){
        auto u = fifo.front();
        for(auto it = g.graph[u].adj_list.begin(); it != g.graph[u].adj_list.end(); ++it){
            if(visited[it->id])
                continue;
            it->dist = g.graph[u].head.dist+1;
            it->prev = &g.graph[u].head;
            g.graph[it->id].head.dist = it->dist;
            g.graph[it->id].head.prev = it->prev;
            set_visited(visited, it->id);
            fifo.push_back(it->id);
        } 
        fifo.pop_front();
        set_visited(visited, u);
    }
}

template<class T, int V>
void print_path(fixed_graph<T,V>& g, int s, int v){
    if(s==v)
        cout << s+1 << ",";
    else if(!g.graph[v].head.prev)
        cout << "no path between " << s+1 << " and " << v+1;
    else{
        print_path(g, s, g.graph[v].head.prev->id); 
        cout << v+1 << ","; 
    }
}

template<class T, int V>
void print(fixed_graph<T,V>& g, int s, int v){

    cout << "path between " << s+1 << " and " << v+1 << ": ";
    print_path(g, s, v);
    cout << "\n";
}


int main(){

    fixed_graph<node, 5> g;
    g.add(node(0), node(1));
    g.add(node(0), node(4));
    g.add(node(4), node(0));
    g.add(node(4), node(1));
    g.add(node(4), node(3));
    g.add(node(1), node(0));
    g.add(node(1), node(3));
    g.add(node(1), node(4));
    g.add(node(1), node(2));
    g.add(node(2), node(1));
    g.add(node(2), node(3));
    g.add(node(3), node(2));
    g.add(node(3), node(1));
    g.add(node(3), node(4));
    for(int i = 0; i < 5; ++i){
        bfs(g, i);
        for(int j = 0; j < 5; ++j)
            print(g, i, j);
    }
}
