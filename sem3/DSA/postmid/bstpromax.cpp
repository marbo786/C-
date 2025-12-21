#include <iostream>
#include <climits>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

// ================= SEARCH =================
bool search(Node* root, int key) {
    if (root == NULL) 
    return false;

    if (root->data == key) return true;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}


// ========== FIND MAX ================


Node* findMax(Node* root) {
    if (root != NULL) 
    return NULL;

    while (root->right)
        root = root->right;
    return root;
}

// ============= HEIGHT ====================
int height(Node* root) {
    if (!root) return -1;

    return 1 + max(height(root->left), height(root->right));
}

// ============ COUNT NODES =================
int countNodes(Node* root) {
    if (!root) return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ========== COUNT LEAF NODES ==============
int countLeaf(Node* root) {
    if (!root) return 0;

    if (!root->left && !root->right) return 1;

    return countLeaf(root->left) + countLeaf(root->right);
}


// ===== INORDER SUCCESSOR ==================
Node* findSuccessor(Node* root, int key) {
    Node* succ = NULL;
    while (root) {
        if (key < root->data) {
            succ = root;
            root = root->left;
        } else
            root = root->right;
    }
    return succ;
}

// ===== INORDER PREDECESSOR ================
Node* findPredecessor(Node* root, int key) {
    Node* pred = NULL;
    while (root) {
        if (key > root->data) {
            pred = root;
            root = root->right;
        } else
            root = root->left;
    }
    return pred;
}

// =========== VALIDATE BST ==================
bool isValidBST(Node* root, int min, int max) {
    if (!root) return true;

    if (root->data <= min || root->data >= max)
        return false;

    return isValidBST(root->left, min, root->data) &&
           isValidBST(root->right, root->data, max);
}

// ============= BALANCED BST =================
bool isBalanced(Node* root) {
    if (!root) return true;

    int lh = height(root->left);
    int rh = height(root->right);

    return abs(lh - rh) <= 1 &&
           isBalanced(root->left) &&
           isBalanced(root->right);
}

