#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <random>
using namespace std;
using namespace std::chrono;

int threeSumCount(const vector<int>& a) {
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
    vector<int> Ns = {100, 200, 400, 800, 1600}; // גדלים לבדיקה
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-1000, 1000);

    cout << "logN\tlogT\n";

    for (int N : Ns) {
        // יצירת וקטור רנדומלי
        vector<int> a(N);
        for (int i = 0; i < N; i++) {
            a[i] = dist(gen);
        }

        // מדידת זמן הריצה
        auto start = high_resolution_clock::now();
        threeSumCount(a);
        auto end = high_resolution_clock::now();

        double elapsed_ms = duration_cast<microseconds>(end - start).count() / 1000.0;

        // לוג בבסיס 10
        double logN = log10(N);
        double logT = log10(elapsed_ms);

        cout << logN << "\t" << logT << "\n";
    }

    return 0;
}

/*
result sample
logN    logT
2.0     0.8
2.3     1.5
2.6     2.4
2.9     3.3
3.2     4.2
*/