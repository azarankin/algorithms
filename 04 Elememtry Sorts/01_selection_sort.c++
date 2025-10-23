
// O(N^2)
// 1/2N^2
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


// O(N)
bool isSorted(char a[], int N) {
    for (int i = 1; i < N; i++) {
        if (less(a[i], a[i - 1])) return false;
    }
    return true;
}


void selectionSort(char a[], int N) {
    for (int i = 0; i < N; i++) {
        int min = i;    //min index
        for (int j = i + 1; j < N; j++) {
            if (less(a[j], a[min])) {
                min = j;
            }
        }
        exch(a, i, min);
    }
}


void printArray(char a[], int N) {
    for (int i = 0; i < N; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}



/*
Array before sort: S O R T E X A M P L E 
Array after sort:  A E E L M O P R S T X 
*/

int main() {
    const int N = 11;
    char a[N] = {'S','O','R','T','E','X','A','M','P','L','E'};

    cout << "Array before sort: ";
    printArray(a, N);

    selectionSort(a, N);

    cout << "Array after sort:  ";
    printArray(a, N);

    cout << "Is sorted? " << (isSorted(a, N) ? "true" : "false") << endl;

    return 0;
}
