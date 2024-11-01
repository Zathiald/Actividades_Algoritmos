#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

/*
 * Descripción breve del programa: 
 * Este programa resuelve el problema de coloreo de grafos.
 * Autor:  Alejandro Muñoz Shimano A01705550, Ángel Francisco García Guzmán A01704203, Samir Baidon Pardo A01705403
 * Fecha de creación/modificación: 2024-10-31
 */

// Verifica si es seguro asignar el color 'c' al vértice 'v'
bool isSafe(int vertexIndex, int color[], int colorToAssign, vector<vector<int>>& adjacencyMatrix) {
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        if (adjacencyMatrix[vertexIndex][i] && color[i] == colorToAssign) {
            return false; // Si el color ya está asignado a un vecino
        }
    }
    return true; // El color se puede asignar
}

// Función auxiliar para el coloreo de grafos
bool graphColoringUtil(int maxColors, vector<vector<int>>& adjacencyMatrix, int color[], int currentVertex) {
    // Si todos los vértices están coloreados
    if (currentVertex == adjacencyMatrix.size()) {
        return true;
    }

    // Probar todos los colores
    for (int colorToTry = 0; colorToTry < maxColors; colorToTry++) {
        if (isSafe(currentVertex, color, colorToTry, adjacencyMatrix)) {
            color[currentVertex] = colorToTry; // Asignar color

            // Recursión para el siguiente vértice
            if (graphColoringUtil(maxColors, adjacencyMatrix, color, currentVertex + 1)) {
                return true;
            }

            // Si no se pudo colorear, quitar el color
            color[currentVertex] = -1;
        }
    }
    return false; // No se pudo colorear
}

// Función principal para colorear el grafo
void graphColoring(vector<vector<int>>& adjacencyMatrix) {
    int numberOfVertices = adjacencyMatrix.size();
    int* color = new int[numberOfVertices];
    memset(color, -1, sizeof(int) * numberOfVertices); // Inicializar los colores a -1

    // Estimar un número máximo de colores
    int maxColors = numberOfVertices; // El número máximo de colores es igual al número de nodos

    if (graphColoringUtil(maxColors, adjacencyMatrix, color, 0)) {
        // Mostrar los resultados
        for (int i = 0; i < numberOfVertices; i++) {
            cout << "Vértice: " << i << ", Color asignado: " << color[i] << endl;
        }
    } else {
        cout << "No es posible asignar colores a los nodos." << endl;
    }

    delete[] color; // Liberar la memoria
}

// Función principal del programa
int main() {
    int numberOfNodes;
    cout << "Ingrese el número de nodos: ";
    cin >> numberOfNodes;

    vector<vector<int>> adjacencyMatrix(numberOfNodes, vector<int>(numberOfNodes));
    cout << "Ingrese la matriz de adyacencias (" << numberOfNodes << "x" << numberOfNodes << "):" << endl;
    for (int i = 0; i < numberOfNodes; i++) {
        for (int j = 0; j < numberOfNodes; j++) {
            cin >> adjacencyMatrix[i][j];
        }
    }

    graphColoring(adjacencyMatrix);

    return 0;
}
