// delete order: O(√N) because tree is unbalanced with time (not like AVL tree or Red-Black Tree)


#include <iostream>
using namespace std;

template <typename Key, typename Value>
class BST {
private:
    struct Node {
        Key key;
        Value val;
        Node* left;
        Node* right;
        int count;
        Node(const Key& k, const Value& v)
            : key(k), val(v), left(nullptr), right(nullptr), count(1) {}
    };

    Node* root = nullptr;

    int size(Node* x) {
        return x ? x->count : 0;
    }

    // ---------- Insert ----------
    Node* put(Node* x, const Key& key, const Value& val) {
        if (!x) return new Node(key, val);
        if (key < x->key)
            x->left = put(x->left, key, val);
        else if (key > x->key)
            x->right = put(x->right, key, val);
        else
            x->val = val;
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

    // ---------- Find Minimum ----------
    Node* min(Node* x) {
        if (!x->left) return x;
        return min(x->left);
    }

    // ---------- Find Maximum ----------
    Node* max(Node* x) {
        if (!x->right) return x;
        return max(x->right);
    }

    // ---------- Delete Minimum ----------
    Node* deleteMin(Node* x) {
        if (!x->left) return x->right;
        x->left = deleteMin(x->left);
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

    // ---------- Delete Maximum ----------
    Node* deleteMax(Node* x) {
        if (!x->right) return x->left;
        x->right = deleteMax(x->right);
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

    // ---------- Hibbard Deletion ----------
    Node* deleteNode(Node* x, const Key& key) {
        if (!x) return nullptr;
        if (key < x->key)
            x->left = deleteNode(x->left, key);
        else if (key > x->key)
            x->right = deleteNode(x->right, key);
        else {
            // Case 1: no right child
            if (!x->right) return x->left;
            // Case 2: no left child
            if (!x->left) return x->right;
            // Case 3: two children
            Node* t = x;
            x = min(t->right);                      // successor
            x->right = deleteMin(t->right);         // delete successor from right subtree
            x->left = t->left;                      // restore left subtree
        }
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

public:
    int size() { return size(root); }

    void put(const Key& key, const Value& val) {
        root = put(root, key, val);
    }

    void deleteMin() {
        if (root) root = deleteMin(root);
    }

    void deleteMax() {
        if (root) root = deleteMax(root);
    }

    void deleteNode(const Key& key) {
        root = deleteNode(root, key);
    }

    Key min() { return min(root)->key; }
    Key max() { return max(root)->key; }

    void inorder(Node* x) {
        if (!x) return;
        inorder(x->left);
        cout << x->key << " ";
        inorder(x->right);
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST<int, string> bst;
    bst.put(50, "A");
    bst.put(30, "B");
    bst.put(70, "C");
    bst.put(20, "D");
    bst.put(40, "E");
    bst.put(60, "F");
    bst.put(80, "G");

    cout << "Inorder before delete: ";
    bst.inorderTraversal();

    bst.deleteMin();
    cout << "After deleteMin: ";
    bst.inorderTraversal();

    bst.deleteMax();
    cout << "After deleteMax: ";
    bst.inorderTraversal();

    bst.deleteNode(50);
    cout << "After deleteNode(50): ";
    bst.inorderTraversal();
}
