
#include <iostream>
#include <vector>
using namespace std;

int threeSumCount(const vector<int>& a) 
{
    // O(N^3)
    int N = a.size();
    int count = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                if (a[i] + a[j] + a[k] == 0) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    int N;
    cin >> N;  // קולט את גודל המערך

    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];  // קולט את המספרים עצמם
    }

    int result = threeSumCount(a);
    cout << result << endl;

    return 0;
}
