// Stack with Dynamic Memory Allocation with Arrays & Class Objects
// (it will be done using new keyword)Run C++ Program

#include <iostream>
using namespace std;

class Stack {
private:
    int top;         // Index of the top element in the stack
    int maxSize;     // Maximum size of the stack
    int* stackArray; // Pointer to dynamically allocated array for the stack

public:
    // Constructor to initialize stack with given size
    Stack(int size) {
        maxSize = size;
        stackArray = new int[maxSize];
        top = -1;  // Initialize top to -1 indicating an empty stack
    }

    // Destructor to free up dynamically allocated memory
    ~Stack() {
        delete[] stackArray;
    }

    // Push element onto stack
    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push " << value << endl;
        } else {
            stackArray[++top] = value;
            cout << value << " pushed onto the stack." << endl;
        }
    }

    // Pop element from stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Cannot pop element." << endl;
            return -1;  // Return an error value if stack is empty
        } else {
            cout << "Popped element: " << stackArray[top] << endl;
            return stackArray[top--];  // Return top element and decrease top index
        }
    }

    // Peek at the top element without popping it
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        } else {
            return stackArray[top];
        }
    }

    // Check if the stack is empty
    bool isEmpty() {
        return (top == -1);
    }

    // Check if the stack is full
    bool isFull() {
        return (top == maxSize - 1);
    }

    // Get the current size of the stack
    int size() {
        return top + 1;
    }

    // Display all elements in the stack
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
        } else {
            cout << "Stack elements: ";
            for (int i = 0; i <= top; i++) {
                cout << stackArray[i] << " ";
            }
            cout << endl;
        }
    }
};

// Main function to demonstrate stack functionality
int main() {
    int stackSize;
    cout << "Enter the size of the stack: ";
    cin >> stackSize;

    Stack myStack(stackSize);  // Create a stack of user-defined size

    // Push elements
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    
    // Display stack
    myStack.display();

    // Pop elements
    myStack.pop();
    myStack.pop();
    
    // Peek at the top element
    cout << "Top element is: " << myStack.peek() << endl;

    // Display stack size
    cout << "Current stack size: " << myStack.size() << endl;

    // Display remaining stack elements
    myStack.display();

    return 0;
    
}

