#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int N;
    std::cin >> N;
    
    std::vector<int> denominaciones(N);
    
    // Leer las denominaciones
    for (int i = 0; i < N; i++) {
        std::cin >> denominaciones[i];
    }
    
    // Leer P y Q
    int P, Q;
    std::cin >> P >> Q;
    
    // Calcular el cambio
    int cambio = Q - P;
    
    // Ordenar las denominaciones de mayor a menor
    std::sort(denominaciones.rbegin(), denominaciones.rend());
    
    // Vector para almacenar el número de monedas de cada denominación
    std::vector<int> numMonedas(N, 0);
    
    // Aplicar el algoritmo avaro para calcular el número de monedas de cada denominación
    for (int i = 0; i < N && cambio > 0; i++) {
        numMonedas[i] = cambio / denominaciones[i];
        cambio %= denominaciones[i];
    }
    
    // Imprimir el número de monedas de cada denominación
    for (int i = 0; i < N; i++) {
        std::cout << numMonedas[i] << std::endl;
    }
    
    return 0;
}
