#include <iostream>
using namespace std;

void merge(int a[], int aux[], int lo, int mid, int hi) {
    // copy to aux
    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        if      (i > mid)           a[k] = aux[j++]; 
        else if (j > hi)            a[k] = aux[i++];
        else if (aux[j] < aux[i])   a[k] = aux[j++];
        else                        a[k] = aux[i++];
    }
}

// Merge Sort Bottom-Up
void mergesort(int a[], int aux[]) {
    // sz = 1...2*sz...N
    for (int sz = 1; sz < N; sz = 2 * sz) {
        // lo = 0 ... lo+=sz+sz ... N - sz
        for (int lo = 0; lo < N - sz; lo += 2 * sz) {
            int mid = lo + sz - 1;
            int hi  = min(lo + 2*sz - 1, N - 1);
            merge(a, aux, lo, mid, hi);
        }
    }
}

int main() {
    const int N = 8; 
    int a[N] = {38, 27, 43, 3, 9, 82, 10, 5};
    int aux[N];

    cout << " before ordering:  ";
    for (int i = 0; i < N; i++) cout << a[i] << " ";
    cout << "\n";

    mergesort(a, aux);

    cout << "after orefdering: ";
    for (int i = 0; i < N; i++) cout << a[i] << " ";
    cout << "\n";

    return 0;
}
