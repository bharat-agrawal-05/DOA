#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum Colour {Red, Black};

struct RBTNode {
    int val;
    RBTNode *left, *right, *parent;
    Colour colour;

    RBTNode(int key) {
        val = key;
        left = right = parent = NULL;
        colour = Red;
    }
};

class RedBlackTree {
private:
    void leftRotate(RBTNode *&root, RBTNode *x) {
        RBTNode *y = x -> right;
        x -> right = y -> left;
        if (y -> left) y -> left -> parent = x;
        y -> parent = x -> parent;
        if (x -> parent == NULL) root = y;
        else if (x == x -> parent -> left) x -> parent -> left = y;
        else x -> parent -> right = y;
        y -> left = x;
        x -> parent = y;
    }

    void rightRotate(RBTNode *&root, RBTNode *x) {
        RBTNode *y = x -> left;
        x -> left = y -> right;
        if (y -> right) y -> right -> parent = x;
        y -> parent = x -> parent;
        if (x -> parent == NULL) root = y;
        else if (x == x -> parent -> right) x -> parent -> right = y;
        else x -> parent -> left = y;
        y -> right = x;
        x -> parent = y;
    }

    void fixInsert(RBTNode *&root, RBTNode *node) {
        // Does not enter the loop if node is root or it's parent is black
        while (node -> parent && node -> parent -> colour == Red) {
            if (node -> parent == node -> parent -> parent -> left) {
                RBTNode *uncle = node -> parent -> parent -> right;
                // If uncle is red, recolour and if node's grandparent is not root, recolour and recheck
                if (uncle && uncle -> colour == Red) {
                    node -> parent -> colour = Black;
                    uncle -> colour = Black;
                    node -> parent -> parent -> colour = Red;
                    node = node -> parent -> parent;
                } 
                // If uncle is NULL or black, apply suitable rotation and recolour
                else {
                    if (node == node -> parent -> right) {
                        node = node -> parent;
                        leftRotate(root, node);
                    }
                    node -> parent -> colour = Black;
                    node -> parent -> parent -> colour = Red;
                    rightRotate(root, node -> parent -> parent);
                }
            } 
            else {
                RBTNode *uncle = node -> parent -> parent -> left;
                // If uncle is red, recolour and if node's grandparent is not root, recolour and recheck
                if (uncle && uncle -> colour == Red) {
                    node -> parent -> colour = Black;
                    uncle -> colour = Black;
                    node -> parent -> parent -> colour = Red;
                    node = node -> parent -> parent;
                } 
                // If uncle is NULL or black, apply suitable rotation and recolour
                else {
                    if (node == node -> parent -> left) {
                        node = node -> parent;
                        rightRotate(root, node);
                    }
                    node -> parent -> colour = Black;
                    node -> parent -> parent -> colour = Red;
                    leftRotate(root, node -> parent -> parent);
                }
            }
        }
        root -> colour = Black; // Since root is always black
    }

    // Used to swap values if node to be deleted is not a leaf but if it is leaf return the pointer to the node
    RBTNode * bstDeletion(RBTNode *node) {
        while (node -> left != NULL || node -> right != NULL) {
            if (node -> right == NULL) {
                RBTNode *predecessor = node -> left;
                while (predecessor -> right) {
                    predecessor = predecessor -> right;
                }
                node -> val = predecessor -> val;
                // cout << "Predecessor Value = " << node -> val << endl;
                node = predecessor;
            }
            else {
                RBTNode *successor = node -> right;
                while (successor -> left) {
                    successor = successor -> left;
                }
                node -> val = successor -> val;
                // cout << "Successor Value = " << node -> val << endl;
                node = successor;
            }
        }
        return node;
    }

