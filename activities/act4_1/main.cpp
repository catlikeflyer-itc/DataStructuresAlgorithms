//
//  main.cpp
//  actividad_4-1
//
//  Created by Vicente Cubells on 13/11/20.
//  Edited by Do Hyun Nam - A01025276 and Emiliano Cabrera - A01025453 on 13/11/21
//

#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <stack>
#include <list>

#include "Graph.hpp"

void loadGraph2(int v, int e, Graph<int, int> * graph)
{    
    std::srand(std::time(nullptr));

    int count = 0;

    // Adds vertexes to graph
    for (int i = 0; i < v; ++i){ 
        graph->addVertex(i);
    }
    
    // * New addition (returns a segmentation fault)
    for (int j = 0; j < e; j++){
        // Create random edges from existing vertexes
        Vertex <int, int> * v1 = graph->nodes[rand() % (v)];
        Vertex <int, int> * v2 = graph->nodes[rand() % (v)];

        if (count < e && v1 != v2) {
            graph->addEdge(v1, v2, count);
            count++;
        }
    }
    /* while (count < e){
        xPos = rand() % (e);
        yPos = rand() % (e);
        Vertex<int, int> * xVal = graph->nodes[xPos];
        Vertex<int, int> * yVal = graph->nodes[yPos];
        count++;
    } */

    std::cout << *graph << std::endl;
}

// creation of a Graph data structure as an adjacency matrix. Time complexity of O(n^2).
void loadGraph(int v, int e, std::vector < std::vector<int> > & graph)
{

    std::srand(std::time(nullptr));
    int a, b;

    for(int i = 0; i < graph.size(); i++){ // loop that fills the v X v sized matrix with 0's
        for(int j = 0; j < graph.size(); j++){
            graph[i].push_back(0);
        }
    }

    while(e != 0){ // randomly creates e connections between the v different objects and inserts them into the matrix as 1's
        a = std::rand() % (v);
        b = std::rand() % (v);

        if(graph[a][b] == 1 || a == b){ // prevents duplicate connections from being created and also self-connections 
            continue;
        }

        graph[a][b] = 1; // creates one-directional connections

        e--;
    }
}

// DFS traversal of the adjacency matrix graph. Time complexity of O(n^2).
void DFS(std::vector < std::vector<int> > & graph, int u)
{
    bool * visited = new bool[graph.size()]; // boolean list to mark nodes as visited or not
    std::stack<int> next;
    int current;
    bool vis_curr;

    for(int i = 0; i < graph.size(); i++){ // sets all nodes as unvisited
        visited[i] = false;
    }

    next.push(u);

    while(!next.empty()){ // iterates as long as there are unvisited nodes in the queue
        current = next.top();
        next.pop();

        if(!visited[current]){ // prints a node and marks it as visited, as long as it was unvisited
            std::cout << current << "  ";
            visited[current] = true;
        }

        for(int i = 0; i < graph.size(); i++){ // iterates as long as there are unvisited nodes in the matrix
            if(graph[current][i] == 1 && !visited[i]){
                next.push(i);
            }
        }
    }
}

void BFS(Graph<int, int> * graph, int u)
{
    std::list<int> Q;
    
    bool *visitedNodes = new bool[graph->nodes.size()]; 
    for(int i = 0; i < graph->nodes.size(); i++) 
        visitedNodes[i] = false; 
  
    // Marcar el nodo inicial com pasado
    visitedNodes[u] = true; 
    Q.push_back(u); 
   
    std::vector<Vertex<int,int>*>::iterator i;
  
    while(!Q.empty()){ 
        // Dequeue a vertex from queue and print it 
        u = Q.front(); 
        std::cout << u << " "; 
        Q.pop_front(); 

        // Get all adjacent vertices of the dequeued 
        // vertex u. If a adjacent has not been visited,  
        // then mark it visited and enqueue it 
        //for (i = graph->nodes.begin(); i != graph->nodes.end(); ++i){ 
        for (int j = u; j < graph->nodes.size(); j++){ 
            if (!visitedNodes[j]){ 
                visitedNodes[j] = true; 
                Q.push_back(j); 
            } 
        } 
    } 
}

int main(int argc, const char * argv[]) {
    /* Definir número de vértices y aristas */
    const int vertices = 10;
    const int aristas = 15;
    
    /* Declaración del grafo como matriz de adyacencia */
    std::vector < std::vector<int> > matriz_adyacencia(vertices);

    /* Generar el grafo como matriz de adyacencia */
    loadGraph(vertices, aristas, matriz_adyacencia);
    
    /* Recorrido con DFS */
    std::cout << "------ Matriz de adyacencia con DFS ------" << std::endl;
    int u = 1;
    DFS(matriz_adyacencia, u);
    
    /* Declaración del grafo como multilista */
    Graph<int, int> * multilista = new Graph<int, int>();

    /* Generar el grafo como multilista */
    loadGraph2(vertices, aristas, multilista);
    
    /* Recorrido con BFS */
    std::cout << "------ Multilista con BFS ------" << std::endl;
    u = 1;
    BFS(multilista, u);
    
    delete multilista;
    
    return 0;
}
