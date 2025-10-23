#include <bits/stdc++.h>
using namespace std;

/*** ---------- Quick-Union with Weighted + Path Compression ---------- ***/
  // Weighted + Path Compression
struct Node {
    int parent;
    int size;
};

class QuickUnionUF {
private:
    Node* tree;
    int N;

public:
    explicit QuickUnionUF(int n) : N(n) {
        tree = new Node[N];
        for (int i = 0; i < N; i++) {
            tree[i].parent = i;
            tree[i].size = 1;
        }
    }

    ~QuickUnionUF() { delete[] tree; }

    int find(int x) {
        // one-pass compression (halving)
        while (x != tree[x].parent) {
            tree[x].parent = tree[tree[x].parent].parent;
            x = tree[x].parent;
        }
        return x;
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) return;

        // weighting — חבר את העץ הקטן לגדול
        if (tree[rootA].size < tree[rootB].size) {
            tree[rootA].parent = rootB;
            tree[rootB].size += tree[rootA].size;
        } else {
            tree[rootB].parent = rootA;
            tree[rootA].size += tree[rootB].size;
        }
    }
};



/*** ---------- Percolation Simulation ---------- ***/
inline int idx(int r, int c, int N) {
    return r * N + c;
}

/*** ---------- percolates function ---------- ***/
bool percolates(int N, const vector<vector<bool>>& open) 
{
    int top = N * N;
    int bottom = N * N + 1;
    QuickUnionUF uf(N * N + 2);

    // חיבור השורה העליונה ל-top
    for (int c = 0; c < N; ++c)
        if (open[0][c])
            uf.unite(top, idx(0, c, N));

    // חיבור השורה התחתונה ל-bottom
    for (int c = 0; c < N; ++c)
        if (open[N - 1][c])
            uf.unite(bottom, idx(N - 1, c, N));

    static const int dr[4] = {-1, 1, 0, 0};
    static const int dc[4] = {0, 0, -1, 1};

    // חיבור תאים פתוחים לשכניהם
    for (int r = 0; r < N; ++r) 
    {
        for (int c = 0; c < N; ++c) {
            if (!open[r][c]) continue;
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N && open[nr][nc])
                    uf.unite(idx(r, c, N), idx(nr, nc, N));
            }
        }
    }

    return uf.connected(top, bottom);
}


/*** ---------- Monte Carlo Simulation ---------- ***/
double run_one_trial(int N, mt19937& rng) {
    vector<vector<bool>> open(N, vector<bool>(N, false));

    vector<pair<int, int>> cells;
    cells.reserve(N * N);
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            cells.emplace_back(r, c);

    shuffle(cells.begin(), cells.end(), rng);

    int opened = 0;
    for (auto [r, c] : cells) {
        open[r][c] = true;
        opened++;
        if (percolates(N, open)) {
            return double(opened) / (N * N);
        }
    }
    return 1.0;
}




int main(int argc, char** argv) {
    int N = 20;    // גודל הרשת
    int T = 100;   // מספר ניסויים
    if (argc >= 2) N = atoi(argv[1]);
    if (argc >= 3) T = atoi(argv[2]);

    mt19937 rng(random_device{}());
    vector<double> results;
    for (int t = 0; t < T; ++t) {
        results.push_back(run_one_trial(N, rng));
    }

    double mean = accumulate(results.begin(), results.end(), 0.0) / T;
    double var = 0.0;
    for (double x : results) var += (x - mean) * (x - mean);
    double stdev = sqrt(var / (T - 1));
    double ci = 1.96 * stdev / sqrt(T);

    cout.setf(ios::fixed);
    cout << setprecision(6);
    cout << "N=" << N << ", T=" << T << "\n";
    cout << "mean p* = " << mean << "\n";
    cout << "stddev = " << stdev << "\n";
    cout << "95% CI = [" << mean - ci << ", " << mean + ci << "]\n";
    return 0;
}
