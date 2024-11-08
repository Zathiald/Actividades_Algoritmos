#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <string>

using namespace std;

/*
 * Descripción: Programa para obtener rutas optimas para conexion de redes entre colonia.
 * Autor: Samir Baidon Pardo A01705403,
 *        Angel Francisco Garcia Guzman A01704203,
 *        Alejandro Muñoz Shimano A01705550
 * Fecha de creación: 2024-11-04
 */

/**
 * Algoritmo de Floyd-Warshall para encontrar distancias mínimas entre todos los pares de nodos.
 * 
 * @param N Número de nodos.
 * @param grafo Matriz de adyacencia con las distancias entre nodos.
 */
void floydWarshall(int N, vector<vector<int>>& grafo) {
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grafo[i][k] != numeric_limits<int>::max() && grafo[k][j] != numeric_limits<int>::max()) {
                    grafo[i][j] = min(grafo[i][j], grafo[i][k] + grafo[k][j]);
                }
            }
        }
    }
}

/**
 * Imprime las distancias mínimas entre colonias calculadas con el algoritmo de Floyd-Warshall.
 * 
 * @param N Número de nodos.
 * @param grafo Matriz de distancias entre colonias.
 */
void calcularDistancias(int N, const vector<vector<int>>& grafo) {
    cout << "            Punto 01" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                cout << "Colonia " << (i + 1) << " a colonia " << (j + 1) << ": " << grafo[i][j] << endl;
            }
        }
        cout << endl;
    }
}

/**
 * Punto 2: Realizar un recorrido simple (TSP aproximado).
 * 
 * @param grafo Matriz de distancias entre las colonias.
 */
void tspAproximado(const vector<vector<int>>& grafo) {
    cout << "            Punto 02" << endl;

    int N = grafo.size();
    vector<int> recorrido;
    vector<bool> visitado(N, false);
    int costoTotal = 0;

    int actual = 0;
    visitado[actual] = true;
    recorrido.push_back(actual + 1);

    for (int i = 1; i < N; i++) {
        int siguiente = -1;
        int minDistancia = numeric_limits<int>::max();

        for (int j = 0; j < N; j++) {
            if (!visitado[j] && grafo[actual][j] < minDistancia) {
                minDistancia = grafo[actual][j];
                siguiente = j;
            }
        }

        if (siguiente != -1) {
            visitado[siguiente] = true;
            costoTotal += minDistancia;
            recorrido.push_back(siguiente + 1);
            actual = siguiente;
        }
    }

    costoTotal += grafo[actual][0];
    recorrido.push_back(1);

    cout << "El recorrido:" << endl;
    for (size_t i = 0; i < recorrido.size(); i++) {
        cout << recorrido[i];
        if (i < recorrido.size() - 1) cout << " -> ";
    }
    cout << endl;
    cout << "El costo: " << costoTotal << endl << endl;
}

/**
 * Implementación del algoritmo Edmonds-Karp para encontrar el flujo máximo.
 * 
 * @param capacidades Matriz de capacidades entre nodos.
 * @param fuente Nodo fuente.
 * @param sumidero Nodo sumidero.
 * @return El flujo máximo entre el nodo fuente y el sumidero.
 */
int edmondsKarp(const vector<vector<int>>& capacidades, int fuente, int sumidero) {
    int N = capacidades.size();
    vector<vector<int>> flujo(N, vector<int>(N, 0));
    int flujoTotal = 0;

    while (true) {
        vector<int> padre(N, -1);
        padre[fuente] = fuente;
        queue<pair<int, int>> q;
        q.push({fuente, numeric_limits<int>::max()});

        while (!q.empty()) {
            int u = q.front().first;
            int flujoActual = q.front().second;
            q.pop();

            for (int v = 0; v < N; v++) {
                if (padre[v] == -1 && capacidades[u][v] > flujo[u][v]) {
                    padre[v] = u;
                    int nuevoFlujo = min(flujoActual, capacidades[u][v] - flujo[u][v]);
                    if (v == sumidero) {
                        flujoTotal += nuevoFlujo;
                        int cur = v;

                        while (cur != fuente) {
                            int prev = padre[cur];
                            flujo[prev][cur] += nuevoFlujo;
                            flujo[cur][prev] -= nuevoFlujo;
                            cur = prev;
                        }
                        break;
                    }
                    q.push({v, nuevoFlujo});
                }
            }
        }
        if (padre[sumidero] == -1) break;
    }

    return flujoTotal;
}

