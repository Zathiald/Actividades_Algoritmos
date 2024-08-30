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

// Función que calcula el cambio utilizando un algoritmo avaro
std::vector<int> calcularCambio(int pago, int precio, const std::vector<int>& denominaciones) {
    int cambio = pago - precio;
    std::vector<int> monedasUsadas(denominaciones.size(), 0);

    if (pago > precio){
        // Recorrer las denominaciones de mayor a menor
        for (size_t i = 0; i < denominaciones.size(); ++i) {
            // Calcular cuántas monedas de esta denominación se pueden usar
            monedasUsadas[i] = cambio / denominaciones[i];
            // Reducir el cambio restante
            cambio %= denominaciones[i];
        }
    }
    else {
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
    for (int moneda : cambio) {
        std::cout << moneda << std::endl;
    }

    return 0;
}

