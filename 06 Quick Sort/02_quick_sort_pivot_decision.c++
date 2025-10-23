#include <iostream>
using namespace std;

const int CUTOFF = 3; // for short arrays


// swap function
inline void exch(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// pivot selection with median-of-3
int medianOf3(int arr[], int lo, int hi) {
    int mid = lo + (hi - lo) / 2;

    // sorting the low mid and high values- lo, mid, hi
    if (arr[mid] < arr[lo]) exch(arr, lo, mid);
    if (arr[hi] < arr[lo]) exch(arr, lo, hi);
    if (arr[hi] < arr[mid]) exch(arr, mid, hi);

    // swap the mid, new pivot to the lo
    exch(arr, lo, mid);
    return arr[lo];
}

// partition function
int partition(int arr[], int lo, int hi) {
    int pivot = medianOf3(arr, lo, hi); //swap the middle value to the first element
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

    exch(arr, lo, j); // return to pivot to it place
    return j;
}


// insertion sort
void insertionSort(int arr[], int lo, int hi) {
    for (int i = lo + 1; i <= hi; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= lo && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void shuffle(int arr[], int n) {
    srand(time(nullptr));  //seed
    for (int i = 0; i < n; i++) {
        int r = i + rand() % (n - i); // r = i ~ n-1
        int temp = arr[i];
        arr[i] = arr[r];
        arr[r] = temp;
    }
}

// no in production
bool isSorted(int arr[], int lo, int hi) {
    for (int i = lo + 1; i <= hi; i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

// QuickSort recursion
void quickSort(int arr[], int lo, int hi) {
    //if (hi <= lo) return;
    
    // cutoff for small arrays
    if (hi <= lo + CUTOFF) {
        insertionSort(arr, lo, hi);
        return;
    }

    //shuffle(arr + lo, hi - lo + 1); //shuffle the sub array
    int p = partition(arr, lo, hi);
    quickSort(arr, lo, p - 1);
    quickSort(arr, p + 1, hi);
    // assert(isSorted(arr, lo, hi));
}


int main() {ֿ
    const int N = 10;
    int arr[N] = {7, 2, 9, 4, 3, 8, 1, 5, 6, 0};

    // duplicate keys
    //const int N = 15;
    //int arr[N] = {5, 3, 7, 3, 2, 9, 5, 5, 8, 3, 2, 1, 5, 0, 5};


    shuffle(arr, N);

    cout << "Before sorting: ";
    for (int i = 0; i < N; i++) cout << arr[i] << " ";
    cout << endl;

    quickSort(arr, 0, N - 1);

    cout << "After sorting:  ";
    for (int i = 0; i < N; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
