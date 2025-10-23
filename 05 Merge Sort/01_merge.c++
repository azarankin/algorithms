// O(N)
// space complexity: O(N)
// stable-sort
// not In-Place

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

int main() {
    const int N = 20; 
    int aux[N]; 
    int a[N] = {1, 4, 6, 8, 10, 12, 14, 16, 2, 3, 5, 7, 9, 11, 13, 15};
    int lo = 0;
    int mid = 7;   // סוף החצי הראשון (0..7)
    int hi = 15;   // סוף החצי השני (8..15)

    cout << "לפני merge: ";
    for (int i = lo; i <= hi; i++) cout << a[i] << " ";
    cout << "\n";

    merge(a, aux, lo, mid, hi);

    cout << "אחרי merge:  ";
    for (int i = lo; i <= hi; i++) cout << a[i] << " ";
    cout << "\n";

    return 0;
}
