//O(nlogn)

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
        if      (i > mid)               a[k] = aux[j++];    //copy the remain aux to a array
        else if (j > hi)                a[k] = aux[i++];    //copy the remain aux to a array
        else if (aux[j] < aux[i])       a[k] = aux[j++];
        else /*if (aux[j] > aux[i])*/   a[k] = aux[i++];
    }
}

void sort(int a[], int aux[], int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    sort(a, aux, lo, mid);
    sort(a, aux, mid + 1, hi);
    merge(a, aux, lo, mid, hi);
}

int main() {
    const int N = 7;
    int a[N] = {38, 27, 43, 3, 9, 82, 10};
    int aux[N];

    cout << "before sort: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";

    sort(a, aux, 0, n - 1);

    cout << "after sort:  ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";

    return 0;
}
