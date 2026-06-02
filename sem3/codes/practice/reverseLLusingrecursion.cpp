#include <iostream>
using namespace std;

// Node structure
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = NULL;
    }
};

// Linked List class
class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = NULL;
    }

    // Insert at end
    void pushBack(int value) {
        Node* newNode = new Node(value);
        if (head == NULL) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    // Display list
    void display() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Recursive reverse helper
    Node* reverseRecursive(Node* curr) {
        // Base case: empty list or last node
        if (curr == NULL || curr->next == NULL)
            return curr;

        // Recur for the rest of the list
        Node* newHead = reverseRecursive(curr->next);

        // Reverse the link
        curr->next->next = curr;
        curr->next = NULL;

        return newHead;
    }

    // Wrapper function
    void reverse() {
        head = reverseRecursive(head);
    }
};

// ---------------- DRIVER CODE ----------------
int main() {
    LinkedList list;

    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushBack(40);

    cout << "Original List: ";
    list.display();

    list.reverse();

    cout << "Reversed List: ";
    list.display();

    return 0;
}
