#include <iostream>
#include <stdexcept>

//  add O(1)    remove - not available 

template<typename T>
class Bag {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& v, Node* n=nullptr) : value(v), next(n) {}
    };

    Node* first = nullptr;
    size_t count = 0;

public:
    Bag() = default;

    ~Bag() {
        while (first != nullptr) {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }

    void add(const T& item) {
        Node* oldFirst = first;
        first = new Node(item, oldFirst);
        ++count;
    }

    bool isEmpty() const {
        return first == nullptr;
    }

    size_t size() const {
        return count;
    }

    // ✅ Iterator פנימי
    class Iterator {
    private:
        Node* current;
    public:
        explicit Iterator(Node* node) : current(node) {}
        T& operator*() const { return current->value; }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin() const { return Iterator(first); }
    Iterator end() const { return Iterator(nullptr); }
};

int main() {
    Bag<std::string> bag;
    bag.add("apple");
    bag.add("banana");
    bag.add("cherry");

    std::cout << "Bag size: " << bag.size() << "\n";  // Bag size: 3
    std::cout << "Items in bag:\n";

    for (const auto& item : bag) {
        std::cout << " - " << item << "\n";  // cherry, banana, apple (בסדר הפוך להכנסה)
    }

    return 0;
}