    void fixDelete(RBTNode *&root, RBTNode* node) {
        while (node != root && node -> colour == Black) {
            // If node is left child
            if (node == node -> parent -> left) {
                RBTNode* sibling = node -> parent -> right;
                // If sibling is red, swap colour of sibling and parent; left rotate parent 
                if (sibling -> colour == Red) {
                    sibling -> colour = Black;
                    node -> parent -> colour = Red;
                    leftRotate(root, node -> parent);
                    sibling = node -> parent -> right;
                }
                
                bool condition1 = sibling -> left == NULL || sibling -> left -> colour == Black;
                bool condition2 = sibling -> right == NULL || sibling -> right -> colour == Black;
                // If sibling and both nephew are black, make sibling red and add black to parent
                if (condition1 && condition2) {
                    sibling -> colour = Red;
                    node = node -> parent;
                } 
                else {
                    // If near nephew is red, swap colour of sibling and near nephew; right rotate sibling
                    if (condition2) {
                        sibling -> left -> colour = Black;
                        sibling -> colour = Red;

                        rightRotate(root, sibling);
                        sibling = node -> parent -> right;
                    }
                    // If far nephew is red, swap colour of sibling and parent; left rotate parent; make far nephew black
                    sibling -> colour = node -> parent -> colour;
                    node -> parent -> colour = Black;
                    sibling -> right -> colour = Black; 

                    leftRotate(root, node -> parent);
                    node = root;
                }
            } 
            // If node is right child (Symmetric to above)
            else { 
                RBTNode* sibling = node -> parent -> left;
                // If sibling is red, swap colour of sibling and parent; right rotate parent
                if (sibling -> colour == Red) {
                    sibling -> colour = Black;
                    node -> parent -> colour = Red;
                    rightRotate(root, node -> parent);
                    sibling = node -> parent -> left;
                }

                bool condition1 = sibling -> left == NULL || sibling -> left -> colour == Black;
                bool condition2 = sibling -> right == NULL || sibling -> right -> colour == Black;
                // If sibling and both nephew are black, make sibling red and add black to parent
                if (condition1 && condition2) {
                    sibling -> colour = Red;
                    node = node -> parent;
                } 
                else {
                    // If near nephew is red, swap colour of sibling and near nephew; left rotate sibling
                    if (condition1) {
                        sibling -> right -> colour = Black;
                        sibling -> colour = Red;
                        leftRotate(root, sibling);
                        sibling = node -> parent -> left;
                    }
                    // If far nephew is red, swap colour of sibling and parent; right rotate parent; make far nephew black
                    sibling -> colour = node -> parent -> colour;
                    node -> parent -> colour = Black;
                    sibling -> left -> colour = Black;
                    rightRotate(root, node -> parent);
                    node = root;
                }
            } 
        }
        
        node -> colour = Black;
    }


    RBTNode* searchNode(RBTNode *root, int key) {
        RBTNode *temp = root;
        while (temp) {
            if (temp -> val < key) {
                temp = temp -> right;
            } else if (temp -> val > key) {
                temp = temp -> left;
            } else {
                return temp;
            }
        }
        return NULL;
    }

public:
    void insert(RBTNode *&root, int key) {
        RBTNode *newNode = new RBTNode(key);
        if (!root) {
            root = newNode;
            root -> colour = Black; // Root is always black
            return;
        }

        RBTNode *parent = NULL, *current = root;
        while (current) {
            parent = current;
            if (key < current -> val) {
                current = current -> left;
            }
            else {
                current = current -> right;
            }
        }

        newNode -> parent = parent;
        if (key < parent -> val) {
            parent -> left = newNode;
        }
        else {
            parent -> right = newNode;
        }

        fixInsert(root, newNode);
    }

    bool search(RBTNode *root, int key) {
        RBTNode *node = searchNode(root, key);
        return node != NULL;
    }

    void deleteKey(RBTNode *&root, int key) {
        RBTNode *nodeToDel = searchNode(root, key);
        if (nodeToDel == NULL) {
            cout << "Key Not Found" << endl;
            return ;
        }

        nodeToDel = bstDeletion(nodeToDel); // Shift the values until node to be deleted is leaf

        if (nodeToDel -> colour == Black) {
            fixDelete(root, nodeToDel);
        }
        if (nodeToDel -> parent == NULL) {
            root = NULL;
        } 
        else {
            if (nodeToDel == nodeToDel -> parent -> left) {
                nodeToDel -> parent -> left = NULL;
            } 
            else {
                nodeToDel -> parent -> right = NULL;
            }
        }
    }

    void inorderTraversal(RBTNode *root, vector<int> &inOrder) {
        if (root == NULL) {
            return ;
        }   
        inorderTraversal(root -> left, inOrder);
        inOrder.emplace_back(root -> val);
        inorderTraversal(root -> right, inOrder);
    }

    int findMin(RBTNode *root) {
        if (root == NULL) {
            cout << "The Tree is Empty" << endl;
            return -1;
        }
        RBTNode *temp = root;
        while (temp -> left) {
            temp = temp -> left;
        }
        return temp -> val;
    }

