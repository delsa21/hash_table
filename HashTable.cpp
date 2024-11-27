#include "HashTable.h"

using namespace std;

// Constructor
HashTable::HashTable(int size, CollisionResolutionMethod method)
        : size(size), numElements(0), collisionResolutionMethod(method) {
    table.resize(size, -1);  // Inicializamos la tabla con -1 para indicar espacios vacíos
}

// Función hash simple
int HashTable::hash(int key) const {
    return key % size;
}

// Linear Probing
int HashTable::linearProbing(int hashValue, int i) const {
    return (hashValue + i) % size;
}

// Quadratic Probing
int HashTable::quadraticProbing(int hashValue, int i) const {
    return (hashValue + i * i) % size;
}

// Rehashing: duplicar el tamaño de la tabla y volver a insertar los elementos
void HashTable::rehash() {
    int oldSize = size;
    size *= 2;  // Doblamos el tamaño de la tabla
    vector<int> oldTable = table;  // Guardamos la tabla anterior
    table.clear();
    table.resize(size, -1);  // Re-inicializamos la tabla

    numElements = 0;  // Reiniciamos el contador de elementos

    // Volvemos a insertar todos los elementos en la nueva tabla
    for (int i = 0; i < oldSize; ++i) {
        if (oldTable[i] != -1) {
            insert(oldTable[i]);
        }
    }
}

// Insertar clave en la tabla
void HashTable::insert(int key) {
    if (numElements >= 0.7 * size) {
        rehash();  // Si el factor de carga es mayor o igual al 70%, hacemos rehashing
    }

    int hashValue = hash(key);

    // Buscamos el lugar adecuado dependiendo del método de resolución de colisiones
    for (int i = 0; i < size; ++i) {
        int index = (collisionResolutionMethod == CollisionResolutionMethod::LINEAR_PROBING)
                    ? linearProbing(hashValue, i)
                    : quadraticProbing(hashValue, i);

        // Si encontramos un espacio vacío o la misma clave, insertamos la clave
        if (table[index] == -1 || table[index] == key) {
            table[index] = key;
            numElements++;
            return;
        }
    }

    throw runtime_error("No se pudo insertar el elemento, la tabla está llena.");
}

// Buscar una clave
bool HashTable::search(int key) const {
    int hashValue = hash(key);

    // Buscamos la clave utilizando el método de resolución de colisiones
    for (int i = 0; i < size; ++i) {
        int index = (collisionResolutionMethod == CollisionResolutionMethod::LINEAR_PROBING)
                    ? linearProbing(hashValue, i)
                    : quadraticProbing(hashValue, i);

        if (table[index] == key) {
            return true;  // La clave ha sido encontrada
        }
        if (table[index] == -1) {
            return false;  // Hemos encontrado un espacio vacío, por lo tanto no está presente
        }
    }

    return false;  // La clave no está en la tabla
}

// Eliminar una clave
bool HashTable::remove(int key) {
    int hashValue = hash(key);

    // Buscamos la clave utilizando el método de resolución de colisiones
    for (int i = 0; i < size; ++i) {
        int index = (collisionResolutionMethod == CollisionResolutionMethod::LINEAR_PROBING)
                    ? linearProbing(hashValue, i)
                    : quadraticProbing(hashValue, i);

        if (table[index] == key) {
            table[index] = -1;  // Marcamos la posición como vacía
            numElements--;
            return true;
        }
        if (table[index] == -1) {
            return false;  // La clave no está presente
        }
    }

    return false;  // La clave no se pudo eliminar porque no está presente
}

// Mostrar la tabla
void HashTable::display() const {
    for (int i = 0; i < size; ++i) {
        if (table[i] != -1) {
            cout << "Indice " << i << ": " << table[i] << endl;
        } else {
            cout << "Indice " << i << ": (vacío)" << endl;
        }
    }
}
