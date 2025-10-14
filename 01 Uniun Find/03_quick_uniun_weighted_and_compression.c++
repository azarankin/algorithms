#include <iostream>
#include <stdexcept>
using namespace std;

struct Node 
{
    int parent;
    int size;    // presented the size only in the root!
};

class UnionFind 
{
    //  find O(α(N)) O(log*N) ≈ O(1)           connected O(α(N))     uniun O(α(N))         initialize O(N)
    // without compression
    //  find O(log(N))   O(log(N)) because its tree problem        connected O(log(N))      uniun O(log(N))          initialize O(N)
            // worst case O(N)
private:
    static const int N = 20; 
    Node tree[N];
    int components;

    // בדיקת תקינות אינדקס
    void validate(int p) const {
        if (p < 0 || p >= N) {
            throw invalid_argument("Index " + to_string(p) +
                                   " is not between 0 and " + to_string(N - 1));
        }
    }

public:
    UnionFind() 
    {
        components = N;
        for (int i = 0; i < N; i++) {
            tree[i].parent = i;
            tree[i].size = 1;
        }
    }

    int find(int p) {
        validate(p);
        // 1. finding the root
        // 2.compress the path to the root
        while (p != tree[x].parent) 
        {
            tree[p].parent = tree[tree[p].parent]; // compression !
            p = tree[p].parent;
        }

        return root;
    }

    // מאחד שתי קבוצות לפי גודל
    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB) return;

        // weighted, uniun the smaller tree to the bigger
        if (tree[rootA].size < tree[rootB].size) 
        {
            tree[rootA].parent = rootB;
            tree[rootB].size += tree[rootA].size;
        }
        else
        {
            tree[rootB].parent = rootA;
            tree[rootA].size += tree[rootB].size;
        }
        components--;
    }

    // בודק אם שני איברים באותה קבוצה
    bool connected(int a, int b) 
    {
        return find(a) == find(b);
    }

    // מחזיר את מספר הקומפוננטות
    int count() const 
    {
        return components;
    }

    // הדפסה של מבנה העץ
    void print() const {
        cout << "Index:\t";
        for (int i = 0; i < N; i++) cout << i << "\t";
        cout << "\nParent:\t";
        for (int i = 0; i < N; i++) cout << tree[i].parent << "\t";
        cout << "\nSize:\t";
        for (int i = 0; i < N; i++) cout << tree[i].size << "\t";
        cout << "\nComponents: " << components << "\n";
    }
};

int main() {
    UnionFind uf;

    uf.unite(1, 2);
    uf.unite(2, 5);
    uf.unite(5, 6);
    uf.unite(7, 8);
    uf.unite(1, 7);

    cout << boolalpha;
    cout << "Connected(1, 6): " << uf.connected(1, 6) << endl;  // true
    cout << "Connected(1, 8): " << uf.connected(1, 8) << endl;  // true
    cout << "Connected(1, 9): " << uf.connected(1, 9) << endl;  // false

    cout << "\nTree structure:\n";
    uf.print();

    cout << "\nNumber of components: " << uf.count() << endl;

    return 0;
}
