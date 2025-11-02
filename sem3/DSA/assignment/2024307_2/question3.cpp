#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int val) {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};


void swapNodes(Node* &head, Node* a, Node* b) {
    if (!a || !b || a == b) return; 

    
    if (head == a) head = b;
    else if (head == b) head = a;

    Node* prevA = a->prev;
    Node* nextA = a->next;
    Node* prevB = b->prev;
    Node* nextB = b->next;

    if (a->next == b) {         //if a before b
        a->next = nextB;
        b->prev = prevA;
        b->next = a;
        a->prev = b;

        if (prevA) prevA->next = b;
        if (nextB) nextB->prev = a;
    }
                                //if b before a
    else if (b->next == a) {
        b->next = nextA;
        a->prev = prevB;
        a->next = b;
        b->prev = a;

        if (prevB) prevB->next = a;
        if (nextA) nextA->prev = b;
    }
    else {
        if (prevA) prevA->next = b;
        if (nextA) nextA->prev = b;
        if (prevB) prevB->next = a;
        if (nextB) nextB->prev = a;

        a->prev = prevB;
        a->next = nextB;
        b->prev = prevA;
        b->next = nextA;
    }
}

void printList(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {

    int arr[] = {3,1,8,5,4,2,9,4,7,0};

    Node* head = new Node(arr[0]);
    Node* curr = head;
    for (int i = 1; i < 10; i++) {
        Node* temp = new Node(arr[i]);
        curr->next = temp;
        temp->prev = curr;
        curr = temp;
    }

    cout << "Original: ";
    printList(head);

                                // manually swapping 3 and 9
    Node* a = head;         
    Node* b = head->next->next->next->next->next->next; 
    swapNodes(head, a, b);

    cout << "After swap: ";
    printList(head);

    return 0;
}

