//
// Created by heineken97 on 27/2/20.
//
#include <vector>
#include <queue>
using namespace std;

#define MAXV 100 //Maxima cantidad de vertices
#define infine 0x3f3f3f3f

struct Edge {
    int node;  // Nodo destino
    int cost;

    Edge(int _node, int _cost) : node(_node), cost(_cost) {} // Builder param
    Edge() : node(-1), cost(-1) {} // Builder by default
};

struct Graph {
    vector<Edge> Ady[MAXV];
    int V; // Cantidad de vertices
    int E; // Cantidad de Aristas
};

struct State{
    int node; // Nodo actual
    int cost;
    State(int _node, int _cost): node(_node), cost(_cost){}
    bool operator<(const State &b) const {// sobrecargar operador de prioridad
        return cost>b.cost;
    }
};

int algorithm_dijkstra(const int start, const int end, const Graph graph){

    priority_queue<State> priorityQueue;
    // Distancia hacia todos los vertices, inicia infinito & vertices procesados
    vector<int> Len(graph.V,infine);
    vector<bool> check(graph.V, false);

    Len[start]=0;
    //Agregar vertice de partida
    priorityQueue.push(State(start,0));
    //Mientras aun hay nodos por procesar
    while(!priorityQueue.empty()){
        State stat = priorityQueue.top(); priorityQueue.pop(); //desencola
        check[stat.node] = true;  //marcar nodo visitado
        if(stat.node == end){
            return stat.cost; //LLego al nodo destino, retorna peso del camino
        }
        int T= (int)graph.Ady[stat.node].size();
        for(int i = 0; i < T; i++){
            //Si no se ha procesado el vertice y la distancia es menor a la distancia de Len, el camino mas corto
            if (!check[graph.Ady[stat.node][i].node] && ((Len[stat.node] + graph.Ady[stat.node][i].cost) < Len[graph.Ady[stat.node][i].node])){
                Len[graph.Ady[stat.node][i].node] = stat.cost + graph.Ady[stat.node][i].cost;
                priorityQueue.push(State(graph.Ady[stat.node][i].node, stat.cost + graph.Ady[stat.node][i].cost));
            }
        }
    }
    return -1;
}