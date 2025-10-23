#include <iostream>
#include <utility>  // std::pair
using namespace std;

inline void exch(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}



// 3-way partition function, Dijkstra 3-way partitioning
pair<int,int> partition3Way(int arr[], int lo, int hi) {
    int lt = lo;
    int gt = hi;
    int pivot = arr[lo]; // pivot
    int idx = lo;

    while (idx <= gt) {
        if (arr[idx] < pivot) {
            exch(arr, lt, idx);
            lt++;
            idx++;
        }
        else if (arr[idx] > pivot) {
            exch(arr, idx, gt);
            gt--;
        }
        else /*if (arr[idx] == pivot)*/{//equal value to pivot
            idx++;
        }
    }

    return {lt, gt}; // returning the middle range of lt...gt with pivot values, samaple: [7 5 5 5 3]
    //[ 3 | 5 5 5 | 7 ]
    //    lt      gt
}



// 3-way quicksort partitioning
void quickSort3Way(int arr[], int lo, int hi) {
    if (hi <= lo) return;

    auto [lt, gt] = partition3Way(arr, lo, hi);

    // int lt = lo;
    // int gt = hi;
    // int v = arr[lo];  // pivot
    // int i = lo;

    // while (i <= gt) {
    //     if (arr[i] < v) {
    //         exch(arr, lt, i);
    //         lt++;
    //         i++;
    //     } else if (arr[i] > v) {
    //         exch(arr, i, gt);
    //         gt--;
    //     } else { // equal
    //         i++;
    //     }
    // }

    // now:
    // arr[lo..lt-1] < v
    // arr[lt..gt]   = v
    // arr[gt+1..hi] > v
    quickSort3Way(arr, lo, lt - 1);
    quickSort3Way(arr, gt + 1, hi);
}

void shuffle(int arr[], int n) {
    srand(time(nullptr));
    for (int i = 0; i < n; i++) {
        int r = i + rand() % (n - i);
        exch(arr, i, r);
    }
}

int main() {
    const int N = 15;

    int arr[N] = {5, 3, 7, 3, 2, 9, 5, 5, 8, 3, 2, 1, 5, 0, 5};

    cout << "Before sorting: ";
    for (int i = 0; i < N; i++) cout << arr[i] << " ";
    cout << endl;

    shuffle(arr, N);
    quickSort3Way(arr, 0, N - 1);

    cout << "After sorting:  ";
    for (int i = 0; i < N; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
