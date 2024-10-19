/*
 * Descripción: Implementación de los algoritmos de Dijkstra y Floyd-Warshall para calcular
 *              las distancias mínimas entre nodos en un grafo.
 * Autores: Alejandro Muñoz Shimano, Ángel Francisco García Guzmán, Samir Baidon Pardo
 * Fecha: 20/10/2024
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX; // Constante que representa la falta de conexión entre nodos

/**
 * Función para encontrar el nodo con la distancia mínima que no ha sido procesado aún.
 * 
 * @param dist Vector con las distancias mínimas desde el nodo fuente.
 * @param shortestPathTreeSet Vector booleano que indica si un nodo ya ha sido procesado.
 * @param n Número de nodos en el grafo.
 * @return Índice del nodo con la menor distancia.
 */
int minDistance(const vector<int>& dist, const vector<bool>& shortestPathTreeSet, int n) {
    int min = INF, min_index = -1;
    
    for (int v = 0; v < n; v++) {
        if (!shortestPathTreeSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

/**
 * Implementación del algoritmo de Dijkstra que calcula las distancias más cortas desde un nodo fuente
 * a todos los demás nodos en el grafo.
 * 
 * @param graph Matriz de adyacencia que representa el grafo.
 * @param src Nodo fuente desde el cual se calculan las distancias.
 * @param n Número de nodos en el grafo.
 */
void dijkstra(const vector<vector<int>>& graph, int src, int n) {
    vector<int> dist(n, INF); // Inicializa las distancias con el valor más alto (infinito)
    vector<bool> shortestPathTreeSet(n, false); // Indica si un nodo ya ha sido procesado

    dist[src] = 0; // La distancia al nodo fuente es siempre 0

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, shortestPathTreeSet, n);

        // Si no hay más nodos alcanzables, se termina el ciclo
        if (u == -1) break;

        shortestPathTreeSet[u] = true;

        // Actualiza las distancias de los nodos adyacentes al nodo u
        for (int v = 0; v < n; v++) {
            if (!shortestPathTreeSet[v] && graph[u][v] != INF && dist[u] != INF 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Imprimir las distancias desde el nodo fuente a los demás nodos
    for (int i = 0; i < n; i++) {
        if (i != src) {
            if (dist[i] == INF) {
                cout << "node " << src + 1 << " to node " << i + 1 << ":  INF" << endl;
            } else {
                cout << "node " << src + 1 << " to node " << i + 1 << ":  " << dist[i] << endl;
            }
        }
    }
}

/**
 * Implementación del algoritmo de Floyd-Warshall que calcula las distancias más cortas
 * entre todos los pares de nodos en el grafo.
 * 
 * @param graph Matriz de adyacencia que representa el grafo.
 * @param n Número de nodos en el grafo.
 */
void floydWarshall(vector<vector<int>>& graph, int n) {
    vector<vector<int>> dist = graph; // Copia de la matriz original para no modificar el grafo original

    // Actualiza las distancias más cortas para cada par de nodos
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Imprimir la matriz de distancias resultado de Floyd-Warshall
    cout << "Floyd:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    // Leer la matriz de adyacencia
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == -1) {
                graph[i][j] = INF; // Convertir -1 a INF para representar la falta de arco
            }
        }
    }

    // Algoritmo de Dijkstra
    cout << "Dijkstra:" << endl;
    for (int i = 0; i < n; i++) {
        dijkstra(graph, i, n);
    }

    // Algoritmo de Floyd-Warshall
    floydWarshall(graph, n);

    return 0;
}
