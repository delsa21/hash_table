#include <iostream>
#include <vector>
#include <optional>

enum class CollisionResolution {
    LINEAR_PROBING,
    QUADRATIC_PROBING
};

class HashTable {
private:
    struct Entry {
        int key;
        bool isActive; // Marca si la entrada está activa o eliminada
    };

    std::vector<std::optional<Entry>> table;
    size_t size;
    size_t numElements;
    CollisionResolution collisionResolutionMethod;

    size_t hashFunction(int key) const {
        return key % size;
    }

    size_t resolveCollision(size_t index, int i) const {
        if (collisionResolutionMethod == CollisionResolution::LINEAR_PROBING) {
            return (index + i) % size;
        } else if (collisionResolutionMethod == CollisionResolution::QUADRATIC_PROBING) {
            return (index + i * i) % size;
        }
        return index; // No debería llegar aquí
    }

    void rehash() {
        size_t newSize = size * 2;
        std::vector<std::optional<Entry>> oldTable = table;


int main() {




    hashTable.display();

    return 0;
}
