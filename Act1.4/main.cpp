#include <iostream>
#include <vector>
using namespace std;

/*
 * Descripción breve del programa:
 * Este programa implementa el algoritmo de ordenamiento MergeSort
 * para ordenar un arreglo de números en orden descendente aplicando la ideologia de Dividir y Venceras.
 *
 * Autores: Samir Baidon Pardo A01705403, Angel Francisco Garcia Guzman A01704203, Alejandro Muñoz Shimano A01705550
 * Fecha de creación/modificación: 22/08/2024
 */

// Función para fusionar dos subarreglos
void fusionarSubarreglos(vector<double> &arreglo, int indiceIzquierdo, int indiceMedio, int indiceDerecho) {
    int tamanioIzquierdo = indiceMedio - indiceIzquierdo + 1;
    int tamanioDerecho = indiceDerecho - indiceMedio;

    // Subarreglos temporales
    vector<double> subarregloIzquierdo(tamanioIzquierdo);
    vector<double> subarregloDerecho(tamanioDerecho);

    // Copiar datos a los subarreglos temporales
    for (int i = 0; i < tamanioIzquierdo; i++) {
        subarregloIzquierdo[i] = arreglo[indiceIzquierdo + i];
    }
    for (int j = 0; j < tamanioDerecho; j++) {
        subarregloDerecho[j] = arreglo[indiceMedio + 1 + j];
    }

    int i = 0; // Índice inicial del subarreglo izquierdo
    int j = 0; // Índice inicial del subarreglo derecho
    int k = indiceIzquierdo; // Índice inicial del subarreglo fusionado

    // Fusionar los subarreglos en orden descendente
    while (i < tamanioIzquierdo && j < tamanioDerecho) {
        if (subarregloIzquierdo[i] >= subarregloDerecho[j]) {
            arreglo[k] = subarregloIzquierdo[i];
            i++;
        } else {
            arreglo[k] = subarregloDerecho[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes del subarreglo izquierdo, si los hay
    while (i < tamanioIzquierdo) {
        arreglo[k] = subarregloIzquierdo[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes del subarreglo derecho, si los hay
    while (j < tamanioDerecho) {
        arreglo[k] = subarregloDerecho[j];
        j++;
        k++;
    }
}

// Función principal que implementa MergeSort
void ordenarMergeSort(vector<double> &arreglo, int indiceIzquierdo, int indiceDerecho) {
    if (indiceIzquierdo < indiceDerecho) {
        int indiceMedio = indiceIzquierdo + (indiceDerecho - indiceIzquierdo) / 2;

        // Ordenar la primera y segunda mitad
        ordenarMergeSort(arreglo, indiceIzquierdo, indiceMedio);
        ordenarMergeSort(arreglo, indiceMedio + 1, indiceDerecho);

        // Fusionar las mitades ordenadas
        fusionarSubarreglos(arreglo, indiceIzquierdo, indiceMedio, indiceDerecho);
    }
}

int main() {
    int cantidadElementos;
    cin >> cantidadElementos;

    vector<double> arreglo(cantidadElementos);

    // Leer los valores del arreglo
    for (int i = 0; i < cantidadElementos; i++) {
        cin >> arreglo[i];
    }

    // Aplicar MergeSort
    ordenarMergeSort(arreglo, 0, cantidadElementos - 1);

    // Imprimir los valores ordenados de mayor a menor
    for (int i = 0; i < cantidadElementos; i++) {
        cout << arreglo[i];
        if (i < cantidadElementos - 1) {
            cout << ", ";
        }
    }

    return 0;
}
