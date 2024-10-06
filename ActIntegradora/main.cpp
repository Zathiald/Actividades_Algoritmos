#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <tuple> 

// Lee el contenido como un string
std::string leerArchivo(const std::string &nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return "";
    }
    std::string contenido((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
    archivo.close();
    return contenido;
}

// Quita los espacios en blanco y saltos de línea
std::string normalizar(const std::string &texto) {
    std::string resultado;
    for (char c : texto) {
        if (!isspace(static_cast<unsigned char>(c))) {
            resultado += c;
        }
    }
    return resultado;
}

// Busca si el codigo está contenido en la transmisión y retorna las posiciones inicial y final si lo encuentra
bool buscarCodigo(const std::string &transmision, const std::string &codigo, size_t &posicionInicial, size_t &posicionFinal) {
    size_t n = transmision.size();
    size_t m = codigo.size();

    // Si el código es más largo que la transmisión, no hay forma de que esté dentro
    if (m > n) return false;

    for (size_t i = 0; i <= n - m; ++i) {
        size_t j = 0;
        while (j < m && transmision[i + j] == codigo[j]) {
            ++j;
        }
        if (j == m) {
            posicionInicial = i;
            posicionFinal = i + m - 1;
            return true; // Se encontró una coincidencia
        }
    }
    return false; // No se encontró ninguna coincidencia
}

// Encuentra el substring común más largo entre dos transmisiones y retorna las posiciones en ambas transmisiones
std::tuple<int, int, int, int> substringComunMasLargo(const std::string &transmision1, const std::string &transmision2) {
    int n = transmision1.size();
    int m = transmision2.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    int longitudMax = 0;
    int finIdx1 = 0;
    int finIdx2 = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (transmision1[i - 1] == transmision2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > longitudMax) {
                    longitudMax = dp[i][j];
                    finIdx1 = i - 1; // Índice donde termina el substring en transmision1
                    finIdx2 = j - 1; // Índice donde termina el substring en transmision2
                }
            }
        }
    }

    return {finIdx1 - longitudMax + 2, finIdx1 + 1, finIdx2 - longitudMax + 2, finIdx2 + 1}; // Posiciones desde 1
}

int main() {
    std::string transmision1 = normalizar(leerArchivo("transmission1.txt"));
    std::string transmision2 = normalizar(leerArchivo("transmission2.txt"));

    std::vector<std::string> mcodes = {
        normalizar(leerArchivo("mcode1.txt")),
        normalizar(leerArchivo("mcode2.txt")),
        normalizar(leerArchivo("mcode3.txt"))
    };

    // Vector con las transmisiones
    std::vector<std::string> transmisiones = {transmision1, transmision2};

    // Para cada transmisión y cada código, verifica si el código está contenido en la transmisión
    for (size_t i = 0; i < transmisiones.size(); ++i) {
        for (size_t j = 0; j < mcodes.size(); ++j) {
            size_t posicionInicial = 0;
            size_t posicionFinal = 0;
            bool encontrado = buscarCodigo(transmisiones[i], mcodes[j], posicionInicial, posicionFinal);

            if (encontrado) {
                std::cout << "true (Posición inicial: " << posicionInicial 
                          << ", Posición final: " << posicionFinal << ")" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        }
    }

    // Parte 3: Encontrar el substring común más largo entre las transmisiones y las posiciones en ambas
    int inicio1, fin1, inicio2, fin2;
    std::tie(inicio1, fin1, inicio2, fin2) = substringComunMasLargo(transmision1, transmision2);

    std::cout << "Transmisión 1: " << inicio1 << " " << fin1 << std::endl;
    std::cout << "Transmisión 2: " << inicio2 << " " << fin2 << std::endl;

    return 0;
}