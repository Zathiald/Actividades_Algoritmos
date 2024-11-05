#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <string>

using namespace std;

struct Edge {
    int u, v, weight;
};

// Punto 1: Calcular las distancias entre colonias
void calculateDistances(int N, const vector<vector<int>>& graph) {
    cout << "            Punto 01" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                cout << "Colonia " << (i + 1) << " a colonia " << (j + 1) << ": " << graph[i][j] << endl;
            }
        }
        cout << endl;
    }
}

// Punto 2: Realizar un recorrido simple (TSP aproximado)
void tspApproximation(const vector<vector<int>>& graph) {
    cout << "            Punto 02" << endl;

    int N = graph.size();
    vector<bool> visited(N, false);
    vector<int> path;
    int cost = 0;

    // Iniciar desde la colonia 1
    int current = 0; // Colonia 1
    visited[current] = true;
    path.push_back(current + 1); // Agregar la colonia al recorrido

    for (int i = 1; i < N; i++) {
        int next = -1;
        int minDist = numeric_limits<int>::max();

        // Encontrar la colonia no visitada más cercana
        for (int j = 0; j < N; j++) {
            if (!visited[j] && graph[current][j] < minDist) {
                minDist = graph[current][j];
                next = j;
            }
        }

        // Actualizar costos y recorrido
        if (next != -1) {
            visited[next] = true;
            cost += minDist;
            path.push_back(next + 1);
            current = next; // Moverse a la siguiente colonia
        }
    }

    // Volver a la colonia inicial
    cost += graph[current][0]; // Regresar a la colonia inicial
    path.push_back(1); // Volver a la colonia 1

    // Imprimir el recorrido y el costo
    cout << "El recorrido:" << endl;
    for (int p : path) {
        cout << p;
        if (p != 1) cout << " -> "; // No imprimir '->' después del último
    }
    cout << endl;
    cout << "El costo: " << cost << endl << endl;
}

// Punto 3: Calcular el flujo máximo usando el algoritmo de Edmonds-Karp (BFS)
int edmondsKarp(const vector<vector<int>>& capacities, int source, int sink) {
    int N = capacities.size();
    vector<vector<int>> flow(N, vector<int>(N, 0));
    int totalFlow = 0;

    while (true) {
        vector<int> parent(N, -1);
        parent[source] = source;
        queue<pair<int, int>> q;
        q.push({source, numeric_limits<int>::max()});

        while (!q.empty()) {
            int u = q.front().first;
            int currentFlow = q.front().second;
            q.pop();

            for (int v = 0; v < N; v++) {
                if (parent[v] == -1 && capacities[u][v] > flow[u][v]) {
                    parent[v] = u;
                    int newFlow = min(currentFlow, capacities[u][v] - flow[u][v]);
                    if (v == sink) {
                        totalFlow += newFlow;
                        int cur = v;

                        while (cur != source) {
                            int prev = parent[cur];
                            flow[prev][cur] += newFlow;
                            flow[cur][prev] -= newFlow;
                            cur = prev;
                        }
                        break;
                    }
                    q.push({v, newFlow});
                }
            }
        }
        if (parent[sink] == -1) break; // No hay más caminos
    }

    return totalFlow;
}

// Punto 4: Calcular la distancia más corta entre la nueva central y la más cercana
double euclideanDistance(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

void calculateMinDistances(const vector<pair<int, int>>& positions, const pair<int, int>& newStation) {
    int N = positions.size();
    double minDistance = numeric_limits<double>::max();
    int nearestIndex = -1;

    for (int i = 0; i < N; i++) {
        double distance = euclideanDistance(positions[i], newStation);
        if (distance < minDistance) {
            minDistance = distance;
            nearestIndex = i;
        }
    }

    cout << "            Punto 04" << endl;
    cout << "La central más cercana a [" << newStation.first << ", " << newStation.second << "] es ["
         << positions[nearestIndex].first << ", " << positions[nearestIndex].second << "] con una distancia de "
         << minDistance << "." << endl;
}

// Función para leer el archivo de entrada
bool readInputFile(const string& filename, int& N, vector<vector<int>>& graph, 
                   vector<vector<int>>& capacities, vector<pair<int, int>>& positions, 
                   pair<int, int>& newStation) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    file >> N; // Leer número de colonias

    // Leer matriz de distancias
    graph.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file >> graph[i][j];
        }
    }

    // Leer matriz de capacidades
    capacities.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file >> capacities[i][j];
        }
    }

    // Leer posiciones de las centrales
    positions.clear();
    for (int i = 0; i < N; i++) {
        int x, y;
        char ch;
        file >> ch >> x >> ch >> y >> ch;
        positions.push_back({x, y});
    }

    // Leer posición de la nueva central
    int x, y;
    char ch;
    file >> ch >> x >> ch >> y >> ch;
    newStation = {x, y};

    file.close();
    return true;
}

int main() {
    int N;
    vector<vector<int>> graph, capacities;
    vector<pair<int, int>> positions;
    pair<int, int> newStation;

    // Solicitar el nombre del archivo de entrada
    string filename;
    cout << "Introduce el nombre del archivo de entrada (con extensión): ";
    cin >> filename;

    // Leer el archivo de entrada
    if (!readInputFile(filename, N, graph, capacities, positions, newStation)) {
        return 1;
    }

    // Punto 1: Calcular las distancias entre colonias
    calculateDistances(N, graph);
    cout << endl;

    // Punto 2: Realizar un recorrido simple (TSP aproximado)
    tspApproximation(graph);
    cout << endl;

    // Punto 3: Calcular el flujo máximo desde un nodo inicial (0) hasta un nodo final (N-1)
    int maxFlow = edmondsKarp(capacities, 0, N - 1);
    cout << "            Punto 03" << endl;
    cout << "Flujo máximo: " << maxFlow << endl << endl;

    // Punto 4: Calcular la distancia más corta entre la nueva central y la más cercana
    calculateMinDistances(positions, newStation);

    return 0;
}
