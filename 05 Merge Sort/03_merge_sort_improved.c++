//O(n⋅k)       = O(N) if the input is ordered       worst case: O(n log n)


#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
using namespace std;

const int CUTOFF = 3;  // cutoff for using insertion sort

// Check if subarray is sorted according to comparator
// Not for production
template<typename T, typename Compare>
bool isSorted(const vector<T>& a, int lo, int hi, Compare comp) {
    for (int i = lo + 1; i <= hi; i++) {
        if (comp(a[i], a[i - 1])) return false;
    }
    return true;
}


// insertion sort for small cutoff
template<typename T, typename Compare>
void insertionSort(vector<T>& a, int lo, int hi, Compare comp) {
    for (int i = lo + 1; i <= hi; i++) {
        T v = a[i];
        int j = i;
        while (j > lo && comp(v, a[j - 1])) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
    }
}

// merge קלאסי
template<typename T, typename Compare>
void merge(vector<T>& a, vector<T>& aux, int lo, int mid, int hi, Compare comp) {
    //assert(isSorted(a, lo, mid, comp));     // Left half sorted
    //assert(isSorted(a, mid + 1, hi, comp)); // Right half sorted

    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        if      (i > mid)             a[k] = aux[j++];
        else if (j > hi)              a[k] = aux[i++];
        else if (comp(aux[j], aux[i])) a[k] = aux[j++];
        else                           a[k] = aux[i++];
    }

    assert(isSorted(a, lo, hi, comp)); // Verify merged range is sorted
}


template<typename T, typename Compare>
void sort(vector<T>& a, vector<T>& aux, int lo, int hi, Compare comp) {
    if (hi <= lo + CUTOFF - 1) {    // sort with cutoff
        insertionSort(a, lo, hi, comp);
        return;
    }

    int mid = lo + (hi - lo) / 2;
    sort(a, aux, lo, mid, comp);
    sort(a, aux, mid + 1, hi, comp);

    // improvement: if the array is ordered
    if (!comp(a[mid + 1], a[mid])) return;

    merge(a, aux, lo, mid, hi, comp);
    //assert(isSorted(a, lo, hi, comp));    //too global
}

template<typename T, typename Compare>
void mergesort(vector<T>& a, Compare comp) {
    vector<T> aux(a.size());
    sort(a, aux, 0, a.size() - 1, comp);
    //assert(isSorted(a, 0, a.size() - 1, comp));    //too global
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    auto comp = [](int x, int y) { return x < y; };
    mergesort(arr, comp);

    cout << "Sorted ascending: ";
    for (auto x : arr) cout << x << " ";
    cout << "\n";

    auto comp2 =[](int x, int y) { return x > y; };
    vector<int> arr2 = {38, 27, 43, 3, 9, 82, 10};
    mergesort(arr2, comp2);

    cout << "Sorted descending: ";
    for (auto x : arr2) cout << x << " ";
    cout << "\n";

    return 0;
}
