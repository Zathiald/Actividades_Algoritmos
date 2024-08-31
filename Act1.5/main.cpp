/*
 * Descripción: Programa que calcula la distribución de monedas de cambio
 *              utilizando un algoritmo avaro.
 * Autores: Samir Baidon Pardo A01705403,
 *              Angel Francisco Garcia Guzman A01704203,
 *              Alejandro Muñoz Shimano A01705550
 * Fecha de creación/modificación: 22/08/2024
 */

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief Calcula el cambio utilizando un algoritmo avaro.
 * @param pago La cantidad de dinero dada por el cliente.
 * @param precio El precio del producto.
 * @param denominaciones Un vector que contiene las denominaciones de las monedas disponibles.
 * @return Un vector con el número de monedas utilizadas de cada denominación.
 * @complexity O(n) donde n es el número de denominaciones.
 */
std::vector<int> calcularCambio(int pago, int precio, const std::vector<int>& denominaciones) {
    int cambio = pago - precio;
    std::vector<int> monedasUsadas(denominaciones.size(), 0);

    if (pago > precio) {
        // Recorrer las denominaciones de mayor a menor
        for (size_t i = 0; i < denominaciones.size(); ++i) {
            // Calcular cuántas monedas de esta denominación se pueden usar
            monedasUsadas[i] = cambio / denominaciones[i];
            // Reducir el cambio restante
            cambio %= denominaciones[i];
        }
    } else {
        std::cout << "No se pago el producto completo\n";
    }

    return monedasUsadas;
}

int main() {
    int numeroDenominaciones;
    std::cin >> numeroDenominaciones;

    std::vector<int> denominaciones(numeroDenominaciones);

    // Leer las denominaciones de las monedas
    for (int i = 0; i < numeroDenominaciones; ++i) {
        std::cin >> denominaciones[i];
    }

    int precio, pago;
    std::cin >> precio >> pago;

    // Ordenar las denominaciones en orden descendente
    std::sort(denominaciones.begin(), denominaciones.end(), std::greater<int>());

    // Calcular el cambio
    std::vector<int> cambio = calcularCambio(pago, precio, denominaciones);

    // Imprimir el número de monedas de cada denominación utilizadas
    std::cout << "Cambio dado:\n";
    for (size_t i = 0; i < cambio.size(); ++i) {
        if (cambio[i] > 0) {
            std::cout << cambio[i] << " moneda(s) de " << denominaciones[i] << "\n";
        }
    }

    return 0;
    // Complejidad total: O(n log n)
    // Donde n es el número de denominaciones.
}
