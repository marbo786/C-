#include <iostream>
using namespace std;

// ---------------------------
// Stack Implementation
// ---------------------------
class Stack {
    int arr[100];
    int top;

public:
    Stack() {
        top = -1;
    }

    void push(int val) {
        if (top == 99) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++top] = val;
    }

    int pop() {
        if (top == -1) {
            cout << "Stack Underflow!" << endl;
            return -1;
        }
        return arr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }
};

// ---------------------------
// Queue Implementation
// ---------------------------
class Queue {
    int arr[100];
    int front, rear, size;

public:
    Queue() {
        front = -1;
        rear = -1;
        size = 0;
    }

    void enqueue(int val) {
        if (rear == 99) {
            cout << "Queue Overflow!" << endl;
            return;
        }
        if (front == -1) front = 0;
        arr[++rear] = val;
        size++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!" << endl;
            return -1;
        }
        int val = arr[front++];
        size--;
        if (front > rear) { // Reset when empty
            front = rear = -1;
            size = 0;
        }
        return val;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return arr[front];
    }

    bool isEmpty() {
        return (front == -1 || front > rear);
    }

    int getSize() {
        return size;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Function to reverse first K elements
    void reverseFirstK(int k) {
        if (isEmpty() || k > size || k <= 0) {
            cout << "Invalid value of K!" << endl;
            return;
        }

        Stack s;

        // Step 1: Push first K elements into stack
        for (int i = 0; i < k; i++) {
            s.push(dequeue());
        }

        // Step 2: Pop from stack and enqueue back (reversed order)
        while (!s.isEmpty()) {
            enqueue(s.pop());
        }

        // Step 3: Move the remaining (size - k) elements to back
        int rem = size - k;
        for (int i = 0; i < rem; i++) {
            enqueue(dequeue());
        }
    }
};

// ---------------------------
// Main Function
// ---------------------------
int main() {
    Queue q;
    int n, val, k;

    cout << "Enter number of elements in queue: ";
    cin >> n;

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        q.enqueue(val);
    }

    cout << "Enter K: ";
    cin >> k;

    cout << "\nOriginal Queue: ";
    q.display();

    q.reverseFirstK(k);

    cout << "Queue after reversing first " << k << " elements: ";
    q.display();

    return 0;
}
