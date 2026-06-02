#include <iostream>
using namespace std;

class Queue {
private:
    int front, rear, size;
    int* arr;

public:
    // Constructor
    Queue(int s) {
        size = s;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    // Enqueue operation (insert element at rear)
    void enqueue(int value) {
        if (rear == size - 1) {
            cout << "Queue Overflow! Cannot insert " << value << endl;
            return;
        }

        if (front == -1) front = 0;  // first element insertion
        arr[++rear] = value;
        cout << value << " enqueued into the queue.\n";
    }

    // Dequeue operation (remove element from front)
    void dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue Underflow! Nothing to remove.\n";
            return;
        }

        cout << arr[front] << " dequeued from the queue.\n";
        front++;

        // Reset when queue becomes empty
        if (front > rear) {
            front = rear = -1;
        }
    }

    // Peek operation (view front element)
    void peek() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Front element: " << arr[front] << endl;
    }

    // Display all elements in the queue
    void display() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Queue elements: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Destructor
    ~Queue() {
        delete[] arr;
    }
};

// ----------------------
// Test the Queue
// ----------------------
int main() {
    Queue q(5); // Queue of size 5

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();

    q.dequeue();
    q.display();

    q.peek();

    q.enqueue(50);
    q.enqueue(60); // Will show overflow if size is exceeded
    q.display();

    return 0;
}
