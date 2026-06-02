#include <iostream>
using namespace std;


struct Node{

    int data;
    Node* left;
    Node* right;

    Node(int value): data(value), left(nullptr),right(nullptr) {};
};

Node* insert(Node* root,int value){

    if (root == nullptr){
        return new Node(value);
    }
    if (value < root->data){
        root->left = insert(root->left,value);
    }
    else if (value > root->data){
        root->right = insert(root->right,value);
    }
    return root;
}

Node* findmin(Node* root){
    while(root->left != nullptr){
        root = root->left;
    }
    return root;
}

Node* findmax(Node* root){
    if(root == nullptr){
        return NULL;
    }

    while(root->right){
        root = root->right;
    }
    return root;
}

bool Search(Node* root, int key){
    if(root == NULL){
        return false;
    }

    if(root->data == key){
        return true;
    }

    if(key < root->data){
        return Search(root->left,key);
    }
    if(key> root->data){
        return Search(root->right,key);
    }
}

int height(Node* root){
    if(!root){
        return -1;
    }
    return 1 + max(height(root->left),height(root->right));
}

int countnodes(Node* root){
    if(!root){
        return 0;
    }
    return 1 + countnodes(root->left) + countnodes(root->right);
}

int countleaf(Node* root){
    if(!root){
        return 0;
    }

    if(!root->left && !root->right){
        return 1;
    }

    return countleaf(root->left) + countleaf(root->right);
}

Node* deletenode(Node* root, int value){
    if(!root){
        return root;
    }

    if(value < root->data){
        root->left = deletenode(root->left,value);
    }

    else if(value > root->data){
        root->right = deletenode(root->right,value);
    }

    else{                                                                // node with one child or no child
        if(root->left == nullptr){
            Node* temp = root->right;
            delete root;
            return temp;
        }
    
        if(root->right == nullptr){
            Node* temp = root->left;
            delete root;
            return temp;
        }
    
    
    Node* temp = findmin(root->right);                      // find smallest in root right subtree
    root->data = temp->data;
    root->right = deletenode(root->right,temp->data);       // same shit we did above in case 0
    }
    return root;
}

void preordertraversal(Node* root){
    if(!root){
        return;
    }
    cout<<root->data<<" ";
    preordertraversal(root->left);
    preordertraversal(root->right);
}


int main(){

    Node* root = nullptr;

    root = insert(root,10);
    root = insert(root,20);

    root = deletenode(root,10);

    preordertraversal(root);

    return 0;
}