#include <iostream>
#include <stdexcept>

//  push O(1)    pop O(1)       (worst case on resizing O(N), resize *2 for full array and *1/2 for 1/4 array)

template<typename T, size_t Capacity>
class ArrayStack {
private:
    T data[Capacity];
    size_t topIndex = 0;

public:
    void push(const T& value) {
        if (topIndex >= Capacity) throw std::overflow_error("Stack overflow");
        data[topIndex++] = value;
    }

    T pop() {
        if (isEmpty()) throw std::underflow_error("Stack underflow");
        return data[--topIndex];
    }

    bool isEmpty() const { return topIndex == 0; }
    size_t size() const { return topIndex; }

    // ✅ Iterator תואם range-based for
    class Iterator {
    private:
        T* ptr;
    public:
        explicit Iterator(T* p) : ptr(p) {}
        T& operator*() const { return *ptr; }
        Iterator& operator++() { --ptr; return *this; }   // יורדים מלמעלה למטה
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(&data[topIndex - 1]); }
    Iterator end() { return Iterator(&data[-1]); }  // אחד לפני תחילת המערך
};

int main() {
    ArrayStack<int, 10> s;
    s.push(10);
    s.push(20);
    s.push(30);

    for (auto x : s) {
        std::cout << x << " ";   // ✅ 30 20 10
    }

    cout << "pop: " << s.pop() << endl;
    cout << "top: " << s.top() << endl;
    std::cout << "\n";
}
