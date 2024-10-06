#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <tuple>

/*
 * Descripción: Programa para identificar substrings similares entre archivos de texto.
 * Autor: Samir Baidon Pardo A01705403,
 *        Angel Francisco Garcia Guzman A01704203,
 *        Alejandro Muñoz Shimano A01705550
 * Fecha de creación: 2024-10-27
 */


/**
 * @brief Lee el contenido de un archivo y lo devuelve como un string.
 * @param nombreArchivo El nombre del archivo a leer.
 * @return El contenido del archivo como un string.
 */
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

/**
 * @brief Elimina los espacios en blanco y saltos de línea de un string.
 * @param texto El texto que se va a normalizar.
 * @return El texto sin espacios en blanco ni saltos de línea.
 */
std::string normalizar(const std::string &texto) {
    std::string resultado;
    for (char c : texto) {
        if (!isspace(static_cast<unsigned char>(c))) {
            resultado += c;
        }
    }
    return resultado;
}

/**
 * @brief Busca si el código está contenido en la transmisión.
 * @param transmision El texto de la transmisión.
 * @param codigo El código que se quiere buscar.
 * @param posicionInicial Posición inicial donde se encuentra el código.
 * @param posicionFinal Posición final donde se encuentra el código.
 * @return true si el código está contenido, false de lo contrario.
 */
bool buscarCodigo(const std::string &transmision, const std::string &codigo, size_t &posicionInicial, size_t &posicionFinal) {
    size_t n = transmision.size();
    size_t m = codigo.size();

    if (m > n) {
        return false;
    }

    for (size_t i = 0; i <= n - m; ++i) {
        size_t j = 0;
        while (j < m && transmision[i + j] == codigo[j]) {
            ++j;
        }
        if (j == m) {
            posicionInicial = i;
            posicionFinal = i + m - 1;
            return true;
        }
    }
    return false;
}

/**
 * @brief Encuentra el substring común más largo entre dos transmisiones.
 * @param transmision1 Primera transmisión.
 * @param transmision2 Segunda transmisión.
 * @return Tupla con las posiciones (inicio y fin) del substring común en ambas transmisiones.
 */
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
                    finIdx1 = i - 1;
                    finIdx2 = j - 1;
                }
            }
        }
    }

    return {finIdx1 - longitudMax + 2, finIdx1 + 1, finIdx2 - longitudMax + 2, finIdx2 + 1};
}

int main() {
    std::string transmision1 = normalizar(leerArchivo("transmission1.txt"));
    std::string transmision2 = normalizar(leerArchivo("transmission2.txt"));

    std::vector<std::string> mcodes = {
        normalizar(leerArchivo("mcode1.txt")),
        normalizar(leerArchivo("mcode2.txt")),
        normalizar(leerArchivo("mcode3.txt"))
    };

    std::vector<std::string> transmisiones = {transmision1, transmision2};

    // Verificar si los códigos están en las transmisiones
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

    // Encontrar el substring común más largo
    int inicio1, fin1, inicio2, fin2;
    std::tie(inicio1, fin1, inicio2, fin2) = substringComunMasLargo(transmision1, transmision2);

    std::cout << "Transmisión 1: " << inicio1 << " " << fin1 << std::endl;
    std::cout << "Transmisión 2: " << inicio2 << " " << fin2 << std::endl;

    return 0;
}
