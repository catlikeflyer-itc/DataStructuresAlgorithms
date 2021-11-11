//
//  main.cpp
//  actividad_4-1
//
//  Created by Vicente Cubells on 13/11/20.
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
    int xPos, yPos;
    int count = 0;

    // Adds vertexes to graph
    for (int i = 0; i < v; ++i){ 
        graph->addVertex(i);
    }

    while (count < e){
        xPos = rand() % (e);
        yPos = rand() % (e);
        Vertex<int, int> * xVal = graph->nodes[xPos];
        Vertex<int, int> * yVal = graph->nodes[yPos];

        count++;
    }

    std::cout << *graph << std::endl;
}

void loadGraph(int v, int e, std::vector < std::vector<int> > & graph)
{

    std::srand(std::time(nullptr));
    int a, b;

    for(int i = 0; i < graph.size(); i++){
        for(int j = 0; j < graph.size(); j++){
            graph[i].push_back(0);
        }
    }

    while(e != 0){
        a = std::rand() % (v);
        b = std::rand() % (v);

        if(graph[a][b] == 1 || a == b){
            continue;
        }

        graph[a][b] = 1;

        e--;
    }
}

void DFS(std::vector < std::vector<int> > & graph, int u)
{
    bool * visited = new bool[graph.size()];
    std::stack<int> next;
    int current;
    bool vis_curr;

    for(int i = 0; i < graph.size(); i++){
        visited[i] = false;
    }

    next.push(u);

    while(!next.empty()){
        current = next.top();
        next.pop();

        if(!visited[current]){
            std::cout << current << "  ";
            visited[current] = true;
        }

        for(int i = 0; i < graph.size(); i++){
            if(!visited[i]){
                next.push(i);
            }
        }
    }
}

void BFS(Graph<int, int> * graph, int u)
{
    std::list<int> q;
    std::vector<int> values;
    Vertex <int, int> * temp;
    
    bool *visited = new bool[q.size()]; 

    for(int i = 0; i < q.size(); i++) 
        visited[i] = false; 
  
    // Marcar el nodo inicial com pasado
    visited[u] = true; 
    q.push_back(u); 
   
    
    while (!q.empty()){
        /* Almacenar el primer valor de la queue en auxiliar*/
        temp = q.front();
        std::cout << temp->getInfo() << std::endl;
        q.pop_front();

        if (temp->getIsVisited() == false){
            for (int i = 0; i<graph->getNumEdges(cuenta); i++){
                Edge<int, int> * arista = graph->getEdge(cuenta, i);
                valor = arista->getTarget()->getInfo();
                if (find(valores.begin(), valores.end(), valor) == valores.end()){
                    valores.push_back(valor);
                    q.push(arista->getTarget()); 
                }
            }
            aux->setIsVisited();
            cuenta = q.front()->getInfo();
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
