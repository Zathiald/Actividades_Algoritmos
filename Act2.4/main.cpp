#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

/* Descripción: Programa que genera un hash hexadecimal de un archivo de texto.
* Autor: Samir Baidon Pardo A01705403,
*          Angel Francisco Garcia Guzman A01704203,
*          Alejandro Muñoz Shimano A01705550
* Fecha de creación: 24/09/2024
*/

// Función para imprimir la matriz generada
void printMatrix(const std::vector<std::vector<char>>& matrix, int n) {
    std::cout << "Matriz generada por el algoritmo:\n";
    for (int row = 0; row < matrix.size(); ++row) {
        for (int col = 0; col < n; ++col) {
            char c = matrix[row][col];
            if (c == '[') {
                std::cout << "[ "; // Mostrar los '[' como '[ '
            } else if (c == '-') {
                std::cout << "- "; // Mostrar guiones para saltos de línea
            } else {
                std::cout << c << ' '; // Mostrar otros caracteres
            }
        }
        std::cout << '\n';
    }
}

// Función para convertir el arreglo a una representación hexadecimal
std::string toHex(const std::vector<int>& a) {
    std::ostringstream oss;
    for (int num : a) {
        oss << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << num;
    }
    return oss.str();
}

int main() {
    std::string filename;
    int n;

    std::cout << "Ingrese el nombre del archivo (ej. datos.txt): ";
    std::cin >> filename;
    std::cout << "Ingrese un entero n (multiplo de 4 entre 16 y 64): ";
    std::cin >> n;

    if (n < 16 || n > 64 || n % 4 != 0) {
        std::cerr << "El valor de n debe ser un múltiplo de 4 y estar entre 16 y 64.\n";
        return 1;
    }

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "No se pudo abrir el archivo.\n";
        return 1;
    }

    std::vector<char> characters;
    char ch;
    while (file.get(ch)) {
        characters.push_back(ch);
    }
    file.close();

    // Crear matriz
    int rows = (characters.size() + n - 1) / n; // Total de filas necesarias
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(n, '[')); // Rellenar con '[' inicialmente

    int currentIndex = 0;
    for (int i = 0; i < characters.size(); ++i) {
        if (characters[i] == '\n') {
            // Indicar el salto de línea con un guion
            matrix[currentIndex / n][currentIndex % n] = '-';
            currentIndex++;
            if (currentIndex % n == 0) { // Si al agregar el guion llegamos al final de la fila
                continue; // Saltamos para no dejar guion en el siguiente caracter
            }
        } else {
            matrix[currentIndex / n][currentIndex % n] = characters[i];
            currentIndex++;
        }
    }

    // Asegurarse de que todas las celdas vacías se llenen con '['
    for (int i = currentIndex; i < rows * n; ++i) {
        matrix[i / n][i % n] = '[';
    }

    printMatrix(matrix, n);

    // Calcular el arreglo a
    std::vector<int> a(n, 0);
    for (int col = 0; col < n; ++col) {
        for (int row = 0; row < rows; ++row) {
            char current = matrix[row][col];
            // Verificar si el carácter es imprimible y no es de relleno ni un guion
            if (current != '[' && current != '-') {
                a[col] += static_cast<unsigned char>(current); // Sumar ASCII
            }
        }
        a[col] %= 256; // Modulo 256
    }

    std::cout << "Arreglo de longitud 'n' que muestra la suma de las columnas con el modulo 256:\n";
    for (int value : a) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::string hexOutput = toHex(a);
    // Dividir la salida en grupos de 4 bytes
    std::cout << "Representación hexadecimal: ";
    for (size_t i = 0; i < hexOutput.length(); i += 8) {
        std::cout << hexOutput.substr(i, 8) << " ";
    }
    std::cout << "\n";

    return 0;
}
