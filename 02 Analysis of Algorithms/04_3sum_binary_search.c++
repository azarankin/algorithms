#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool binarySearch(const vector<int>& a, int target, int lo, int hi) 
{   // O(N^2logN)
    while (lo <= hi) 
    {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return true;
        else if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}

int threeSumBinary(vector<int>& a, int target) 
{
    int N = a.size();
    int count = 0;

    sort(a.begin(), a.end());  // O(N log N) פעם אחת בלבד

    for (int i = 0; i < N; i++) 
    {
        for (int j = i + 1; j < N; j++) 
        {
            //int target = -(a[i] + a[j]);
            if (binarySearch(a, target, j + 1, N - 1)) 
            {
                count++;
            }
        }
    }

    return count;
}

int main() {
    int target =  10;
    vector<int> a = {30, -40, -20, -10, 40, 0, 10, 5}; // sort is avalable

    int count = threeSumBinary(a, target);
    cout << "Number of 3-sum triples: " << count << endl;

    return 0;
}
