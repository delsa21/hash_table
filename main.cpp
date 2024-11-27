#include <iostream>
#include "HashTable.h"

using namespace std;

int main() {
    int size;
    int methodChoice;

    cout << "Introduce el tamaño de la tabla hash: ";
    cin >> size;

    cout << "Selecciona el método de resolución de colisiones:\n";
    cout << "1. Linear Probing\n";
    cout << "2. Quadratic Probing\n";
    cout << "Elige opción: ";
    cin >> methodChoice;

    CollisionResolutionMethod method = (methodChoice == 1)
                                       ? CollisionResolutionMethod::LINEAR_PROBING
                                       : CollisionResolutionMethod::QUADRATIC_PROBING;

    HashTable hashTable(size, method);

    int option, key;
    do {
        cout << "\n----- Menú -----\n";
        cout << "1. Insertar clave\n";
        cout << "2. Buscar clave\n";
        cout << "3. Eliminar clave\n";
        cout << "4. Mostrar tabla\n";
        cout << "5. Salir\n";
        cout << "Selecciona una opción: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Introduce la clave a insertar: ";
                cin >> key;
                hashTable.insert(key);
                break;

            case 2:
                cout << "Introduce la clave a buscar: ";
                cin >> key;
                if (hashTable.search(key)) {
                    cout << "La clave " << key << " está en la tabla.\n";
                } else {
                    cout << "La clave " << key << " no está en la tabla.\n";
                }
                break;

            case 3:
                cout << "Introduce la clave a eliminar: ";
                cin >> key;
                if (hashTable.remove(key)) {
                    cout << "La clave " << key << " ha sido eliminada.\n";
                } else {
                    cout << "La clave " << key << " no está en la tabla.\n";
                }
                break;

            case 4:
                hashTable.display();
                break;

            case 5:
                cout << "Saliendo\n";
                break;

            default:
                cout << "Opción no válida. Intenta nuevamente.\n";
        }
    } while (option != 5);

    return 0;
}
