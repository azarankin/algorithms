
// O(N lg N)            wort case for ordered array O(N^3)
ֿ// 1.39N lg N
// space complexity: O(log n)           worst case for bad pivot O(n)

#include <iostream>
using namespace std;



void exch(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
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
// int partition(int arr[], int lo, int hi) {
//     const int pivotIdx = lo;   // 1st element for the pivot
//     int pivot = arr[pivotIdx];
//     int i = pivotIdx + 1;
//     int j = hi;

//     while (true) {
//         while (i <= hi && arr[i] < pivot) i++;
//         while (j >= lo + 1 && arr[j] > pivot) j--;

//         if (i >= j) break;
//         exch(arr, i, j);
//         i++;
//         j--;
//     }
//     int newPivotIdx = j;//because it crossed with i     if (i >= j) break;
//         //or i-1
//     exch(arr, pivotIdx, newPivotIdx);
//     return j;
// }


// QuickSort recursion
void quickSort(int arr[], int lo, int hi) {
    if (hi <= lo) return;
    int p = partition(arr, lo, hi);
    quickSort(arr, lo, p - 1);     // each call is O(log n) space, log n times for O(1) function: 1/2 1/4 1/8 1/16
    quickSort(arr, p + 1, hi);
}

int main() {
    const int N = 10;
    int arr[N] = {7, 2, 9, 4, 3, 8, 1, 5, 6, 0};

    cout << "Before sorting: ";
    for (int i = 0; i < N; i++) cout << arr[i] << " ";
    cout << endl;

    quickSort(arr, 0, N - 1);

    cout << "After sorting:  ";
    for (int i = 0; i < N; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}



/*
spacer order sample:

quickSort(0,7)
 ├─ quickSort(0,3)
 │   ├─ quickSort(0,1)
 │   │   ├─ quickSort(0,0)
 │   │   └─ quickSort(2,1)
 │   └─ quickSort(2,3)
 └─ quickSort(5,7)
     ├─ ...

*/