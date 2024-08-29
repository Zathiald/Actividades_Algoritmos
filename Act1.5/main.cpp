#include <iostream>
#include <vector>
#include <algorithm>

// Breve descripción del programa: 
// Este programa calcula el número mínimo de monedas necesarias para dar un cambio, utilizando el algoritmo avaro.

//Autores: Samir Baidon Pardo A01705403, Angel Francisco Garcia Guzman A01704203, Alejandro Muñoz Shimano A01705550
//Fecha de creación/modificación: 29/08/2024

int main() {
    int numDenominaciones;
    std::cin >> numDenominaciones;
    
    std::vector<int> denominaciones(numDenominaciones);
    
    // Leer las denominaciones
    for (int i = 0; i < numDenominaciones; i++) {
        std::cin >> denominaciones[i];
    }
    
    // Leer los valores de P y Q
    int p, q;
    std::cin >> p >> q;
    
    // Calcular el cambio
    int cambio = q - p;
    
    // Ordenar las denominaciones de mayor a menor
    std::sort(denominaciones.rbegin(), denominaciones.rend());
    
    // Vector para almacenar el número de monedas de cada denominación
    std::vector<int> numMonedas(numDenominaciones, 0);
    
    // Aplicar el algoritmo avaro para calcular el número de monedas de cada denominación
    for (int i = 0; i < numDenominaciones && cambio > 0; i++) {
        numMonedas[i] = cambio / denominaciones[i];
        cambio %= denominaciones[i];
    }
    
    // Imprimir el número de monedas de cada denominación
    for (int i = 0; i < numDenominaciones; i++) {
        std::cout << numMonedas[i] << std::endl;
    }
    
    return 0;
}

