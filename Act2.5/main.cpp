/*
 * Descripción: Programa para calcular todos los substrings de una cadena y mostrarlos ordenados alfabéticamente.
 * Autor: Samir Baidon Pardo A01705403,
 *        Angel Francisco Garcia Guzman A01704203,
 *        Alejandro Muñoz Shimano A01705550
 * Fecha de creación: 2024-09-27
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Complejidad: O(n^2), pues hay dos loops anidados.

// Función que genera todos los substrings de un string dado.
// @param input: Cadena de entrada para generar substrings.
// @return vector de strings con todos los substrings generados.
std::vector<std::string> generarSubstrings(const std::string &input) {
    std::vector<std::string> substrings;
    int longitud = input.length();

    // Complejidad de este bucle anidado: O(n^2)
    // El bucle externo recorre desde el primer hasta el último carácter (O(n)),
    // y el bucle interno genera substrings de todas las posibles longitudes para cada índice (O(n)).
    // Por lo tanto, la complejidad es O(n^2).
    for (int i = 0; i < longitud; ++i) {
        for (int j = 1; j <= (longitud - i); ++j) {
            substrings.push_back(input.substr(i, j));  // Complejidad de substr(): O(j) en cada iteración
        }
    }

    // El número total de substrings es O(n^2), lo que domina el costo de la operación anterior.
    return substrings;
}

// Función principal que lee un string, genera substrings, los ordena y los muestra.
// @return 0 si el programa se ejecuta correctamente.
int main() {
    std::string cadenaEntrada;
    std::cout << "Ingrese una cadena de texto: ";
    std::cin >> cadenaEntrada;

    // Complejidad: O(n^2) para generar todos los substrings.
    std::vector<std::string> substrings = generarSubstrings(cadenaEntrada);

    // Complejidad de std::sort: O(m log m), donde m es el número de substrings (O(n^2)).
    // Por lo tanto, la complejidad de ordenación es O(n^2 log n^2), que equivale a O(n^2 log n).
    std::sort(substrings.begin(), substrings.end());

    // Complejidad para imprimir los substrings: O(n^2), ya que recorremos todos los substrings generados.
    std::cout << "Substrings ordenados alfabéticamente:\n";
    for (const std::string &substring : substrings) {
        std::cout << substring << std::endl;
    }

    return 0;
}