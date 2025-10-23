#include <iostream>
using namespace std;

// ---------- greater ----------
// Comparison function for MaxHeap.
// Returns true if i < j (i smaller than j), so heap keeps the larger element on top.
inline bool greater(int i, int j) {
    return i < j;
}

// ---------- exch ----------
// Swap two elements in the array
inline void exch(int pq[], int i, int j) {
    int temp = pq[i];
    pq[i] = pq[j];
    pq[j] = temp;
}

// ---------- sink ----------
// Bottom-up restoration of heap order
void sink(int pq[], int N, int k) {
    while (2 * k <= N) {               // while left child exists
        int j = 2 * k;
        // pick larger child for MaxHeap
        if (j < N && greater(pq[j], pq[j + 1])) j++;
        // if parent is already larger than or equal to child — stop
        if (!greater(pq[k], pq[j])) break;
        exch(pq, k, j);
        k = j;
    }
}

// ---------- heapify ----------
// Build heap using bottom-up method (O(N))
void heapify(int pq[], int N) {
    for (int k = N / 2; k >= 1; k--) {
        sink(pq, N, k);
    }
}

// ---------- heapSort ----------
// Sort using Heap Sort in-place
void heapSort(int pq[], int N) {
    heapify(pq, N);  // build max heap
    int n = N;
    while (n > 1) {
        exch(pq, 1, n--); // move max to the end
        sink(pq, n, 1);   // restore heap order
    }
}

int main() {
    const int MAX_SIZE = 20;
    // 1-based indexing for heap simplicity
    int pq[MAX_SIZE] = {0, 12, 5, 30, 22, 17, 8, 14};
    int N = 7;

    cout << "Before heap sort:\n";
    for (int i = 1; i <= N; i++) cout << pq[i] << " ";
    cout << endl;

    heapSort(pq, N);

    cout << "After heap sort:\n";
    for (int i = 1; i <= N; i++) cout << pq[i] << " ";
    cout << endl;

    return 0;
}
