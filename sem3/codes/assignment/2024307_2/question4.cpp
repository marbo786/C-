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

bool positionHead(Node* &head, int pos) {

    if (!head || pos < 0) return false;

    Node* curr = head;
    int index = 0;

    while (curr && index < pos) {
        curr = curr->next;
        index++;
    }

    if (!curr) return false; 

    if (curr == head) return true;

    Node* prevPart = curr->prev;
    Node* last = curr;

    while (last->next) 
    {
        last = last->next;
    }

    prevPart->next = NULL;  // removing old link
    curr->prev = NULL;      // new head

    last->next = head;      
    head->prev = last;

    head = curr;
    return true;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {

    int arr[] = {11,3,8,2,1};

    Node* head = new Node(arr[0]);
    Node* curr = head;

    for (int i = 1; i < 5; i++) {
        Node* temp = new Node(arr[i]);
        curr->next = temp;
        temp->prev = curr;
        curr = temp;
    }

    cout << "Original: ";
    printList(head);

    positionHead(head, 3);      

    cout << "After positionHead(3): ";
    printList(head);

    return 0;
}

