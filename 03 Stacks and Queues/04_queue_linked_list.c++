#include <iostream>
#include <stdexcept>
#include <string>

//  enqueue O(1)    dequeue O(1)       worst case dequeue without last/tail O(N)    

template<typename T>
class LinkedQueue {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& v) : value(v), next(nullptr) {}
    };

    Node* head = nullptr;  // front
    Node* tail = nullptr;  // back
    size_t count = 0;

public:
    ~LinkedQueue() {
        while (!isEmpty()) dequeue();
    }

    void enqueue(const T& value) {
        Node* node = new Node(value);
        if (isEmpty()) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        ++count;
    }

    T dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue underflow");
        Node* old = head;
        T val = old->value;
        head = head->next;
        if (!head) tail = nullptr;
        delete old;
        --count;
        return val;
    }

    bool isEmpty() const { return head == nullptr; }
    size_t size() const { return count; }

    // ✅ Iterator תומך range-based for
    class Iterator {
    private:
        Node* current;
    public:
        explicit Iterator(Node* node) : current(node) {}
        T& operator*() const { return current->value; }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

int main() 
{
    LinkedQueue<std::string> q;
    q.enqueue("to");
    q.enqueue("be");
    q.enqueue("some");

    for (auto& s : q)
        std::cout << s << " ";  // ✅ A B C
    std::cout << "\n";

    cout << q.dequeue(); << endl; // some
    
    q.enqueue("be");

    for (auto& s : q)
        std::cout << s << " ";  // ✅ B C D
    std::cout << "\n";
}