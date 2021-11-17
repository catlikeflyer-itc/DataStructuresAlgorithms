#ifndef graph_hpp
#define graph_hpp

#include<iostream> 
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

template <class T>
class GraphVertex
{
private:
    T val;
    std::vector<int> adj;
public: 
    ~GraphVertex() {};
    GraphVertex() {};
    GraphVertex(T _val) {val = _val;};

    T get_val() {return val;};
    void set_val(T _val) {val = _val;};

    std::vector<int> get_adj() {return adj;};
    void add_to_adj(int idx) {
        adj.push_back(idx);
    };

    friend bool operator == (GraphVertex<T> d, GraphVertex<T> dd){
        return (d.get_val() == dd.get_val());
    }
};

template <class T>
class Graph
{
private:
    std::vector<GraphVertex<T>> nodes;
    bool is_directed;

public:
    ~Graph() {};
    Graph() {is_directed=true;};

    void add_node(T val)
    {
        GraphVertex<T> node(val);
        nodes.push_back(node);
    };

    void add_edge(int src, int dst)
    {
        nodes[src].add_to_adj(dst);
        if (!is_directed)
            nodes[dst].add_to_adj(src);
    };

    void add_edge_element(string s, string d){
        GraphVertex<T> src(s);
        GraphVertex<T> dst(d);
        auto it_src = std::find(nodes.begin(), nodes.end(), src);
        auto it_dst = std::find(nodes.begin(), nodes.end(), dst);
        // Si existen
        if(it_src != nodes.end() && it_dst != nodes.end()){
            int i_src = it_src - nodes.begin();
            int i_dst = it_dst - nodes.begin();
            add_edge(i_src, i_dst);
            // std::cout<<i_src<<"->"<<i_dst<<std::endl;
        } // Si no existen
        else {
            std::cout<<"(error) no existen"<<endl;
        }
    }

    void printNeighbors(){
        for(int i = 0; i < nodes.size(); i++){
            if(nodes[i].get_adj().size() != 0){
                std::cout<< nodes[i].get_val() <<":\t"<<nodes[i].get_adj().size()<<std::endl;
            }
        }
    }

    map<T, int> saveNeigbhors(){
        map<T, int> count;
        for(int i = 0; i < nodes.size(); i++){
            count[ nodes[i].get_val() ] = nodes[i].get_adj().size();
        }
        return count;
    }

    void BFS(int start_vertex)
    {
        std::vector<int> visited(nodes.size(), 0); 
        std::queue<int> neighbors; 
        visited.at(start_vertex) = 1; 
        std::cout << nodes.at(start_vertex).get_val() << " "; 
        std::vector<int> adjacents; 
        adjacents = nodes.at(start_vertex).get_adj(); 
        for(int i = 0; i < adjacents.size(); i++){
            neighbors.push(adjacents.at(i)); 
        }
        while(!neighbors.empty()){
            int temp = neighbors.front(); 
            if(visited.at(temp) == 0){
                visited.at(temp) = 1; 
                std::cout << nodes.at(temp).get_val() << " "; 
                std::vector<int> adjacents;
                adjacents = nodes.at(temp).get_adj();
                for(int i=0; i<adjacents.size();i++){
                    neighbors.push(adjacents.at(i));
                }
            }
            neighbors.pop();
        }

        std::cout << std::endl;
    };

    void DFS(int start_vertex)
    {
        std::vector<int> visited(nodes.size(), 0);
        std::stack<int> neighbors;
        visited.at(start_vertex)=1;
        std::cout << nodes.at(start_vertex).get_val() << " ";
        std::vector<int> adjacents;
        adjacents=nodes.at(start_vertex).get_adj();
        for(int i=0; i<adjacents.size();i++)
        {
            neighbors.push(adjacents.at(i));
        }
        while(!neighbors.empty())
        {
            int temp = neighbors.top();
            neighbors.pop();
            if(visited.at(temp)==0)
            {
                visited.at(temp)=1;
                std::cout << nodes.at(temp).get_val() << " ";
                std::vector<int> adjacents;
                adjacents=nodes.at(temp).get_adj();
                for(int i=0; i<adjacents.size();i++)
                {
                    neighbors.push(adjacents.at(i));
                }
            }   
        }
        std::cout << std::endl;
    }

    int size(){
        return nodes.size();
    }
};

#endif