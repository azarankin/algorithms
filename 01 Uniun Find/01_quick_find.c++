#include <iostream>
using namespace std;

class QuickFind 
{
        //find O(1)         connected O(1)      uniun O(N)      initialize O(N)
private:
    inline static int SIZE = 20;
    int id[SIZE];
    int count = SIZE;

public:
    QuickFind() : count(SIZE) 
    {
        for (int i = 0; i < SIZE; i++) 
        {
            id[i] = i;
        }
    }

    int find(int p) 
    {
        return id[p];
    }

    bool connected(int p, int q) 
    {
        return id[p] == id[q];
    }

    void uniun(int p, int q) 
    {
        int pid = id[p];
        int qid = id[q];

        if (pid == qid) return;

        for (int i = 0; i < SIZE; i++) 
        {
            if (id[i] == pid) 
            {
                id[i] = qid;
            }
        }
        count--;
    }

    int getCount() const {
        return count;
    }
};

int main() {
    QuickFind uf();

    uf.uniun(1, 2);
    uf.uniun(2, 5);
    uf.uniun(5, 6);

    cout << boolalpha;
    cout << "Connected(1,6): " << uf.connected(1, 6) << endl;
    cout << "Connected(1,7): " << uf.connected(1, 7) << endl;
    cout << "Number of components: " << uf.getCount() << endl;

    return 0;
}
