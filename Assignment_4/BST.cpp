#include <bits/stdc++.h>
using namespace std;

struct BSTNode{
    int val;
    BSTNode *left, *right, *parent;

    BSTNode(int data){
        val = data;
        left = right = parent = NULL;
    }
};

class BinarySearchTree{
    private:
        void inorderTraversalHelper(BSTNode* root, vector<int>& inOrder){
            if(root == NULL){
                return ;
            }
            inorderTraversalHelper(root -> left, inOrder);
            inOrder.emplace_back(root -> val);
            inorderTraversalHelper(root -> right, inOrder);
        }
    public:
        BSTNode* root = NULL;

        void insertKey(int key){
            BSTNode *newNode = new BSTNode(key);
            if (root == NULL){
                root = newNode;
                return ;
            }

            BSTNode *parent = NULL, *curr = root;
            while (curr){
                parent = curr;
                if (key < curr -> val){
                    curr = curr -> left;
                }
                else{
                    curr = curr -> right;
                }
            }

            newNode -> parent = parent;
            if (key < parent -> val){
                parent -> left = newNode;
            }
            else{
                parent -> right = newNode;
            }
        }

        void deleteKey(int key) {
            BSTNode* nodeToDelete = root;
            while (nodeToDelete) {
                if (nodeToDelete->val < key) {
                    nodeToDelete = nodeToDelete->right;
                } else if (nodeToDelete->val > key) {
                    nodeToDelete = nodeToDelete->left;
                } else {
                    break;
                }
            }

            if (nodeToDelete == NULL) {
                cout << "Key not found" << endl;
                return;
            }

            BSTNode* parent = nodeToDelete->parent;

            // 0 or 1 child case
            if (nodeToDelete->left == NULL || nodeToDelete->right == NULL) {
                BSTNode* child = nodeToDelete->left ? nodeToDelete->left : nodeToDelete->right;

                if (parent == NULL) {  // Deleting the root node
                    root = child;
                } else {
                    if (parent->left == nodeToDelete) {
                        parent->left = child;
                    } else {
                        parent->right = child;
                    }
                }
                if (child != NULL) {
                    child->parent = parent;  // Update the child's parent pointer
                }
                delete nodeToDelete;

            } else {  // 2 children case
                BSTNode* successor = nodeToDelete->right;
                while (successor->left != NULL) {
                    successor = successor->left;
                }

                nodeToDelete->val = successor->val;  // Copy the successor's value to nodeToDelete

                // Now delete the successor node (which will have at most one child)
                if (successor->parent->left == successor) {
                    successor->parent->left = successor->right;
                } else {
                    successor->parent->right = successor->right;
                }

                if (successor->right != NULL) {
                    successor->right->parent = successor->parent;
                }

                delete successor;
            }
        }

        bool search(int key){
            BSTNode* node = root;
            while(node){
                if (node -> val < key){
                    node = node -> right;
                }
                else if (node -> val > key){
                    node = node -> left;
                }
                else{
                    return true;
                }
            }
            return false;
        }
        vector<int> inorderTraversal(){
            vector<int> inOrder;
            inorderTraversalHelper(root, inOrder);
            return inOrder;
        }
        int findMin(){
            BSTNode* temp = root;
            while(temp -> left){
                temp = temp -> left;
            }
            return temp -> val;
        }
        int findMax(){
            BSTNode* temp = root;
            while(temp -> right){
                temp = temp -> right;
            }
            return temp -> val;
        }
        int select(int k){
            vector<int> inOrder = inorderTraversal();
            if (k <= 0 || k > inOrder.size()){
                cout << "Invalid k" << endl;
                return -1;
            }
            return inOrder[k-1];
        }
        int rank(int key){
            vector<int> inOrder = inorderTraversal();
            int rank = 0;
            for (int i = 0; i < inOrder.size(); i++){
                if (inOrder[i] == key){
                    return rank;
                }
                rank++;
            }
            return -1;
        }
        int findPredecessor(int key){
            BSTNode* node = root;
            while(node){
                if (node -> val < key){
                    node = node -> right;
                }
                else if (node -> val > key){
                    node = node -> left;
                }
                else{
                    break;
                }
            }
            if (node == NULL){
                cout << "Key not found" << endl;
                return -1;
            }
            if (node -> left){
                node = node -> left;
                while(node -> right){
                    node = node -> right;
                }
                return node -> val;
            }
            else{
                BSTNode* parent = node -> parent;
                while(parent && parent -> left == node){
                    node = parent;
                    parent = parent -> parent;
                }
                if (parent == NULL){
                    cout << "No Predecessor" << endl;
                    return -1;
                }
                return parent -> val;
            }
        }
        int findSuccessor(int key){
            BSTNode* node = root;
            while(node){
                if (node -> val < key){
                    node = node -> right;
                }
                else if (node -> val > key){
                    node = node -> left;
                }
                else{
                    break;
                }
            }
            if (node == NULL){
                cout << "Key not found" << endl;
                return -1;
            }
            if (node -> right){
                node = node -> right;
                while(node -> left){
                    node = node -> left;
                }
                return node -> val;
            }
            else{
                BSTNode* parent = node -> parent;
                while(parent && parent -> right == node){
                    node = parent;
                    parent = parent -> parent;
                }
                if (parent == NULL){
                    cout << "No Successor" << endl;
                    return -1;
                }
                return parent -> val;
            }
        }
};

void print(BinarySearchTree bst){
    vector<int> inOrder = bst.inorderTraversal();
    for (int i = 0; i < inOrder.size(); i++){
        cout << inOrder[i] << " ";
    }
    cout << endl;
}

int main()
{
    BinarySearchTree bst;
    bst.insertKey(10);
    bst.insertKey(5);
    bst.insertKey(15);
    bst.insertKey(3);
    print(bst);
    bst.deleteKey(10);
    print(bst);
    return 0;
}