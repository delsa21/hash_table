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

        table.clear();
        table.resize(newSize, std::nullopt);
        size = newSize;
        numElements = 0;

        for (const auto& entry : oldTable) {
            if (entry.has_value() && entry->isActive) {
                insert(entry->key);
            }
        }
    }

public:
    HashTable(size_t size, CollisionResolution method)
            : size(size), numElements(0), collisionResolutionMethod(method) {
        table.resize(size, std::nullopt);
    }

    void insert(int key) {
        if (numElements >= size * 0.7) {
            rehash();
        }

        size_t index = hashFunction(key);
        size_t i = 0;

        while (table[resolveCollision(index, i)].has_value() &&
               table[resolveCollision(index, i)]->isActive) {
            i++;
        }

        table[resolveCollision(index, i)] = Entry{key, true};
        numElements++;
    }

    bool search(int key) const {
        size_t index = hashFunction(key);
        size_t i = 0;

        while (table[resolveCollision(index, i)].has_value()) {
            const auto& entry = table[resolveCollision(index, i)];
            if (entry->isActive && entry->key == key) {
                return true;
            }
            i++;
        }

        return false;
    }

    void remove(int key) {
        size_t index = hashFunction(key);
        size_t i = 0;

        while (table[resolveCollision(index, i)].has_value()) {
            auto& entry = table[resolveCollision(index, i)];
            if (entry->isActive && entry->key == key) {
                entry->isActive = false;
                numElements--;
                return;
            }
            i++;
        }

        std::cout << "Key not found: " << key << std::endl;
    }

    void display() const {
        for (size_t i = 0; i < size; ++i) {
            if (table[i].has_value() && table[i]->isActive) {
                std::cout << "[" << i << "]: " << table[i]->key << std::endl;
            } else {
                std::cout << "[" << i << "]: " << "EMPTY" << std::endl;
            }
        }
    }
};

int main() {
    HashTable hashTable(7, CollisionResolution::LINEAR_PROBING);

    hashTable.insert(13);
    hashTable.insert(18);
    hashTable.insert(6);
    hashTable.insert(21);

    hashTable.display();

    std::cout << "Searching 10: " << (hashTable.search(21) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching 100: " << (hashTable.search(100) ? "Found" : "Not Found") << std::endl;

    hashTable.remove(18);
    hashTable.display();

    return 0;
}
