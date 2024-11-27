#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <iostream>
#include <stdexcept>

// Enum para los métodos de resolución de colisiones
enum class CollisionResolutionMethod {
    LINEAR_PROBING,
    QUADRATIC_PROBING
};

// Clase HashTable
class HashTable {
public:
    // Constructor que recibe el tamaño de la tabla y el método de resolución de colisiones
    HashTable(int size, CollisionResolutionMethod method);

    // Método para insertar una clave
    void insert(int key);

    // Método para buscar una clave
    bool search(int key) const;

    // Método para eliminar una clave
    bool remove(int key);

    // Mostrar la tabla para ver los elementos
    void display() const;

private:
    // Atributos de la tabla hash
    int size;  // Tamaño de la tabla
    int numElements;  // Número de elementos insertados
    std::vector<int> table;  // La tabla hash (con valores -1 representando espacios vacíos)

    CollisionResolutionMethod collisionResolutionMethod;  // Método de resolución de colisiones

    // Función hash simple
    int hash(int key) const;

    // Métodos de resolución de colisiones
    int linearProbing(int hashValue, int i) const;
    int quadraticProbing(int hashValue, int i) const;

    // Método para expandir la tabla cuando el factor de carga sea demasiado alto
    void rehash();
};

#endif // HASHTABLE_H