    int findMax(RBTNode *root) {
        if (root == NULL) {
            cout << "The Tree is Empty" << endl;
            return -1;
        }
        RBTNode *temp = root;
        while (temp -> right) {
            temp = temp -> right;
        }
        return temp -> val;
    }

    int select(RBTNode *root, int k) {
        vector<int> inOrder;
        inorderTraversal(root, inOrder);
        if (k - 1 < 0 || k - 1 >= inOrder.size()) {
            cout << "Invalid k" << endl;
            return -1;
        }
        return inOrder[k - 1];
    }

    int rank(RBTNode *root, int key) {
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

    int findPredecessor(RBTNode *root, int key) {
        RBTNode *node = searchNode(root, key);
        if (node == NULL || node -> left == NULL) {
            cout << "No Predecessor" << endl;
            return -1;
        }
        return findMax(node -> left);
    }

    int findSuccessor(RBTNode *root, int key) {
        RBTNode *node = searchNode(root, key);
        if (node == NULL || node -> right == NULL) {
            cout << "No Successor" << endl;
            return -1;
        }
        return findMin(node -> right);
    }

    void levelOrderTraversal(RBTNode *root) {
        if (root == NULL) {
            cout << "The Tree is Empty" << endl;
            return ;
        }
        queue<RBTNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                RBTNode *node = q.front();
                q.pop();
                if (node == NULL) {
                    cout << "N(B)" << " ";
                    continue;
                }
                cout << node -> val << "(" << (node -> colour == Red ? "R" : "B") << ") ";
                q.push(node -> left);
                q.push(node -> right);
            }
            cout << endl;
        }
        cout << endl;
    }

};

int main() {
    RedBlackTree rbt;
    RBTNode *root = NULL;
    bool flag = true;

    vector<int> keys = {40, 20, 10, 30, 60, 50, 80, 70, 90, 99};
    for (int i = 0; i < keys.size(); ++i) {
        rbt.insert(root, keys[i]);
    }
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
        cout << "11. Level Order Traversal" << endl;
        cout << "12. Exit" << endl;

        int choice;
        cout << "Enter your choice : ";
        cin >> choice;
        switch(choice) {
            case 1: {
                int key;
                cout << "Enter the key to insert: ";
                cin >> key;
                rbt.insert(root, key);
                break;
            }

            case 2: {
                int key;
                cout << "Enter the key to search: ";
                cin >> key;
                cout << (rbt.search(root, key) ? "Key Found" : "Key Not Found") << endl;
                break;
             }

            case 3: {
                int key;
                cout << "Enter the key to delete: ";
                cin >> key;
                rbt.deleteKey(root, key);
                break;
            }

            case 4: {
                vector<int> inOrder;
                rbt.inorderTraversal(root, inOrder);
                cout << "Inorder Traversal: ";
                for (int i = 0; i < inOrder.size(); ++i) {
                    cout << inOrder[i] << " ";
                }
                cout << endl;
                break;
            }

            case 5: {
                int minVal = rbt.findMin(root);
                if (minVal != -1) {
                    cout << "Minimum Value: " << minVal << endl;
                }
                break;
            }

            case 6: {
                int maxVal = rbt.findMax(root);
                if (maxVal != -1) {
                    cout << "Maximum Value: " << maxVal << endl;
                }
                break;
            }

            case 7: {
                int k;
                cout << "Enter the value of k: ";
                cin >> k;
                int kth = rbt.select(root, k);
                if (kth != -1) {
                    cout << "The kth smallest element is: " << kth << endl;
                }
                break;
            }

            case 8: {
                int key;
                cout << "Enter the key to find rank: ";
                cin >> key;
                int r = rbt.rank(root, key);
                if (r != 0) {
                    cout << "The rank of the key is: " << r << endl;
                }
                break;
            }

            case 9: {
                int key;
                cout << "Enter the key to find predecessor: ";
                cin >> key;
                int pred = rbt.findPredecessor(root, key);
                if (pred != -1) {
                    cout << "The predecessor of the key is: " << pred << endl;
                }
                break;
            }

            case 10: {
                int key;
                cout << "Enter the key to find successor: ";
                cin >> key;
                int succ = rbt.findSuccessor(root, key);
                if (succ != -1) {
                    cout << "The successor of the key is: " << succ << endl;
                }
                break;
            }

            case 11: {
                rbt.levelOrderTraversal(root);
                break;
            }

            case 12: {
                flag = false;
            }
        }
    }
    return 0;
}