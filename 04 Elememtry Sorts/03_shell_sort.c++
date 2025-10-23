
// Avg: O(N^3/2)            Best: O(NlogN)   Good: O(N^2)
// space complexity: O(1)
// not stable-sort


#include <iostream>
using namespace std;


bool less(char v, char w) {
    return v < w;
}


void exch(char a[], int i, int j) {
    char temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

bool isSorted(char a[], int N) {
    for (int i = 1; i < N; i++) {
        if (less(a[i], a[i - 1])) return false;
    }
    return true;
}


void shellSort(char a[], int N, int decreaseBy = 2) {
    int h = 1;
    // 1. calculate the spaces (Knuth sequence)
    while (h < N / decreaseBy) { // 3 < 6   7 < 6
        h = decreaseBy * h + 1;  // 3, 7, 15, 31, ...
    }

    // 2.decreasing the spaces
    while (h >= 1) {
        for (int i = h; i < N; i++) {
            for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
                exch(a, j, j - h);
            }
        }
        h = h / decreaseBy;  // decreasing the spaces   // 3, 1, 0
    }
}

void printArray(char a[], int N) {
    for (int i = 0; i < N; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}


/*
Array before sort: S O R T E X A M P L E Z
Array after sort:  A E E L M O P R S T X Z
*/

int main() {
    const int N = 12;
    char a[N] = {'S','O','R','T','E','X','A','M','P','L','E', 'Z'};

    cout << "Array before sort: ";
    printArray(a, N);

    shellSort(a, N);

    cout << "Array after sort:  ";
    printArray(a, N);

    cout << "Is sorted? " << (isSorted(a, N) ? "true" : "false") << endl;

    return 0;
}
