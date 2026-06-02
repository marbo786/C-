#include <iostream>
using namespace std;

// ---------------- NODE CLASS ----------------
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

// ---------------- DOUBLY LINKED LIST CLASS ----------------
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Constructor
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // ---------------- PUSH FRONT ----------------
    void pushFront(int val) {
        Node* nn = new Node(val);

        if (head == nullptr) {          // Empty list
            head = tail = nn;
            return;
        }

        nn->next = head;
        head->prev = nn;
        head = nn;
    }

    // ---------------- PUSH BACK ----------------
    void pushBack(int val) {
        Node* nn = new Node(val);

        if (tail == nullptr) {          // Empty list
            head = tail = nn;
            return;
        }

        tail->next = nn;
        nn->prev = tail;
        tail = nn;
    }

    // ---------------- POP FRONT ----------------
    void popFront() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }

        if (head == tail) {             // Only one element
            delete head;
            head = tail = nullptr;
            return;
        }

        Node* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
    }

    // ---------------- POP BACK ----------------
    void popBack() {
        if (tail == nullptr) {
            cout << "List is empty" << endl;
            return;
        }

        if (head == tail) {             // Only one element
            delete tail;
            head = tail = nullptr;
            return;
        }

        Node* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
    }

    // ---------------- INSERT AT POSITION ----------------
    void insertAtPosition(int pos, int val) {
        if (pos <= 1) {
            pushFront(val);
            return;
        }

        Node* temp = head;
        int count = 1;

        while (temp != nullptr && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == nullptr || temp->next == nullptr) {
            pushBack(val);
            return;
        }

        Node* nn = new Node(val);
        nn->next = temp->next;
        nn->prev = temp;

        temp->next->prev = nn;
        temp->next = nn;
    }

    // ---------------- DELETE AT POSITION ----------------
    void deleteAtPosition(int pos) {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }

        if (pos <= 1) {
            popFront();
            return;
        }

        Node* temp = head;
        int count = 1;

        while (temp != nullptr && count < pos) {
            temp = temp->next;
            count++;
        }

        if (temp == nullptr) {
            cout << "Position out of range" << endl;
            return;
        }

        if (temp->next == nullptr) { // last node
            popBack();
            return;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    // ---------------- SEARCH ----------------
    bool search(int key) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == key)
                return true;
            temp = temp->next;
        }
        return false;
    }

    // ---------------- DISPLAY FORWARD ----------------
    void displayForward() {
        Node* temp = head;
        if (!temp) {
            cout << "List is empty" << endl;
            return;
        }

        cout << "Forward: ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // ---------------- DISPLAY BACKWARD ----------------
    void displayBackward() {
        Node* temp = tail;
        if (!temp) {
            cout << "List is empty" << endl;
            return;
        }

        cout << "Backward: ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL" << endl;
    }

    // ---------------- DESTRUCTOR ----------------
    ~DoublyLinkedList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ---------------- MAIN FUNCTION ----------------
int main() {
    DoublyLinkedList dll;

    dll.pushFront(10);
    dll.pushBack(20);
    dll.pushFront(5);
    dll.insertAtPosition(2, 15);
    dll.displayForward();
    dll.displayBackward();

    dll.popFront();
    dll.popBack();
    dll.displayForward();

    dll.deleteAtPosition(2);
    dll.displayForward();

    cout << (dll.search(15) ? "Found" : "Not Found") << endl;
}
