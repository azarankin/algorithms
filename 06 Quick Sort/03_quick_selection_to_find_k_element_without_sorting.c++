// Avg: O(N)        worst case without shuffling O(n2)
// space complaxity O(1)

#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
using namespace std;

const int N = 10;

// פונקציית החלפה
inline void exch(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Fisher–Yates shuffle
void shuffle(int arr[], int n) {
    srand(time(nullptr));
    for (int i = 0; i < n; i++) {
        int r = i + rand() % (n - i);
        exch(arr, i, r);
    }
}

// partition function (like on QuickSort)
int partition(int arr[], int lo, int hi) {
    int pivot = arr[lo];
    int i = lo + 1;
    int j = hi;

    while (true) {
        while (i <= hi && arr[i] < pivot) i++;
        while (j >= lo + 1 && arr[j] > pivot) j--;
        if (i >= j) break;
        exch(arr, i, j);
        i++;
        j--;
    }
    exch(arr, lo, j);
    return j;
}

// Quick-Select for k element detection (0-based)
int quickSelect(int arr[], int n, int k) {
    //if(k < 0 || k >= n) return INT_MIN;
    shuffle(arr, n);         // shuffle
    int lo = 0, hi = n - 1;

    while (hi > lo) {
        int j = partition(arr, lo, hi);
        if (j < k) lo = j + 1;  // +1 dissabling j
        else if (j > k) hi = j - 1; //-1 dissabling j
        else return arr[k];  // found
    }

    return arr[k];
}

int main() {
    int arr[N] = {7, 2, 9, 4, 3, 8, 1, 5, 6, 0};
    int k = 4; // (the 5th smallest element), 4 indexed

    int kth = quickSelect(arr, N, k);

    cout << "The " << k+1 << "th smallest element is: " << kth << endl;
    return 0;
}
