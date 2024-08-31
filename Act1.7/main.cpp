/*
 * Descripción: Programa para resolver el problema del cambio de monedas utilizando
 *              programación dinámica y algoritmos avaros.
 * Autores: Samir Baidon Pardo A01705403,
 *          Angel Francisco Garcia Guzman A01704203,
 *          Alejandro Muñoz Shimano A01705550
 * Fecha de creación/modificación: 29/08/2024
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

/**
 * @brief Resuelve el problema del cambio utilizando un algoritmo avaro.
 * @param denominaciones Un vector que contiene las denominaciones disponibles de las monedas.
 * @param cambio La cantidad de cambio a entregar.
 * @complexity O(n) donde n es el número de denominaciones.
 */
void calcularCambioAvaro(vector<int> &denominaciones, int cambio) {
    sort(denominaciones.rbegin(), denominaciones.rend()); // Ordenar las monedas de mayor a menor
    vector<int> resultado(denominaciones.size(), 0);

    for (int i = 0; i < denominaciones.size(); i++) {
        if (cambio >= denominaciones[i]) {
            resultado[i] = cambio / denominaciones[i];
            cambio -= resultado[i] * denominaciones[i];
        }
    }

    for (int i = 0; i < resultado.size(); i++) {
        cout << resultado[i] << endl;
    }
}

/**
 * @brief Resuelve el problema del cambio utilizando programación dinámica.
 * @param denominaciones Un vector que contiene las denominaciones disponibles de las monedas.
 * @param cambio La cantidad de cambio a entregar.
 * @complexity O(n * m) donde n es la cantidad de cambio y m es el número de denominaciones.
 */
void calcularCambioDinamico(vector<int> &denominaciones, int cambio) {
    sort(denominaciones.rbegin(), denominaciones.rend()); // Ordenar las monedas de mayor a menor
    vector<int> dp(cambio + 1, INT_MAX);  // dp[i] representa el número mínimo de monedas para el cambio i
    vector<int> usada(cambio + 1, -1);    // usada[i] representa la moneda utilizada para el cambio i
    dp[0] = 0;

    for (int i = 1; i <= cambio; i++) {
        for (int j = 0; j < denominaciones.size(); j++) {
            if (denominaciones[j] <= i && dp[i - denominaciones[j]] != INT_MAX) {
                if (dp[i] > dp[i - denominaciones[j]] + 1) {
                    dp[i] = dp[i - denominaciones[j]] + 1;
                    usada[i] = j;
                }
            }
        }
    }

    vector<int> resultado(denominaciones.size(), 0);
    while (cambio > 0) {
        if (usada[cambio] == -1) {
            cout << "No se puede dar cambio exacto." << endl;
            return;
        }
        resultado[usada[cambio]]++;
        cambio -= denominaciones[usada[cambio]];
    }

    for (int i = 0; i < resultado.size(); i++) {
        cout << resultado[i] << endl;
    }
}

int main() {
    int numDenominaciones;
    cin >> numDenominaciones;

    vector<int> denominaciones(numDenominaciones);
    for (int i = 0; i < numDenominaciones; i++) {
        cin >> denominaciones[i];
    }

    int precio, pago;
    cin >> precio >> pago;

    int cambio = pago - precio;

    // Imprimir resultados utilizando el algoritmo avaro
    calcularCambioAvaro(denominaciones, cambio);
    cout << endl;

    // Imprimir resultados utilizando programación dinámica
    calcularCambioDinamico(denominaciones, cambio);

    return 0;
    // Complejidad total: O(n * m)
    // Donde n es la cantidad de cambio y m es el número de denominaciones.
}
