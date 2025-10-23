#include <iostream>
#include <cstdlib>   // rand, srand
#include <ctime>     // time

using namespace std;

void exch(char arr[], int i, int j) {
    char temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


int uniform(int n) {
    return rand() % n;  // 0 ~ n-1
}

void shuffle(char arr[], int n) {
    for (int i = 0; i < n; i++) {
        int r = uniform(i + 1); // 0 ~ i
        exch(arr, i, r);
    }
}


void shuffleAllElements(char arr[], int n) {
    if(i<2) return;
    for (int i = 1; i < n; i++) {
        int r = uniform(i); // 0 ~ i-1
        exch(arr, i, r);
    }
}

void printArray(const char arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    srand(time(nullptr));  // seed

    const int N = 11;
    char a[N] = {'S','O','R','T','E','X','A','M','P','L','E'};


    cout << "Before shuffle: ";
    printArray(a, N);

    shuffle(a, N);

    cout << "After shuffle:  ";
    printArray(a, N);

    return 0;
}
