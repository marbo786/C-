#include <iostream>
using namespace std;

class CircularQueue {
private:
    int front, rear, size;
    int* arr;

public:
    // Constructor
    CircularQueue(int s) {
        size = s;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    // Check if queue is full
    bool isFull() {
        return ((rear + 1) % size == front);
    }

    // Check if queue is empty
    bool isEmpty() {
        return (front == -1);
    }

    // Enqueue operation
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot insert " << value << endl;
            return;
        }

        // First element insertion
        if (front == -1)
            front = 0;

        rear = (rear + 1) % size;
        arr[rear] = value;

        cout << value << " enqueued into the queue.\n";
    }

    // Dequeue operation
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! Nothing to remove.\n";
            return;
        }

        cout << arr[front] << " dequeued from the queue.\n";

        // If the queue becomes empty after this operation
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % size;
        }
    }

    // Peek operation
    void peek() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Front element: " << arr[front] << endl;
    }

    // Display all elements
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Queue elements: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear)
                break;
            i = (i + 1) % size;
        }
        cout << endl;
    }

    // Destructor
    ~CircularQueue() {
        delete[] arr;
    }
};

// ----------------------
// Test the Circular Queue
// ----------------------
int main() {
    CircularQueue q(5);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();

    q.dequeue();
    q.dequeue();
    q.display();

    q.enqueue(50);
    q.enqueue(60); // wrap-around happens here
    q.display();

    q.peek();

    q.enqueue(70); // should show overflow if queue is full

    return 0;
}
