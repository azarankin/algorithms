#include <iostream>
#include <stdexcept>
#include <string>

//  push O(1)    pop O(1)       applied with first

template<typename T>
class LinkedStack {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& v, Node* n=nullptr) : value(v), next(n) {}
    };

    Node* head = nullptr;
    size_t count = 0;

public:
    ~LinkedStack() {
        while (!isEmpty()) pop();
    }

    void push(const T& value) {
        head = new Node(value, head);
        ++count;
    }

    T pop() {
        if (isEmpty()) throw std::underflow_error("Stack underflow");
        Node* old = head;
        T val = old->value;
        head = head->next;
        delete old;
        --count;
        return val;
    }

    bool isEmpty() const { return head == nullptr; }
    size_t size() const { return count; }

    // ✅ Iterator תואם ל־range-based for
    class Iterator {
    private:
        Node* current;
    public:
        explicit Iterator(Node* node) : current(node) {}
        T& operator*() const { return current->value; }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

int main() {
    LinkedStack<std::string> s;
    s.push("to");
    s.push("be");
    s.push("or");

    for (auto& word : s) {
        std::cout << word << " ";   // ✅ or be to
    }
    cout << "pop: " << s.pop() << endl;
    cout << "top: " << s.top() << endl;
    std::cout << "\n";
}

