/*
 * Descripción: Programa para calcular todos los substrings de una cadena y mostrarlos ordenados alfabéticamente.
 * Autor: Samir Baidon Pardo A01705403,
*          Angel Francisco Garcia Guzman A01704203,
*          Alejandro Muñoz Shimano A01705550
 * Fecha de creación: 2024-09-27
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Función que genera todos los substrings de un string dado.
// @param input: Cadena de entrada para generar substrings.
// @return vector de strings con todos los substrings generados.
std::vector<std::string> generarSubstrings(const std::string &input) {
    std::vector<std::string> substrings;
    int longitud = input.length();

    for (int i = 0; i < longitud; ++i) {
        for (int j = 1; j <= (longitud - i); ++j) {
            substrings.push_back(input.substr(i, j));
        }
    }
    return substrings;
}

// Función principal que lee un string, genera substrings, los ordena y los muestra.
// @return 0 si el programa se ejecuta correctamente.
int main() {
    std::string cadenaEntrada;
    std::cout << "Ingrese una cadena de texto: ";
    std::cin >> cadenaEntrada;

    std::vector<std::string> substrings = generarSubstrings(cadenaEntrada);

    // Ordenar el vector de substrings alfabéticamente.
    std::sort(substrings.begin(), substrings.end());

    std::cout << "Substrings ordenados alfabéticamente:\n";
    for (const std::string &substring : substrings) {
        std::cout << substring << std::endl;
    }

    return 0;
}
