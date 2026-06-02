#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
};

int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int getbalance(Node *N){
    if (N == NULL){
        return 0;
    }

    return height(N->left) - height(N->right);
}

Node* rightrotate(Node* y){
    Node* x = y->left;
    Node* t2 = x->right;

    x->right = y;
    y->left = t2;
    
    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;

    return x;
}

Node* leftrotate(Node* x){
    Node* y = x->right;
    Node* t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key){
    if(!node){
        Node* newnode = new Node();
        newnode->key = key;
        newnode->left = nullptr;
        newnode->right = nullptr;
        newnode->height = 1;
        return newnode;
    }

    if (key < node->key){
        node->left = insert(node->left,key);
    }
    else if (key > node->key){
        node->right = insert(node->right,key);
    }
    else{
        return node;}

        node->height = max(height(node->left),height(node->right)) + 1;
        int balance = getbalance(node);

        // LL case

        if(balance > 1 && key < node->left->key){
            return rightrotate(node);
        }

        // RR case

        if(balance < -1 && key > node->right->key){
            return leftrotate(node);
        }

        // LR case

        if(balance > 1 && key > node->left->key){
            node->left = leftrotate(nodde->left);
            return rightrotate(node);
        }

        // RL case

        if(balance < -1 && key < node->right->key){
            node->right = rightrotate(node->right);
            return leftrotate(node);
        }

        return node;
}