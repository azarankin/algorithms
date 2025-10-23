// insert O(1)      delete max O(N)     max O(N)


#include <iostream>
using namespace std;

// ---------- insert ----------
// Insert element at the end of the array (O(1))
void insert(int pq[], int& N, int x) {
    if (N >= MAX_SIZE) {
        cout << "Priority queue is full!" << endl;
        return;
    }
    pq[N++] = x;
}

// ---------- findMaxIndex ----------
// Find the index of the maximum element (O(N))
int findMaxIndex(int pq[], int N) {
    if (N == 0) return -1;
    int maxIdx = 0;
    for (int i = 1; i < N; i++) {
        if (pq[i] > pq[maxIdx]) {
            maxIdx = i;
        }
    }
    return maxIdx;
}

// ---------- delMax ----------
// Remove and return the maximum element (O(N))
int delMax(int pq[], int& N) {
    if (N == 0) {
        cout << "Priority queue is empty!" << endl;
        return -1;
    }

    int maxIdx = findMaxIndex(pq, N);
    int maxVal = pq[maxIdx];

    // Swap max with the last element
    int temp = pq[maxIdx];
    pq[maxIdx] = pq[N - 1];
    pq[N - 1] = temp;

    // Decrease the size (effectively removing last)
    N--;

    // no need to "null" like in Java — static array, primitive type
    return maxVal;
}

// ---------- isEmpty ----------
bool isEmpty(int N) {
    return N == 0;
}

int main() {
    const int MAX_SIZE = 20;

    int pq[MAX_SIZE];  // static unordered array
    int N = 0;         // number of elements

    // Insert elements (unordered)
    insert(pq, N, 12);
    insert(pq, N, 5);
    insert(pq, N, 30);
    insert(pq, N, 22);
    insert(pq, N, 17);

    cout << "Elements in PQ (unordered): ";
    for (int i = 0; i < N; i++) cout << pq[i] << " ";
    cout << endl;

    cout << "Delete max: " << delMax(pq, N) << endl;

    cout << "Elements after delMax: ";
    for (int i = 0; i < N; i++) cout << pq[i] << " ";
    cout << endl;

    return 0;
}
