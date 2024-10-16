#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Función para encontrar el mínimo en Dijkstra
int minDistance(const vector<int>& dist, const vector<bool>& sptSet, int n) {
    int min = INF, min_index = -1;
    
    for (int v = 0; v < n; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

// Algoritmo de Dijkstra para un nodo fuente
void dijkstra(const vector<vector<int>>& graph, int src, int n) {
    vector<int> dist(n, INF); // Distancias
    vector<bool> sptSet(n, false); // Conjunto de nodos ya procesados

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, sptSet, n);

        if (u == -1) break; // Si no hay más nodos alcanzables

        sptSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (!sptSet[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Imprimir las distancias desde el nodo src a todos los demás
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

// Algoritmo de Floyd-Warshall
void floydWarshall(vector<vector<int>>& graph, int n) {
    vector<vector<int>> dist = graph;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Imprimir la matriz resultado de Floyd-Warshall
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
