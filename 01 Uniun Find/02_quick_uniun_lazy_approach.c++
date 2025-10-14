#include <iostream>
#include <vector>
using namespace std;

class QuickUnionUF 
{
    //find O(N)         connected O(N)      uniun O(N)     (best case is O(1))      initialize O(N)
private:
    inline static int SIZE = 20;
    int id[SIZE];

public:
    QuickUnionUF()
    {
        for (int i = 0; i < SIZE; i++) 
        {
            id[i] = i;
        }
    }

private:
    int root(int i) 
    {
        while (i != id[i]) 
        {
            i = id[i];
        }
        return i;
    }

public:
    // בודק אם שני איברים שייכים לאותה קבוצה
    bool connected(int p, int q) 
    {
        return root(p) == root(q);
    }

    // מאחד את שתי הקבוצות
    void unionSets(int p, int q) 
    {
        int i = root(p);
        int j = root(q);
        id[i] = j;   // מצמיד את השורש של p לשורש של q
    }
};

int main() {
    QuickUnionUF uf(10);

    uf.unionSets(1, 2);
    uf.unionSets(2, 5);
    uf.unionSets(5, 6);

    cout << boolalpha;
    cout << "Connected(1, 6): " << uf.connected(1, 6) << endl;  // true
    cout << "Connected(1, 7): " << uf.connected(1, 7) <
}