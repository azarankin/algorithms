// search       1/2*O(N)~O(N)     
// insert/update O(N)        
// not ordered iteration
// size/isEmpty O(1)
// rank/floor/ceiling O(N)
// min/max O(N)
// ordered iteration O(n log n)
#include <iostream>
#include <queue>
#include <stdexcept>

template<typename Key, typename Value>
class ST {
private:
    // ---------- Node ----------
    struct Node {
        Key key; Value val;
        Node* next;
        Node(const Key& k, const Value& v = Value(), Node* n = nullptr)
            : key(k), val(v), next(n) {}
    };

    Node* first;  // pointer to the first node
    int n;        // number of key-value pairs

    // ---------- equalTo Function ----------
    // Returns true if keys are equal
    bool equal(const Key& a, const Key& b) const {
        return a == b;
    }

public:
    // ---------- Constructor ----------
    ST() : first(nullptr), n(0) {}

    // ---------- Destructor ----------
    ~ST() {
        Node* curr = first;
        while (curr != nullptr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }

    // ---------- Put ----------
    // Insert or update a key-value pair in the table
    void put(const Key& key, const Value& val = Value()) {
        Node* curr = first;
        while (curr != nullptr) {
            if (equal(curr->key, key)) {  // equal instead of ==
                curr->val = val;  // update existing value
                return;
            }
            curr = curr->next;
        }
        // Insert new node at the front
        first = new Node(key, val, first);
        n++;
    }

    // ---------- Get ----------
    // Return the value paired with the key (or default if absent)
    Value get(const Key& key) const {
        for (Node* x = first; x != nullptr; x = x->next) {
            if (equal(x->key, key)) {  // equal instead of ==
                return x->val;
            }
        }
        return Value();  // return default-constructed value
    }

    // ---------- Contains ----------
    // Check if the table contains the given key
    bool contains(const Key& key) const {
        for (Node* curr = first; curr != nullptr; curr = curr->next) {
            if (equal(curr->key, key)) return true;
        }
        return false;
    }

    // ---------- Delete ----------
    // Remove key (and its value) from the table
    void deleteKey(const Key& key) {
        Node* curr = first;
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (equal(curr->key, key)) {  // equal instead of ==
                if (prev == nullptr) {
                    // deleting the first node
                    first = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                n--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    // ---------- isEmpty ----------
    bool isEmpty() const {
        return n == 0;
    }

    // ---------- size ----------
    int size() const {
        return n;
    }

    // ---------- keys ----------
    // Return all keys in the table as a queue
    std::queue<Key> keys() const {
        std::queue<Key> q;
        for (Node* x = first; x != nullptr; x = x->next) {
            q.push(x->key);
        }
        return q;
    }
};

int main() {
    ST<std::string, int> st;

    st.put("A", 1);
    st.put("B", 2);
    st.put("C", 3);

    std::cout << "Size: " << st.size() << "\n";
    std::cout << "B = " << st.get("B") << "\n";

    st.deleteKey("B");
    std::cout << "Size after delete: " << st.size() << "\n";

    std::queue<std::string> q = st.keys();
    std::cout << "Keys: ";
    whil
