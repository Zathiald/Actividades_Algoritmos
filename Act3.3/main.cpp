#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Función para resolver el problema de la mochila
int knapsack(int N, vector<int> valores, vector<int> pesos, int W) {
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    // Llenando la matriz dp
    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (pesos[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - pesos[i - 1]] + valores[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Mostrar la matriz generada
    cout << "Matriz generada:" << endl;
    for (int i = 0; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            cout << setw(4) << dp[i][w];
        }
        cout << endl;
    }

    return dp[N][W];
}

int main() {
    int N, W;
    
    cout << "Número de elementos: ";
    cin >> N;
    
    vector<int> valores(N), pesos(N);
    
    cout << "Beneficios:" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> valores[i];
    }
    
    cout << "Pesos:" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> pesos[i];
    }
    
    cout << "Peso máximo de la mochila: ";
    cin >> W;
    
    int beneficio_optimo = knapsack(N, valores, pesos, W);
    cout << "Beneficio óptimo: " << beneficio_optimo << endl;
    
    return 0;
}
