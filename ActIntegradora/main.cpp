#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

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

// Busca si el codigo está contenido en la transmisión
bool buscarCodigo(const std::string &transmision, const std::string &codigo) {
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
            return true; // Se encontró una coincidencia
        }
    }
    return false; // No se encontró ninguna coincidencia
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
            bool encontrado = buscarCodigo(transmisiones[i], mcodes[j]);
            if (encontrado) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        }
    }

    return 0;
}

