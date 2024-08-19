#include <iostream>
using namespace std;

void torresDeHanoi(int n, char origen, char destino, char auxiliar) {
    // Caso base: Si solo queda un disco, se mueve directamente al destino
    if (n == 1) {
        cout << "Mueve el disco " << n << " desde " << origen << " hasta " << destino << endl;
        return;
    }

    // Divide: Mover los primeros n-1 discos de la torre origen a la torre auxiliar
    torresDeHanoi(n - 1, origen, auxiliar, destino);

    // Resuelve: Mover el disco n desde la torre origen a la torre destino
    cout << "Mueve el disco " << n << " desde " << origen << " hasta " << destino << endl;

    // Conquista: Mover los n-1 discos desde la torre auxiliar a la torre destino
    torresDeHanoi(n - 1, auxiliar, destino, origen);
}

int main() {
    int n;
    cout << "Introduce el número de discos: ";
    cin >> n;

    // Llamada a la función de las torres de Hanoi
    torresDeHanoi(n, 'A', 'C', 'B');

    return 0;
}
