#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <string>

using namespace std;

/**
 * Descripción breve: Programa para resolver varios problemas relacionados con
 * las colonias y sus interacciones, como el cálculo de distancias, el flujo
 * máximo y la ubicación de la nueva central más cercana.
 * 
 * Autor(es): Samir Baidon Pardo A01705403, Alejandro Muñoz Shimano A01705550, Ángel Francisco García Guzmán A01704203
 * Fecha de creación/modificación: 05/11/2024
 */

struct Edge {
    int origen, destino, peso;
};

/**
 * Punto 1: Calcular las distancias entre colonias.
 * 
 * @param N Número de colonias.
 * @param grafo Matriz de distancias entre las colonias.
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
    vector<bool> visitado(N, false);
    vector<int> recorrido;
    int costo = 0;

    // Iniciar desde la colonia 1
    int actual = 0; // Colonia 1
    visitado[actual] = true;
    recorrido.push_back(actual + 1); // Agregar la colonia al recorrido

    for (int i = 1; i < N; i++) {
        int siguiente = -1;
        int minDistancia = numeric_limits<int>::max();

        // Encontrar la colonia no visitada más cercana
        for (int j = 0; j < N; j++) {
            if (!visitado[j] && grafo[actual][j] < minDistancia) {
                minDistancia = grafo[actual][j];
                siguiente = j;
            }
        }

        // Actualizar costos y recorrido
        if (siguiente != -1) {
            visitado[siguiente] = true;
            costo += minDistancia;
            recorrido.push_back(siguiente + 1);
            actual = siguiente; // Moverse a la siguiente colonia
        }
    }

    // Volver a la colonia inicial
    costo += grafo[actual][0]; // Regresar a la colonia inicial
    recorrido.push_back(1); // Volver a la colonia 1

    // Imprimir el recorrido y el costo
    cout << "El recorrido:" << endl;
    for (int i = 0; i < recorrido.size(); ++i) {
        cout << recorrido[i];
        if (i < recorrido.size() - 1) cout << " -> ";
    }
    cout << endl;
    cout << "El costo: " << costo << endl << endl;
}

/**
 * Punto 3: Calcular el flujo máximo usando el algoritmo de Edmonds-Karp (BFS).
 * 
 * @param capacidades Matriz de capacidades de las aristas.
 * @param fuente Nodo fuente.
 * @param sumidero Nodo sumidero.
 * @return El flujo máximo.
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
        if (padre[sumidero] == -1) break; // No hay más caminos
    }

    return flujoTotal;
}

/**
 * Punto 4: Calcular la distancia más corta entre la nueva central y la más cercana.
 * 
 * @param posiciones Lista de posiciones de las colonias.
 * @param nuevaEstacion Posición de la nueva estación.
 */
double calcularDistanciaEuclidiana(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

/**
 * Punto 4: Calcular la distancia más corta entre la nueva central y la más cercana.
 * 
 * @param posiciones Lista de posiciones de las colonias.
 * @param nuevaEstacion Posición de la nueva estación.
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
 * Función para leer el archivo de entrada.
 * 
 * @param archivo Nombre del archivo a leer.
 * @param N Número de colonias.
 * @param grafo Matriz de distancias entre las colonias.
 * @param capacidades Matriz de capacidades de las aristas.
 * @param posiciones Lista de posiciones de las colonias.
 * @param nuevaEstacion Posición de la nueva estación.
 * @return true si se pudo leer correctamente, false si hubo un error.
 */
bool leerArchivoEntrada(const string& archivo, int& N, vector<vector<int>>& grafo, 
                        vector<vector<int>>& capacidades, vector<pair<int, int>>& posiciones, 
                        pair<int, int>& nuevaEstacion) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    file >> N; // Leer número de colonias

    // Leer matriz de distancias
    grafo.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file >> grafo[i][j];
        }
    }

    // Leer matriz de capacidades
    capacidades.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file >> capacidades[i][j];
        }
    }

    // Leer posiciones de las centrales
    posiciones.clear();
    for (int i = 0; i < N; i++) {
        int x, y;
        char ch;
        file >> ch >> x >> ch >> y >> ch;
        posiciones.push_back({x, y});
    }

    // Leer posición de la nueva central
    int x, y;
    char ch;
    file >> ch >> x >> ch >> y >> ch;
    nuevaEstacion = {x, y};

    file.close();
    return true;
}

int main() {
    int N;
    vector<vector<int>> grafo, capacidades;
    vector<pair<int, int>> posiciones;
    pair<int, int> nuevaEstacion;

    // Solicitar el nombre del archivo de entrada
    string archivo;
    cout << "Introduce el nombre del archivo de entrada (con extensión): ";
    cin >> archivo;

    // Leer el archivo de entrada
    if (!leerArchivoEntrada(archivo, N, grafo, capacidades, posiciones, nuevaEstacion)) {
        return 1;
    }

    // Punto 1: Calcular las distancias entre colonias
    calcularDistancias(N, grafo);
    
    // Punto 2: Resolver el TSP
    tspAproximado(grafo);

    // Punto 3: Calcular el flujo máximo
    cout << "            Punto 03" << endl;
    int flujoMaximo = edmondsKarp(capacidades, 0, N-1); // Usar el nodo 0 como fuente y el nodo N-1 como sumidero
    cout << "El flujo máximo: " << flujoMaximo << endl << endl;

    // Punto 4: Calcular la distancia más corta para la nueva estación
    calcularMinDistancias(posiciones, nuevaEstacion);

    return 0;
}
