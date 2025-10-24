// search       O(log n)     
// insert/update 1/2*O(N) ~ O(N)        
// ordered iteration
// size/isEmpty O(1)
// rank/floor/ceiling O(log N)
// min/max O(1)
// ordered iteration O(N)
#include <iostream>
#include <stdexcept>

template<typename Key, typename Value, int SIZE=20>
class OrderedArrayST {
private:
    Key keys[SIZE];
    Value vals[SIZE];
    int n; // number of key-value pairs

    // ---------- Compare Function ----------
    // Returns:
    //  -1 if a < b
    //   0 if a == b
    //  +1 if a > b
    int compareTo(const Key& a, const Key& b) const {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }

public:
    OrderedArrayST() : n(0) {}

    ---------- Binary Search ----------
    returns index of key or insertion point
    int rank(const Key& key) const {
        int lo = 0, hi = n - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int cmp = compare(key, keys[mid]);
            if (cmp < 0) hi = mid - 1;
            else if (cmp > 0) lo = mid + 1;
            else return mid;
        }
        return lo;  // insertion point, the rank,  k-th smallest key
    }

    // ---------- Get ----------
    Value get(const Key& key) const {
        if (isEmpty()) return Value();
        int i = rank(key);
        if (i < n && compare(keys[i], key) == 0)
            return vals[i];
        return Value(); // default if not found
    }

    // ---------- Put ----------
    void put(const Key& key, const Value& val = Value()) {
        if (n == SIZE) throw std::overflow_error("Symbol Table full");
        int i = rank(key);

        // if key already exists -> update
        if (i < n && compare(keys[i], key) == 0) {
            vals[i] = val;
            return;
        }

        // shift elements to the right
        for (int j = n; j > i; --j) {
            keys[j] = keys[j - 1];
            vals[j] = vals[j - 1];
        }

        keys[i] = key;
        vals[i] = val;
        n++;
    }

    // ---------- Delete ----------
    void deleteKey(const Key& key) {
        if (isEmpty()) return;
        int i = rank(key);
        if (i == n || compare(keys[i], key) != 0) return;  // key not found

        for (int j = i; j < n - 1; ++j) {
            keys[j] = keys[j + 1];
            vals[j] = vals[j + 1];
        }
        n--;
    }

    // ---------- Contains ----------
    bool contains(const Key& key) const {
        int i = rank(key);
        return (i < n && compare(keys[i], key) == 0);
    }

    // ---------- Size ----------
    int size() const { return n; }

    // ---------- isEmpty ----------
    bool isEmpty() const { return n == 0; }

    // ---------- Print all keys ----------
    void printKeys() const {
        for (int i = 0; i < n; ++i) {
            std::cout << keys[i] << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    OrderedArrayST<std::string, int> st;

    st.put("C", 3);
    st.put("A", 1);
    st.put("B", 2);
    st.put("E", 5);
    st.put("D", 4);

    std::cout << "Keys: ";
    st.printKeys();  // Output: A B C D E

    std::cout << "Value for C: " << st.get("C") << "\n";

    st.deleteKey("C");
    std::cout << "After deleting C: ";
    st.printKeys();  // Output: A B D E

    return 0;
}
