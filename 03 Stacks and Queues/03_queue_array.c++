#include <iostream>
#include <stdexcept>

//  enqueue O(1)    dequeue O(1)       (worst case on resizing O(N), resize *2 for full array and *1/2 for 1/4 array)

template<typename T, size_t Capacity>
class ArrayQueue {
private:
    T data[Capacity];
    size_t head = 0;   // מיקום של ה־front
    size_t tail = 0;   // מיקום ההכנסה הבא
    size_t count = 0;  // כמות איברים בפועל

public:
    void enqueue(const T& value) {
        if (count == Capacity) throw std::overflow_error("Queue overflow");
        data[tail] = value;
        tail = (tail + 1) % Capacity;
        ++count;
    }

    T dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue underflow");
        T val = data[head];
        head = (head + 1) % Capacity;
        --count;
        return val;
    }

    bool isEmpty() const { return count == 0; }
    size_t size() const { return count; }

    // ✅ Iterator תומך range-based for
    class Iterator {
    private:
        const ArrayQueue* q;
        size_t idx;
        size_t remaining;
    public:
        Iterator(const ArrayQueue* queue, size_t start, size_t n)
            : q(queue), idx(start), remaining(n) {}
        T operator*() const { return q->data[idx]; }
        Iterator& operator++() {
            idx = (idx + 1) % Capacity;
            --remaining;
            return *this;
        }
        bool operator!=(const Iterator& other) const { return remaining != other.remaining; }
    };

    Iterator begin() const { return Iterator(this, head, count); }
    Iterator end() const { return Iterator(this, tail, 0); }
};

int main() 
{
    ArrayQueue<int, 5> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    for (auto x : q)
        std::cout << x << " ";  // ✅ 10 20 30
    std::cout << "\n";

    cout << q.dequeue() << endl; // 10
    
    q.enqueue(40);

    for (auto x : q)
        std::cout << x << " ";  // ✅ 20 30 40
    std::cout << "\n";
}