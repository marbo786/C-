#include <iostream>
using namespace std;

// Node structure for the linked list
class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

// Queue class using linked list
class Queue {
private:
    Node* front;
    Node* rear;

public:
    // Constructor
    Queue() {
        front = NULL;
        rear = NULL;
    }

    // Enqueue operation (insert element at rear)
    void enqueue(int val) {
        Node* newNode = new Node(val);

        if (rear == NULL) {  // empty queue
            front = rear = newNode;
            cout << val << " enqueued into the queue.\n";
            return;
        }

        rear->next = newNode;
        rear = newNode;

        cout << val << " enqueued into the queue.\n";
    }

    // Dequeue operation (remove element from front)
    void dequeue() {
        if (front == NULL) {
            cout << "Queue Underflow! Nothing to remove.\n";
            return;
        }

        Node* temp = front;
        cout << temp->data << " dequeued from the queue.\n";
        front = front->next;

        // If queue becomes empty
        if (front == NULL)
            rear = NULL;

        delete temp;
    }

    // Peek operation (view front element)
    void peek() {
        if (front == NULL) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Front element: " << front->data << endl;
    }

    // Display all elements in the queue
    void display() {
        if (front == NULL) {
            cout << "Queue is empty.\n";
            return;
        }

        Node* temp = front;
        cout << "Queue elements: ";
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor
    ~Queue() {
        while (front != NULL) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

// ----------------------
// Test the Queue
// ----------------------
int main() {
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();

    q.dequeue();
    q.display();

    q.peek();

    q.enqueue(50);
    q.display();

    return 0;
}
