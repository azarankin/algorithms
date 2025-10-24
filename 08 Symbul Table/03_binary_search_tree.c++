// search/insert/min/max/floor/ceiling/rank/select  O(h) = O(log n)
// if not in random order may take the worst case of O(N)
// avg case for search/insert is 1.39log N
// ordered iteration O(N)
// delete O(√N)

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

template <typename Key, typename Value>
class BST {
private:
    struct Node {
        Key key; Value val;
        Node* left; Node* right;
        int count;
        Node(const Key& k, const Value& v, int c = 1)
            : key(k), val(v), left(nullptr), right(nullptr), count(c) {}
    };

    Node* root = nullptr;

    // ---------- Compare Function ----------
    int compare(const Key& a, const Key& b) const {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }

    // ---------- Utilities ----------
    int size(Node* curr) const {
        return curr ? curr->count : 0;
    }

    // ---------- Search ----------
    Value* get(Node* curr, const Key& key) const {
        if (!curr) return nullptr;
        int cmp = compare(key, curr->key);
        if (cmp < 0) return get(curr->left, key);
        else if (cmp > 0) return get(curr->right, key);
        else return &(curr->val);
    }

    // ---------- Insert ----------
    Node* put(Node* curr, const Key& key, const Value& val) {
        if (!curr) return new Node(key, val);
        int cmp = compare(key, curr->key);
        if (cmp < 0)
            curr->left = put(curr->left, key, val);
        else if (cmp > 0)
            curr->right = put(curr->right, key, val);
        else
            curr->val = val;
        curr->count = 1 + size(curr->left) + size(curr->right);
        return curr;
    }

    // ---------- Min / Max ----------
    Node* min(Node* curr) const {
        return curr->left ? min(curr->left) : curr;
    }
    Node* max(Node* curr) const {
        return curr->right ? max(curr->right) : curr;
    }

    // ---------- Floor ----------
    Node* floor(Node* curr, const Key& key) const {
        if (!curr) return nullptr;
        int cmp = compare(key, curr->key);
        if (cmp == 0) return curr;
        if (cmp < 0) return floor(curr->left, key);
        Node* t = floor(curr->right, key);
        return t ? t : curr;
    }

    // ---------- Ceiling ----------
    Node* ceiling(Node* curr, const Key& key) const {
        if (!curr) return nullptr;
        int cmp = compare(key, curr->key);
        if (cmp == 0) return curr;
        if (cmp > 0) return ceiling(curr->right, key);
        Node* t = ceiling(curr->left, key);
        return t ? t : curr;
    }

    // ---------- Rank ----------
    int rank(Node* curr, const Key& key) const {
        if (!curr) return 0;
        int cmp = compare(key, curr->key);
        if (cmp < 0)
            return rank(curr->left, key);
        else if (cmp > 0)
            return 1 + size(curr->left) + rank(curr->right, key);
        else
            return size(curr->left);
    }

    // ---------- Select ----------
    Node* select(Node* curr, int k) const {
        if (!curr) return nullptr;
        int t = size(curr->left);
        if (t > k) return select(curr->left, k);
        else if (t < k) return select(curr->right, k - t - 1);
        else return curr;
    }

    // ---------- Delete Min ----------
    Node* deleteMin(Node* curr) {
        if (!curr->left) return curr->right;
        curr->left = deleteMin(curr->left);
        curr->count = 1 + size(curr->left) + size(curr->right);
        return curr;
    }

    // ---------- Delete ----------
    Node* deleteNode(Node* curr, const Key& key) {
        if (!curr) return nullptr;
        int cmp = compare(key, curr->key);
        if (cmp < 0)
            curr->left = deleteNode(curr->left, key);
        else if (cmp > 0)
            curr->right = deleteNode(curr->right, key);
        else {
            if (!curr->right) return curr->left;
            if (!curr->left) return curr->right;
            Node* t = curr;
            curr = min(t->right);
            curr->right = deleteMin(t->right);
            curr->left = t->left;
        }
        curr->count = 1 + size(curr->left) + size(curr->right);
        return curr;
    }

    // ---------- Inorder Traversal ----------
    void inorder(Node* curr, queue<Key>& q) const { //collect keys by order, sample: 2, 3, 4, 5, 7, 8
        if (!curr) return;
        inorder(curr->left, q);
        q.push(curr->key);
        inorder(curr->right, q);
    }

    // ---------- Level Order ----------
    void levelOrder(queue<Key>& q) const {
        if (!root) return;
        queue<Node*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            Node* curr = nodes.front(); nodes.pop();
            q.push(curr->key);
            if (curr->left) nodes.push(curr->left);
            if (curr->right) nodes.push(curr->right);
        }
    }

public:
    // ---------- Public Interface ----------
    int size() const { return size(root); }
    bool isEmpty() const { return root == nullptr; }

    void put(const Key& key, const Value& val) { root = put(root, key, val); }
    Value* get(const Key& key) const { return get(root, key); }
    void remove(const Key& key) { root = deleteNode(root, key); }

    Key min() const { return min(root)->key; }
    Key max() const { return max(root)->key; }
    Key floor(const Key& key) const { Node* x = floor(root, key); return x ? x->key : Key(); }
    Key ceiling(const Key& key) const { Node* x = ceiling(root, key); return x ? x->key : Key(); }

    int rank(const Key& key) const { return rank(root, key); }
    Key select(int k) const { Node* x = select(root, k); return x ? x->key : Key(); }

    queue<Key> keys() const { queue<Key> q; inorder(root, q); return q; }
    queue<Key> levelOrder() const { queue<Key> q; levelOrder(q); return q; }
};

int main() {
    BST<int, string> bst;
    vector<int> keys = {50, 30, 70, 20, 40, 60, 80};
    random_shuffle(keys.begin(), keys.end());

    for (int k : keys)
        bst.put(k, "val" + to_string(k));

    cout << "Inorder traversal:\n";
    auto q = bst.keys();
    while (!q.empty()) { cout << q.front() << " "; q.pop(); }
    cout << "\n";

    cout << "Min: " << bst.min() << "  Max: " << bst.max() << "\n";
    cout << "Floor(65): " << bst.floor(65) << "  Ceil(65): " << bst.ceiling(65) << "\n";
    cout << "Rank(60): " << bst.rank(60) << "  Select(3): " << bst.select(3) << "\n";
}
