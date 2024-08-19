#include <iostream>
#include <vector>
using namespace std;

// Función para fusionar dos subarreglos
void merge(vector<double> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Subarreglos temporales
    vector<double> L(n1), R(n2);

    // Copiar datos a los subarreglos temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    // Fusionar los subarreglos temporales de nuevo en arr[l..r]
    int i = 0; // índice inicial de primer subarreglo
    int j = 0; // índice inicial de segundo subarreglo
    int k = left; // índice inicial de subarreglo fusionado

    // Orden descendente
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función principal que implementa MergeSort
void mergeSort(vector<double> &arr, int left, int right) {
    if (left < right) {
        // Encuentra el punto medio
        int mid = left + (right - left) / 2;

        // Ordenar la primera y segunda mitad
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Fusionar las mitades ordenadas
        merge(arr, left, mid, right);
    }
}

int main() {
    int N;
    cin >> N;

    vector<double> arr(N);

    // Leer los N valores
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    // Aplicar MergeSort
    mergeSort(arr, 0, N - 1);

    // Imprimir los valores ordenados de mayor a menor
    for (int i = 0; i < N; i++) {
        cout << arr[i];
        if (i < N - 1) {
            cout << ", ";
        }
    }

    return 0;
}
