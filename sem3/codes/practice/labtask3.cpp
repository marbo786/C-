#include <iostream>
using namespace std;

// ---------------- NODE STRUCTURE ----------------
class Compartment {
public:
    int id;
    int capacity;
    Compartment* next;
    Compartment* prev;

    Compartment(int id, int capacity) {
        this->id = id;
        this->capacity = capacity;
        next = prev = NULL;
    }
};

// ---------------- TRAIN MANAGER CLASS ----------------
class Train {
    Compartment* head;
    Compartment* tail;

public:
    Train() {
        head = tail = NULL;
    }

    // Add compartment at the beginning
    void addAtFront(int id, int capacity) {
        Compartment* newComp = new Compartment(id, capacity);

        if (head == NULL) { // empty train
            head = tail = newComp;
        } else {
            newComp->next = head;
            head->prev = newComp;
            head = newComp;
        }
        cout << "Compartment " << id << " added at front.\n";
    }

    // Add compartment at the end
    void addAtEnd(int id, int capacity) {
        Compartment* newComp = new Compartment(id, capacity);

        if (tail == NULL) { // empty train
            head = tail = newComp;
        } else {
            tail->next = newComp;
            newComp->prev = tail;
            tail = newComp;
        }
        cout << "Compartment " << id << " added at end.\n";
    }

    // Add compartment at a specific position (1-indexed)
    void addAtPosition(int pos, int id, int capacity) {
        if (pos <= 1) {
            addAtFront(id, capacity);
            return;
        }

        Compartment* temp = head;
        int count = 1;

        while (temp != NULL && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == NULL || temp->next == NULL) {
            addAtEnd(id, capacity);
            return;
        }

        Compartment* newComp = new Compartment(id, capacity);
        newComp->next = temp->next;
        newComp->prev = temp;
        temp->next->prev = newComp;
        temp->next = newComp;

        cout << "Compartment " << id << " added at position " << pos << ".\n";
    }

    // Delete compartment from specific position
    void deleteAtPosition(int pos) {
        if (head == NULL) {
            cout << "Train is empty. Nothing to delete.\n";
            return;
        }

        if (pos == 1) { // delete front
            Compartment* temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            else
                tail = NULL;
            cout << "Compartment " << temp->id << " deleted from front.\n";
            delete temp;
            return;
        }

        Compartment* temp = head;
        int count = 1;

        while (temp != NULL && count < pos) {
            temp = temp->next;
            count++;
        }

        if (temp == NULL) {
            cout << "Invalid position!\n";
            return;
        }

        if (temp->next != NULL)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        if (temp->prev != NULL)
            temp->prev->next = temp->next;

        cout << "Compartment " << temp->id << " deleted from position " << pos << ".\n";
        delete temp;
    }

    // Display compartments forward
    void displayForward() {
        if (head == NULL) {
            cout << "Train is empty!\n";
            return;
        }

        Compartment* temp = head;
        cout << "\nTrain (Forward): ";
        while (temp != NULL) {
            cout << "[ID: " << temp->id << ", Cap: " << temp->capacity << "] ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Display compartments backward
    void displayBackward() {
        if (tail == NULL) {
            cout << "Train is empty!\n";
            return;
        }

        Compartment* temp = tail;
        cout << "\nTrain (Backward): ";
        while (temp != NULL) {
            cout << "[ID: " << temp->id << ", Cap: " << temp->capacity << "] ";
            temp = temp->prev;
        }
        cout << endl;
    }

    // Compute total capacity
    void totalCapacity() {
        int total = 0;
        Compartment* temp = head;

        while (temp != NULL) {
            total += temp->capacity;
            temp = temp->next;
        }

        cout << "\nTotal Passenger Capacity of Train: " << total << endl;
    }
};

// ---------------- DRIVER CODE ----------------
int main() {
    Train t;

    t.addAtEnd(101, 50);
    t.addAtEnd(102, 60);
    t.addAtFront(100, 40);
    t.addAtPosition(2, 150, 70);

    t.displayForward();
    t.displayBackward();

    t.totalCapacity();

    t.deleteAtPosition(2);
    t.displayForward();

    t.totalCapacity();

    return 0;
}
