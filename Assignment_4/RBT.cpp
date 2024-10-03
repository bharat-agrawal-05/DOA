#include <iostream>
#include <vector>
using namespace std;

enum Color { RED, BLACK };

struct RBTNode {
    int key;
    RBTNode *left, *right, *parent;
    Color color;

    RBTNode(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RedBlackTree {
private:
    RBTNode *root;

    // Left rotation
    void leftRotate(RBTNode *x) {
        RBTNode *y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Right rotation
    void rightRotate(RBTNode *x) {
        RBTNode *y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    // Fix violations after insertion
    void fixInsert(RBTNode *z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBTNode *y = z->parent->parent->right; // Uncle
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                RBTNode *y = z->parent->parent->left; // Uncle
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void inorderHelper(RBTNode *node, vector<int> &res) {
        if (node) {
            inorderHelper(node->left, res);
            res.push_back(node->key);
            inorderHelper(node->right, res);
        }
    }

    RBTNode* findMin(RBTNode *node) {
        while (node->left)
            node = node->left;
        return node;
    }

    // Helper function to search for a key
    RBTNode* searchHelper(RBTNode *node, int key) {
        if (!node || node->key == key)
            return node;
        if (key < node->key)
            return searchHelper(node->left, key);
        return searchHelper(node->right, key);
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int key) {
        RBTNode *newNode = new RBTNode(key);
        if (!root) {
            root = newNode;
            root->color = BLACK; // Root is always black
            return;
        }

        RBTNode *parent = nullptr, *current = root;
        while (current) {
            parent = current;
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }

        newNode->parent = parent;
        if (key < parent->key)
            parent->left = newNode;
        else
            parent->right = newNode;

        // Fix any violations caused by the insertion
        fixInsert(newNode);
    }

    bool search(int key) {
        return searchHelper(root, key) != nullptr;
    }

    vector<int> inorderTraversal() {
        vector<int> res;
        inorderHelper(root, res);
        return res;
    }

    int findMin() {
        if (!root) throw runtime_error("Empty tree");
        return findMin(root)->key;
    }

    int findMax() {
        if (!root) throw runtime_error("Empty tree");
        RBTNode* node = root;
        while (node->right)
            node = node->right;
        return node->key;
    }

    int select(int k) {
        vector<int> res = inorderTraversal();
        if (k - 1 < 0 || k - 1 >= res.size()) throw runtime_error("Index out of bounds");
        return res[k - 1];
    }

    int rank(int key) {
        vector<int> res = inorderTraversal();
        for (int i = 0; i < res.size(); ++i) {
            if (res[i] == key) return i + 1;
        }
        throw runtime_error("Key not found");
    }

    int findPredecessor(int key) {
        RBTNode *node = searchHelper(root, key);
        if (!node || !node->left) throw runtime_error("No predecessor");
        return findMin(node->left)->key;
    }

    int findSuccessor(int key) {
        RBTNode *node = searchHelper(root, key);
        if (!node || !node->right) throw runtime_error("No successor");
        return findMin(node->right)->key;
    }
};

int main() {
    RedBlackTree rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(5);

    cout << rbt.select(2) << endl; // Output: 10
    cout << rbt.rank(20) << endl;  // Output: 3
    cout << rbt.findPredecessor(10) << endl; // Output: 5
    cout << rbt.findSuccessor(10) << endl;   // Output: 20

    return 0;
}