/*
 * Descripción: Programa para resolver un laberinto utilizando Backtracking y Ramificación y Poda.
 * Autores: Samir Baidon Pardo A01705403,
 *              Angel Francisco Garcia Guzman A01704203,
 *              Alejandro Muñoz Shimano A01705550
 * Fecha de creación/modificación: 02/09/2024
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * Imprime la solución del laberinto.
 * @param solucion Matriz que representa la solución del laberinto.
 */
void imprimirSolucion(const vector<vector<int>>& solucion) {
    for (const auto& fila : solucion) {
        for (int valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }
}

/**
 * Verifica si es seguro moverse a la posición (x, y) en el laberinto.
 * @param x Coordenada x de la casilla.
 * @param y Coordenada y de la casilla.
 * @param laberinto Matriz que representa el laberinto.
 * @param solucion Matriz que representa la solución del laberinto.
 * @return true si es seguro moverse a la posición (x, y), false en caso contrario.
 */
bool esSeguro(int x, int y, const vector<vector<int>>& laberinto, const vector<vector<int>>& solucion) {
    int filas = laberinto.size();
    int columnas = laberinto[0].size();
    return (x >= 0 && x < filas && y >= 0 && y < columnas && laberinto[x][y] == 1 && solucion[x][y] == 0);
}

/**
 * Función recursiva que resuelve el laberinto utilizando Backtracking.
 * @param x Coordenada x de la casilla actual.
 * @param y Coordenada y de la casilla actual.
 * @param laberinto Matriz que representa el laberinto.
 * @param solucion Matriz que representa la solución del laberinto.
 * @return true si se encuentra una solución, false en caso contrario.
 */
bool resolverLaberintoBacktracking(int x, int y, const vector<vector<int>>& laberinto, vector<vector<int>>& solucion) {
    int filas = laberinto.size();
    int columnas = laberinto[0].size();
    
    if (x == filas - 1 && y == columnas - 1) {
        solucion[x][y] = 1;
        return true;
    }
    
    if (esSeguro(x, y, laberinto, solucion)) {
        solucion[x][y] = 1;
        
        if (resolverLaberintoBacktracking(x + 1, y, laberinto, solucion)) return true;
        if (resolverLaberintoBacktracking(x, y + 1, laberinto, solucion)) return true;
        if (resolverLaberintoBacktracking(x - 1, y, laberinto, solucion)) return true;
        if (resolverLaberintoBacktracking(x, y - 1, laberinto, solucion)) return true;
        
        solucion[x][y] = 0; // Retrocede
    }
    
    return false;
}

/**
 * Resuelve el laberinto utilizando la técnica de Backtracking.
 * @param laberinto Matriz que representa el laberinto.
 * @return true si se encuentra una solución, false en caso contrario.
 */
bool resolverLaberintoConBacktracking(const vector<vector<int>>& laberinto) {
    int filas = laberinto.size();
    int columnas = laberinto[0].size();
    vector<vector<int>> solucion(filas, vector<int>(columnas, 0));
    
    if (!resolverLaberintoBacktracking(0, 0, laberinto, solucion)) {
        cout << "No se encontró solución utilizando Backtracking.\n";
        return false;
    }
    
    cout << "Backtracking\n";
    imprimirSolucion(solucion);
    return true;
}

/**
 * Función recursiva que resuelve el laberinto utilizando Ramificación y Poda.
 * @param x Coordenada x de la casilla actual.
 * @param y Coordenada y de la casilla actual.
 * @param laberinto Matriz que representa el laberinto.
 * @param solucion Matriz que representa la solución del laberinto.
 * @return true si se encuentra una solución, false en caso contrario.
 */
bool resolverLaberintoBranchAndBound(int x, int y, const vector<vector<int>>& laberinto, vector<vector<int>>& solucion) {
    int filas = laberinto.size();
    int columnas = laberinto[0].size();
    
    if (x == filas - 1 && y == columnas - 1) {
        solucion[x][y] = 1;
        return true;
    }
    
    if (esSeguro(x, y, laberinto, solucion)) {
        solucion[x][y] = 1;
        
        if (resolverLaberintoBranchAndBound(x + 1, y, laberinto, solucion)) return true;
        if (resolverLaberintoBranchAndBound(x, y + 1, laberinto, solucion)) return true;
        
        solucion[x][y] = 0; // Poda
    }
    
    return false;
}

/**
 * Resuelve el laberinto utilizando la técnica de Ramificación y Poda.
 * @param laberinto Matriz que representa el laberinto.
 * @return true si se encuentra una solución, false en caso contrario.
 */
bool resolverLaberintoConBranchAndBound(const vector<vector<int>>& laberinto) {
    int filas = laberinto.size();
    int columnas = laberinto[0].size();
    vector<vector<int>> solucion(filas, vector<int>(columnas, 0));
    
    if (!resolverLaberintoBranchAndBound(0, 0, laberinto, solucion)) {
        cout << "No se encontró solución utilizando Ramificación y Poda.\n";
        return false;
    }
    
    cout << "Ramificación y Poda\n";
    imprimirSolucion(solucion);
    return true;
}

int main() {
    int filas, columnas;
    cin >> filas >> columnas;
    
    vector<vector<int>> laberinto(filas, vector<int>(columnas));
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cin >> laberinto[i][j];
        }
    }
    
    cout << "Laberinto inicial:\n";
    imprimirSolucion(laberinto);
    
    cout << endl;
    
    resolverLaberintoConBacktracking(laberinto);
    
    cout << endl;
    
    resolverLaberintoConBranchAndBound(laberinto);
    
    return 0;
}
