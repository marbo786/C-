#include <iostream>
using namespace std;

// ---------------- STACK IMPLEMENTATION ----------------
class Stack {
    int *arr;
    int top;
    int size;

public:
    Stack(int s = 100) {
        size = s;
        arr = new int[size];
        top = -1;
    }

    // Push element into stack
    void push(int value) {
        if (top == size - 1) {
            cout << "Stack Overflow!\n";
            return;
        }
        arr[++top] = value;
    }

    // Pop element from stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return -1;
        }
        return arr[top--];
    }

    // Peek top element
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        return arr[top];
    }

    // Check if stack is empty
    bool isEmpty() {
        return top == -1;
    }

    // Display all elements
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~Stack() {
        delete[] arr;
    }
};

// ---------------- QUEUE USING TWO STACKS ----------------
class Queue {
    Stack s1, s2; // two stacks
    int capacity;

public:
    Queue(int size = 100) : s1(size), s2(size), capacity(size) {}

    // Enqueue operation (O(1))
    void enqueue(int value) {
        s1.push(value);
        cout << value << " enqueued into queue\n";
    }

    // Dequeue operation (O(n) in worst case)
    void dequeue() {
        if (s1.isEmpty() && s2.isEmpty()) {
            cout << "Queue is empty! Cannot dequeue.\n";
            return;
        }

        // Move elements to s2 only if it's empty
        if (s2.isEmpty()) {
            while (!s1.isEmpty()) {
                s2.push(s1.pop());
            }
        }

        int removed = s2.pop();
        cout << removed << " dequeued from queue\n";
    }

    // Peek (front element)
    void peek() {
        if (s1.isEmpty() && s2.isEmpty()) {
            cout << "Queue is empty! Nothing to peek.\n";
            return;
        }

        if (s2.isEmpty()) {
            while (!s1.isEmpty()) {
                s2.push(s1.pop());
            }
        }

        cout << "Front element: " << s2.peek() << endl;
    }

    // Display queue elements in order
    void display() {
        if (s1.isEmpty() && s2.isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        // Temporary stacks for printing
        Stack temp1 = s1, temp2 = s2;

        cout << "Queue elements: ";

        // Elements already in correct order in s2
        for (int i = 0; !temp2.isEmpty(); i++) {
            cout << temp2.pop() << " ";
        }

        // Reverse s1 to show correct order
        Stack rev;
        while (!temp1.isEmpty()) {
            rev.push(temp1.pop());
        }

        while (!rev.isEmpty()) {
            cout << rev.pop() << " ";
        }

        cout << endl;
    }
};

// ---------------- DRIVER CODE ----------------
int main() {
    Queue q(10);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();

    q.peek();
    q.dequeue();
    q.display();

    q.enqueue(40);
    q.enqueue(50);
    q.display();

    q.peek();
}
