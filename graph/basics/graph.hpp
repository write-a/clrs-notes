// an adjacency list representation of graph
//

#include <array>
#include <vector>
#include <cassert>
#include <utility>
#include <iostream>

using namespace std;

namespace clrs{

    namespace graph{


        class node{

            public:
            node():id(-1),dist(0),prev(nullptr){};
            explicit node(int id):id(id),dist(0),prev(nullptr){}
            ~node(){}
            int id;
            int dist;
            node* prev;

        };
        ostream& operator<< (ostream& stream, const node& n){
            stream << "id: " << n.id << ", dist: " << n.dist << ", prev: ";
            if(n.prev)
                stream << n.prev->id;
            else
                stream << "null";
        }
    

    
        template<class T>
        class adjacency_list{
            public:
            adjacency_list(){}
            explicit adjacency_list(T&& head):head(head){}
            ~adjacency_list(){}
            T head;
            vector<T> adj_list;
        };
        
        template<class T>
        ostream& operator<< (ostream& stream, const adjacency_list<T>& l){
            stream << "T: " << l.head << ", list: [";
            for(auto& t: l.adj_list){
                stream << "(" << t << ")--> "; 
            }
            stream << " ]";
        }



        template<class T, int V>
        class fixed_graph{
            public:
            fixed_graph(){}
            ~fixed_graph(){}
            void add(T&& u, T&& v){
                assert(u.id < V);
                if(graph[u.id].adj_list.empty()){
                    graph[u.id].head.id = u.id;
                    graph[u.id].head.dist = u.dist;
                }
                graph[u.id].adj_list.push_back(forward<T>(v));
            }

            array<adjacency_list<T>, V> graph;

        };
            
        template<class T, int V>
        ostream& operator<< (ostream& stream, const fixed_graph<T,V>& g){
            for(auto& l : g.graph){
                stream << l << "\n"; 
            }
        }

    
    }

}
