#include <iostream>
using namespace std;

// ---------------- QUEUE IMPLEMENTATION ----------------
class Queue {
    int *arr;
    int front, rear, size, count;

public:
    Queue(int s = 100) {
        size = s;
        arr = new int[size];
        front = 0;
        rear = -1;
        count = 0;
    }

    // Enqueue (insert at rear)
    void enqueue(int value) {
        if (count == size) {
            cout << "Queue Overflow!\n";
            return;
        }
        rear = (rear + 1) % size;
        arr[rear] = value;
        count++;
    }

    // Dequeue (remove from front)
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!\n";
            return -1;
        }
        int val = arr[front];
        front = (front + 1) % size;
        count--;
        return val;
    }

    // Peek (front element)
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return -1;
        }
        return arr[front];
    }

    // Check if queue is empty
    bool isEmpty() {
        return count == 0;
    }

    // Get number of elements
    int getCount() {
        return count;
    }

    // Display queue elements
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        cout << "Queue: ";
        for (int i = 0; i < count; i++) {
            cout << arr[(front + i) % size] << " ";
        }
        cout << endl;
    }

    ~Queue() {
        delete[] arr;
    }
};

// ---------------- STACK USING TWO QUEUES ----------------
class Stack {
    Queue q1, q2;
    int capacity;

public:
    Stack(int size = 100) : q1(size), q2(size), capacity(size) {}

    // Push operation — O(n)
    void push(int value) {
        cout << value << " pushed onto stack\n";

        // Step 1: enqueue new element into q2
        q2.enqueue(value);

        // Step 2: move all elements from q1 → q2
        while (!q1.isEmpty()) {
            q2.enqueue(q1.dequeue());
        }

        // Step 3: swap q1 and q2
        Queue temp = q1;
        q1 = q2;
        q2 = temp;
    }

    // Pop operation — O(1)
    void pop() {
        if (q1.isEmpty()) {
            cout << "Stack Underflow!\n";
            return;
        }
        int removed = q1.dequeue();
        cout << removed << " popped from stack\n";
    }

    // Peek (top element)
    void peek() {
        if (q1.isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }
        cout << "Top element: " << q1.peek() << endl;
    }

    // Display all stack elements
    void display() {
        if (q1.isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }

        cout << "Stack elements (top to bottom): ";
        for (int i = 0; i < q1.getCount(); i++) {
            cout << q1.peek() << " ";
            int val = q1.dequeue();
            q1.enqueue(val);
        }
        cout << endl;
    }
};

// ---------------- DRIVER CODE ----------------
int main() {
    Stack s(10);

    s.push(10);
    s.push(20);
    s.push(30);
    s.display();

    s.peek();
    s.pop();
    s.display();

    s.push(40);
    s.display();

    s.peek();
}