/**
 * Calcula la distancia euclidiana entre dos puntos.
 * 
 * @param p1 Punto 1 con coordenadas (x, y).
 * @param p2 Punto 2 con coordenadas (x, y).
 * @return Distancia euclidiana entre p1 y p2.
 */
double calcularDistanciaEuclidiana(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

/**
 * Encuentra la central más cercana a una nueva estación.
 * 
 * @param posiciones Vector de posiciones de las estaciones.
 * @param nuevaEstacion Coordenadas de la nueva estación.
 */
void calcularMinDistancias(const vector<pair<int, int>>& posiciones, const pair<int, int>& nuevaEstacion) {
    int N = posiciones.size();
    double distanciaMinima = numeric_limits<double>::max();
    int indiceMasCercano = -1;

    for (int i = 0; i < N; i++) {
        double distancia = calcularDistanciaEuclidiana(posiciones[i], nuevaEstacion);
        if (distancia < distanciaMinima) {
            distanciaMinima = distancia;
            indiceMasCercano = i;
        }
    }

    cout << "            Punto 04" << endl;
    cout << "La central más cercana a [" << nuevaEstacion.first << ", " << nuevaEstacion.second << "] es ["
         << posiciones[indiceMasCercano].first << ", " << posiciones[indiceMasCercano].second << "] con una distancia de "
         << distanciaMinima << "." << endl;
}

/**
 * Lee los datos de entrada desde un archivo.
 * 
 * @param archivo Nombre del archivo de entrada.
 * @param N Número de nodos.
 * @param grafo Matriz de adyacencia para el grafo.
 * @param capacidades Matriz de capacidades para el grafo.
 * @param posiciones Vector de posiciones de las estaciones.
 * @param nuevaEstacion Coordenadas de la nueva estación.
 * @return Verdadero si la lectura fue exitosa, falso en caso contrario.
 */
bool leerArchivoEntrada(const string& archivo, int& N, vector<vector<int>>& grafo, 
                        vector<vector<int>>& capacidades, vector<pair<int, int>>& posiciones, 
                        pair<int, int>& nuevaEstacion) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    file >> N;

    grafo.assign(N, vector<int>(N, numeric_limits<int>::max()));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file >> grafo[i][j];
            if (i == j) grafo[i][j] = 0;
        }
    }

    capacidades.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file >> capacidades[i][j];
        }
    }

    posiciones.clear();
    for (int i = 0; i < N; i++) {
        int x, y;
        char ch;
        file >> ch >> x >> ch >> y >> ch;
        posiciones.push_back({x, y});
    }

    int x, y;
    char ch;
    file >> ch >> x >> ch >> y >> ch;
    nuevaEstacion = {x, y};

    file.close();
    return true;
}

/**
 * Función principal del programa.
 */
int main() {
    int N;
    vector<vector<int>> grafo, capacidades;
    vector<pair<int, int>> posiciones;
    pair<int, int> nuevaEstacion;

    string archivo;
    cout << "Introduce el nombre del archivo de entrada (con extensión): ";
    cin >> archivo;

    if (!leerArchivoEntrada(archivo, N, grafo, capacidades, posiciones, nuevaEstacion)) {
        return 1;
    }

    floydWarshall(N, grafo);
    calcularDistancias(N, grafo);
    tspAproximado(grafo);

    cout << "            Punto 03" << endl;
    int flujoMaximo = edmondsKarp(capacidades, 0, N-1);
    cout << "El flujo máximo: " << flujoMaximo << endl << endl;

    calcularMinDistancias(posiciones, nuevaEstacion);

    return 0;
}
