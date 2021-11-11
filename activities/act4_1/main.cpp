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

#include "Graph.hpp"

void loadGraph2(int v, int e, Graph<int, int> * graph)
{
    /* Implementar */
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
    /* Implementar */
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
