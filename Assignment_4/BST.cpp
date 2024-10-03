#include <iostream>
#include <vector>
using namespace std;

struct BSTNode {
    int val;
    BSTNode *left, *right, *parent;

    BSTNode(int data) {
        val = data;
        left = right = parent = NULL;
    }
};

class BinarySearchTree {
private:
    BSTNode* searchNode(BSTNode *root, int key) {
        BSTNode *temp = root;
        while (temp) {
            if (temp -> val < key) {
                temp = temp -> right;
            }
            else if (temp -> val > key) {
                temp = temp -> left;
            }
            else {
                return temp;
            }
        }
        return NULL;
    }

public:
    void insert(BSTNode *&root, int key) {
        BSTNode *newNode = new BSTNode(key);
        if (root == NULL) {
            root = newNode;
            return ;
        }

        BSTNode *parent = NULL, *curr = root;
        while (curr) {
            parent = curr;
            if (key < curr -> val) {
                curr = curr -> left;
            }
            else {
                curr = curr -> right;
            }
        }

        newNode -> parent = parent;
        if (key < parent -> val) {
            parent -> left = newNode;
        }
        else {
            parent -> right = newNode;
        }
    }

    bool search(BSTNode *root, int key) {
        BSTNode *node = searchNode(root, key);
        return node != NULL;
    }

    void deleteKey(BSTNode *&root, int key) {
        BSTNode *nodeToDel = searchNode(root, key);
        if (nodeToDel == NULL) {
            cout << "Key Not Found in Tree" << endl;
            return ;
        }
        BSTNode *parent = nodeToDel -> parent;
        nodeToDel -> parent = NULL;
        if (nodeToDel -> left == NULL || nodeToDel -> right == NULL) {
            BSTNode *exists = nodeToDel -> left ? nodeToDel -> left : nodeToDel -> right;
            parent -> left = parent -> left == nodeToDel ? exists : parent -> left;
            parent -> right = parent -> right == nodeToDel ? exists : parent -> right;
        }
        else {
            int successor = findSuccessor(nodeToDel, key);
            nodeToDel -> val = successor;
            deleteKey(nodeToDel -> right, successor);
        }
    }

    void inorderTraversal(BSTNode *root, vector<int>& inOrder) {
        if (root == NULL) {
            return ;
        }
        inorderTraversal(root -> left, inOrder);
        inOrder.emplace_back(root -> val);
        inorderTraversal(root -> right, inOrder);
    }

    int findMin(BSTNode* root) {
        if (root == NULL) {
            cout << "The Tree is Empty" << endl;
            return -1;
        }
        BSTNode *temp = root;
        while (temp -> left) {
            temp = temp -> left;
        }
        return temp -> val;
    }

    int findMax(BSTNode* root) {
        if (root == NULL) {
            cout << "The Tree is Empty" << endl;
            return -1;
        }
        BSTNode *temp = root;
        while (temp -> right) {
            temp = temp -> right;
        }
        return temp -> val;
    }

    int select(BSTNode* root, int k) {
        vector<int> inOrder;
        inorderTraversal(root, inOrder);
        if (k - 1 < 0 || k - 1 >= inOrder.size()) {
            cout << "Invalid k" << endl;
            return -1;
        }
        return inOrder[k - 1];
    }

    int rank(BSTNode *root, int key) {
        vector<int> inOrder;
        inorderTraversal(root, inOrder);
        for (int i = 0; i < inOrder.size(); ++i) {
            if (inOrder[i] == key) {
                return i + 1;
            }
        }
        cout << "Key Not Found in Tree" << endl;
        return 0;
    }

    int findPredecessor(BSTNode *root, int key) {
        BSTNode *node = searchNode(root, key);
        if (node == NULL || node -> left == NULL) {
            cout << "No Predecessor" << endl;
            return -1;
        }
        return findMax(node -> left);
    }

    int findSuccessor(BSTNode *root, int key) {
        BSTNode *node = searchNode(root, key);
        if (node == NULL || node -> right == NULL) {
            cout << "No Successor" << endl;
            return -1;
        }
        return findMin(node -> right);
    }
};

int main() {
    BinarySearchTree bst;
    BSTNode *root = NULL;
    bool flag = true;
    while (flag) {
        cout << "\n\n1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Delete" << endl;
        cout << "4. Display Inorder Traversal" << endl;
        cout << "5. Find Min" << endl;
        cout << "6. Find Max" << endl;
        cout << "7. Select" << endl;
        cout << "8. Rank" << endl;
        cout << "9. Find Predecessor" << endl;
        cout << "10. Find Successor" << endl;
        cout << "11. Exit" << endl;

        int choice;
        cout << "Enter your choice : ";
        cin >> choice;
        switch(choice) {
            case 1: {
                int key;
                cout << "Enter the key to insert: ";
                cin >> key;
                bst.insert(root, key);
                break;
            }
            
            case 2: {
                int key;
                cout << "Enter the key to search: ";
                cin >> key;
                cout << (bst.search(root, key) ? "Key Found" : "Key Not Found") << endl;
                break;
            }

            case 3: {
                int key;
                cout << "Enter the key to delete: ";
                cin >> key;
                bst.deleteKey(root, key);
                break;
            }

            case 4: {
                vector<int> inOrder;
                bst.inorderTraversal(root, inOrder);
                cout << "Inorder Traversal: ";
                for (int i = 0; i < inOrder.size(); ++i) {
                    cout << inOrder[i] << " ";
                }
                cout << endl;
                break;
            }

            case 5: {
                int minVal = bst.findMin(root);
                if (minVal != -1) {
                    cout << "Minimum Value: " << minVal << endl;
                }
                break;
            }

            case 6: {
                int maxVal = bst.findMax(root);
                if (maxVal != -1) {
                    cout << "Maximum Value: " << maxVal << endl;
                }
                break;
            }

            case 7: {
                int k;
                cout << "Enter the value of k: ";
                cin >> k;
                int kth = bst.select(root, k);
                if (kth != -1) {
                    cout << "The kth smallest element is: " << kth << endl;
                }
                break;
            }

            case 8: {
                int key;
                cout << "Enter the key to find rank: ";
                cin >> key;
                int r = bst.rank(root, key);
                if (r != 0) {
                    cout << "The rank of the key is: " << r << endl;
                }
                break;
            }

            case 9: {
                int key;
                cout << "Enter the key to find predecessor: ";
                cin >> key;
                int pred = bst.findPredecessor(root, key);
                if (pred != -1) {
                    cout << "The predecessor of the key is: " << pred << endl;
                }
                break;
            }

            case 10: {
                int key;
                cout << "Enter the key to find successor: ";
                cin >> key;
                int succ = bst.findSuccessor(root, key);
                if (succ != -1) {
                    cout << "The successor of the key is: " << succ << endl;
                }
                break;
            }

            case 11: {
                flag = false;
            }
        }
    }
    return 0;
}