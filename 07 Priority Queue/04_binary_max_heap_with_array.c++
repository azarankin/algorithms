#include <iostream>
using namespace std;

// ---------- greater ----------
// Compares two elements in the heap.
// For MaxHeap: return true if pq[i] < pq[j].
inline bool greater(int i, int j) {
    return i > j;
}

// ---------- exch ----------
// Swaps two elements in the heap.
inline void exch(int pq[], int i, int j) {
    int temp = pq[i];
    pq[i] = pq[j];
    pq[j] = temp;
}

// ---------- swim ----------
// Moves an element up the tree as long as it is larger than its parent.
void swim(int pq[], int curr) {
    while (curr > 1 && greater(pq[curr / 2], pq[curr])) {  // while parent is smaller than child
        exch(pq, curr, curr / 2);
        curr = curr / 2;
    }
}

// ---------- sink ----------
// Moves an element down the tree if it is smaller than its largest child.
void sink(int pq[], int counter, int curr) {
    while (2 * curr <= counter) {              // while there is at least a left child
        int child = 2 * curr;                  // left child
        if (child < counter && greater(pq[child], pq[child + 1])) child += 1;  // pick the larger child
        if (!greater(pq[curr], pq[child])) break;     // stop if parent is not smaller than the largest child
        exch(pq, curr, child);                 // swap parent with child
        curr = child;                          // continue sinking
    }
}

// ---------- insert ----------
// Inserts a new element into the heap.
void insert(int pq[], int& counter, int x) {
    pq[++counter] = x;
    swim(pq, counter);
}

// ---------- delMax ----------
// Removes and returns the largest element (at index 1).
int delMax(int pq[], int& counter) {
    int max = pq[1];
    exch(pq, 1, counter--);     // swap max with the last element and shrink heap
    sink(pq, counter, 1);       // restore heap order
    //pq[N+1] = null;  // prevent loitering in JAVA
    return max;
}

// ---------- heapify ----------
// Turns an existing array into a valid heap in O(N) time.
void heapify(int pq[], int& counter) {
    for (int k = counter / 2; k >= 1; k--) {
        sink(pq, counter, k);
    }
}

int main() {
    const int MAX_SIZE = 20;

    int pq[MAX_SIZE];   // Heap array (1-based indexing)
    int counter = 0;    // Number of elements in the heap

    // Insert elements
    insert(pq, counter, 12);
    insert(pq, counter, 5);
    insert(pq, counter, 30);
    insert(pq, counter, 22);
    insert(pq, counter, 17);

    cout << "Heap after insertions:\n";
    for (int i = 1; i <= counter; i++) cout << pq[i] << " ";
    cout << endl;

    // Remove max element
    cout << "Delete max: " << delMax(pq, counter) << endl;

    cout << "Heap after deleting max:\n";
    for (int i = 1; i <= counter; i++) cout << pq[i] << " ";
    cout << endl;

    return 0;
}
