// get M, 5, most minimum values
// time: O(N log M)   not O(N log N) for sort
// space: O(M)        not O(N)

#include <iostream>
#include <climits>
using namespace std;

// ---------- less ----------
// Compare function to control heap order
inline bool less(int a, int b) {
    return a < b;
}

// ---------- swap ----------
inline void exch(int pq[], int i, int j) {
    int temp = pq[i];
    pq[i] = pq[j];
    pq[j] = temp;
}

// ---------- swim ----------
void swim(int pq[], int curr) {
    // While the current node is smaller than its parent
    while (curr > 1 && less(pq[curr], pq[curr / 2])) {
        exch(pq, curr, curr / 2);
        curr = curr / 2;  // move up to parent
    }
}

// ---------- sink ----------
void sink(int pq[], int counter, int curr) {
    while (2 * curr <= counter) {
        int j = 2 * curr;  // left child
        // choose smaller child
        if (j < counter && less(pq[j + 1], pq[j])) j++;
        if (!less(pq[j], pq[curr])) break; // if parent <= child -> stop
        exch(pq, curr, j);
        curr = j;
    }
}

// ---------- insert ----------
// O(log M)
void insert(int pq[], int& counter, int M, int x) {
    if (counter < M) {
        // insert new value normally
        pq[++counter] = x;
        swim(pq, counter);
    } else if (less(pq[1], x)) {
        // replace min with bigger value
        pq[1] = x;
        sink(pq, counter, 1);
    }
    // else: ignore value if it's not bigger than min
}

// ---------- delete the minimum ----------
// O(log M)
int delMin(int pq[], int& counter) {
    int minVal = pq[1];
    exch(pq, 1, counter--);   // remove top value
    sink(pq, counter, 1);
    return minVal;
}

int main() {
    const int M = 5;   // number of max elements to keep
    int pq[M + 1];     // MinPQ, size M

    const int N = 12;  // array elements
    int arr[N] = {12, 5, 7, 30, 22, 14, 3, 50, 17, 25, 19, 45};

    int counter = 0;   // current PQ size

    for (int i = 0; i < N; i++) {
        insert(pq, counter, M, arr[i]);
    }

    cout << "Top " << M << " max values in ascending order:\n";
    while (counter > 0) {
        cout << delMin(pq, counter) << " ";
    }
    cout << endl;

    return 0;
}
