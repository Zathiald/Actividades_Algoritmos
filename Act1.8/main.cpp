/*
 * Descripción: Programa para resolver un laberinto utilizando Backtracking y Ramificación y Poda.
 * Autores: Samir Baidon Pardo A01705403,
 *          Angel Francisco Garcia Guzman A01704203,
 *          Alejandro Muñoz Shimano A01705550
 * Fecha de creación/modificación: 02/09/2024
 */

#include <iostream>
#include <vector>
#include <limits> // Para manejo de errores en la entrada

using namespace std;

const int CELDA_TRANSITABLE = 1;

/**
 * Imprime la solución del laberinto.
 * Complejidad: O(n * m), donde n es el número de filas y m el número de columnas.
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
 * Complejidad: O(1) porque es una simple verificación de límites y condiciones.
 * @param x Coordenada x de la casilla.
 * @param y Coordenada y de la casilla.
 * @param laberinto Matriz que representa el laberinto.
 * @param solucion Matriz que representa la solución del laberinto.
 * @return true si es seguro moverse a la posición (x, y), false en caso contrario.
 */
bool esSeguro(int x, int y, const vector<vector<int>>& laberinto, const vector<vector<int>>& solucion) {
    int filas = laberinto.size();
    int columnas = laberinto[0].size();
    return (x >= 0 && x < filas && y >= 0 && y < columnas && laberinto[x][y] == CELDA_TRANSITABLE && solucion[x][y] == 0);
}

/**
 * Función recursiva que resuelve el laberinto utilizando Backtracking.
 * Complejidad: O(4^(n*m)), ya que en cada casilla se pueden tomar hasta 4 direcciones diferentes.
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
        solucion[x][y] = CELDA_TRANSITABLE;
        return true;
    }
    
    if (esSeguro(x, y, laberinto, solucion)) {
        solucion[x][y] = CELDA_TRANSITABLE;
        
        if (resolverLaberintoBacktracking(x + 1, y, laberinto, solucion)) return true; // Hacia adelante
        if (resolverLaberintoBacktracking(x, y + 1, laberinto, solucion)) return true; // Hacia abajo
        if (resolverLaberintoBacktracking(x - 1, y, laberinto, solucion)) return true; // Hacia atrás
        if (resolverLaberintoBacktracking(x, y - 1, laberinto, solucion)) return true; // Hacia arriba
        
        solucion[x][y] = 0; // Retrocede
    }
    
    return false;
}

/**
 * Resuelve el laberinto utilizando la técnica de Backtracking.
 * Complejidad: O(4^(n*m)), depende de la complejidad de la función recursiva resolverLaberintoBacktracking.
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
 * Complejidad: O(2^(n+m)), ya que solo se exploran las direcciones hacia adelante o hacia abajo, reduciendo las ramas posibles.
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
        solucion[x][y] = CELDA_TRANSITABLE;
        return true;
    }
    
    if (esSeguro(x, y, laberinto, solucion)) {
        solucion[x][y] = CELDA_TRANSITABLE;
        
        if (resolverLaberintoBranchAndBound(x + 1, y, laberinto, solucion)) return true; // Hacia adelante
        if (resolverLaberintoBranchAndBound(x, y + 1, laberinto, solucion)) return true; // Hacia abajo
        
        solucion[x][y] = 0; // Poda
    }
    
    return false;
}

/**
 * Resuelve el laberinto utilizando la técnica de Ramificación y Poda.
 * Complejidad: O(2^(n+m)), debido a la naturaleza de la técnica de Ramificación y Poda, que reduce las ramas exploradas.
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

/**
 * Lee los datos del laberinto desde la entrada estándar y verifica que sean correctos.
 * Complejidad: O(n * m), ya que lee una matriz completa de n filas y m columnas.
 * @param filas Cantidad de filas del laberinto.
 * @param columnas Cantidad de columnas del laberinto.
 * @return Matriz que representa el laberinto.
 */
vector<vector<int>> leerLaberinto(int filas, int columnas) {
    vector<vector<int>> laberinto(filas, vector<int>(columnas));
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            while (true) {
                cin >> laberinto[i][j];
                if (cin.fail() || laberinto[i][j] < 0 || laberinto[i][j] > 1) {
                    cin.clear(); // Limpia el error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar entrada inválida
                    cout << "Entrada inválida. Ingrese 0 o 1 para la celda [" << i << "][" << j << "]: ";
                } else {
                    break;
                }
            }
        }
    }
    
    return laberinto;
}

/**
 * Función principal del programa.
 * Complejidad total: O(4^(n*m)) debido a la utilización de la técnica de Backtracking, que tiene la mayor complejidad entre las funciones.
 */
int main() {
    int filas, columnas;
    
    // Validación de entrada para las dimensiones
    while (true) {
        cin >> filas;
        if (cin.fail() || filas <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Ingrese un entero positivo.\n";
        } else {
            break;
        }
    }
    
    while (true) {
        cin >> columnas;
        if (cin.fail() || columnas <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Ingrese un entero positivo.\n";
        } else {
            break;
        }
    }
    
    vector<vector<int>> laberinto = leerLaberinto(filas, columnas);
    
    // Resolver con Backtracking
    resolverLaberintoConBacktracking(laberinto);
    
    // Resolver con Ramificación y Poda
    resolverLaberintoConBranchAndBound(laberinto);
    
    return 0;
}
