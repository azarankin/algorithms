#include <iostream>
#include <vector>
using namespace std;

bool binarySearch(const vector<int>& a, int target, int lo, int hi) 
{
    //O(NlogN)
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) {
            return true;
        } else if (a[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return false;
}

int twoSumBinary(const vector<int>& a, int target) {
    int N = a.size();
    int count = 0;

    for (int i = 0; i < N; i++) {
        //int target = -a[i];
        // מחפשים את ה-target רק בצד ימין של i כדי לא לספור פעמיים
        if (binarySearch(a, target, i + 1, N - 1)) 
        {
            count++;
        }
    }

    return count;
}

int main() {
    int target = 4;
    vector<int> a = {-5, -2, -1, 0, 1, 3, 4, 6};

    int count = twoSumBinary(a, target);
    cout << "Number of 2-sum pairs: " << count << endl;

    return 0;
}
