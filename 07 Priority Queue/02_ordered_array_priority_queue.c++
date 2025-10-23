// insert O(N)      delete max O(1)     max O(1)


#include <iostream>
using namespace std;

const int MAX_SIZE = 20;

// ---------- insert (sorted) ----------
// Insert element into a sorted array (descending order)
void insert(int pq[], int& N, int x) {
    if (N >= MAX_SIZE) {
        cout << "Priority queue is full!" << endl;
        return;
    }

    int i = N - 1;
    // shift elements that are smaller than x
    while (i >= 0 && pq[i] < x) {
        pq[i + 1] = pq[i];
        i--;
    }
    pq[i + 1] = x;
    N++;
}

// ---------- delMax ----------
// Remove and return the maximum element (at index 0) in O(1)
int delMax(int pq[], int& N) {
    if (N == 0) {
        cout << "Priority queue is empty!" << endl;
        return -1;
    }

    int maxVal = pq[0];

    // shift elements left by 1
    for (int i = 1; i < N; i++) {
        pq[i - 1] = pq[i];
    }
    N--;

    return maxVal;
}

// ---------- isEmpty ----------
bool isEmpty(int N) {
    return N == 0;
}

int main() {
    int pq[MAX_SIZE];
    int N = 0;

    // Insert elements (kept sorted descending)
    insert(pq, N, 12);
    insert(pq, N, 5);
    insert(pq, N, 30);
    insert(pq, N, 22);
    insert(pq, N, 17);

    cout << "Elements in PQ (sorted descending): ";
    for (int i = 0; i < N; i++) cout << pq[i] << " ";
    cout << endl;

    cout << "Delete max: " << delMax(pq, N) << endl;

    cout << "Elements after delMax: ";
    for (int i = 0; i < N; i++) cout << pq[i] << " ";
    cout << endl;

    return 0;
}
