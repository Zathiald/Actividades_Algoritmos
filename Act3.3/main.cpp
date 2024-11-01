#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

/*
 * Descripción breve del programa: 
 * Este programa resuelve el problema de la mochila utilizando programación dinámica.
 * Autor: Alejandro Muñoz Shimano A01705550, Ángel Francisco García Guzmán A01704203, Samir Baidon Pardo A01705403
 * Fecha de creación/modificación: 2024-10-31
 */

// Función para resolver el problema de la mochila
int knapsack(int numberOfItems, vector<int> itemValues, vector<int> itemWeights, int maxWeight) {
    vector<vector<int>> dp(numberOfItems + 1, vector<int>(maxWeight + 1, 0));

    // Llenando la matriz dp
    for (int i = 1; i <= numberOfItems; ++i) {
        for (int weight = 0; weight <= maxWeight; ++weight) {
            if (itemWeights[i - 1] <= weight) {
                dp[i][weight] = max(dp[i - 1][weight], dp[i - 1][weight - itemWeights[i - 1]] + itemValues[i - 1]);
            } else {
                dp[i][weight] = dp[i - 1][weight];
            }
        }
    }

    // Mostrar la matriz generada
    cout << "Matriz generada:" << endl;
    for (int i = 0; i <= numberOfItems; ++i) {
        for (int weight = 0; weight <= maxWeight; ++weight) {
            cout << setw(4) << dp[i][weight];
        }
        cout << endl;
    }

    return dp[numberOfItems][maxWeight];
}

// Función principal del programa
int main() {
    int numberOfItems, maxWeight;
    
    cout << "Número de elementos: ";
    cin >> numberOfItems;
    
    vector<int> itemValues(numberOfItems), itemWeights(numberOfItems);
    
    cout << "Beneficios:" << endl;
    for (int i = 0; i < numberOfItems; ++i) {
        cin >> itemValues[i];
    }
    
    cout << "Pesos:" << endl;
    for (int i = 0; i < numberOfItems; ++i) {
        cin >> itemWeights[i];
    }
    
    cout << "Peso máximo de la mochila: ";
    cin >> maxWeight;
    
    int optimalBenefit = knapsack(numberOfItems, itemValues, itemWeights, maxWeight);
    cout << "Beneficio óptimo: " << optimalBenefit << endl;
    
    return 0;
}
