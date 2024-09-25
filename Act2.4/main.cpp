#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

/* Descripción: Programa que genera un hash hexadecimal de un archivo de texto.
* Autor: Samir Baidon Pardo A01705403,
*          Angel Francisco Garcia Guzman A01704203,
*          Alejandro Muñoz Shimano A01705550
* Fecha de creación: 24/09/2024
*/

void printMatrix(const std::vector<std::vector<char>>& matrix) {
    std::cout << "Matriz generada por el algoritmo:\n";
    for (const auto& row : matrix) {
        for (char c : row) {
            if (c == '\0') {
                std::cout << ' ' << ' '; // Espacio vacío
            } else if (c == '\n') {
                std::cout << "- "; // Representación de salto de línea
            } else {
                std::cout << c << ' ';
            }
        }
        std::cout << '\n';
    }
}

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
    int rows = (characters.size() + n - 1) / n; // Total de filas
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(n, '\0'));

    for (int i = 0; i < characters.size(); ++i) {
        matrix[i / n][i % n] = characters[i];
    }

    // Rellenar el último renglón si es necesario
    if (characters.size() % n != 0) {
        for (int i = characters.size() % n; i < n; ++i) {
            matrix[rows - 1][i] = '['; // Rellenar con '['
        }
    }

    printMatrix(matrix);

    // Calcular el arreglo a
    std::vector<int> a(n, 0);
    for (int col = 0; col < n; ++col) {
        for (int row = 0; row < rows; ++row) {
            a[col] += (unsigned char)matrix[row][col]; // Sumar ASCII
        }
        a[col] %= 256; // Modulo 256
    }

    std::cout << "Arreglo de longitud 'n' que muestra la suma de las columnas con el modulo 256:\n";
    for (int value : a) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::string hexOutput = toHex(a);
    std::cout << "Representación hexadecimal: " << hexOutput << "\n";
    std::cout << "Longitud de la cadena de salida: " << hexOutput.length() / 2 << "\n"; // Cada dos dígitos representa un byte

    return 0;
}
