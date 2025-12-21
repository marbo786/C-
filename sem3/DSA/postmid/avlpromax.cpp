#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) {
        key = k;
        left = right = NULL;
        height = 1;
    }
};


// ---------- BALANCE FACTOR ----------
int getBalance(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}



// ---------- SEARCH ----------
bool search(Node* root, int key) {
    if (!root) return false;
    if (root->key == key) return true;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// ---------- FIND MAX ----------
Node* findMax(Node* root) {
    if (!root) return NULL;
    while (root->right)
        root = root->right;
    return root;
}

// ---------- COUNT NODES ----------
int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ---------- VALIDATE AVL TREE ----------
bool isBST(Node* root, int minV, int maxV) {
    if (!root) return true;
    if (root->key <= minV || root->key >= maxV)
        return false;
    return isBST(root->left, minV, root->key) &&
           isBST(root->right, root->key, maxV);
}

bool isBalancedAVL(Node* root) {
    if (!root) return true;
    int bal = getBalance(root);
    if (bal > 1 || bal < -1)
        return false;
    return isBalancedAVL(root->left) && isBalancedAVL(root->right);
}

bool validateAVL(Node* root) {
    return isBST(root, INT_MIN, INT_MAX) && isBalancedAVL(root);
}

// ---------- INORDER ----------
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

