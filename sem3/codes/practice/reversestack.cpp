#include <iostream>
#include <string>
using namespace std;

class Stack {
    char arr[100];
    int top;

public:
    Stack() {
        top = -1;
    }

    // Push a character onto the stack
    void push(char ch) {
        if (top == 99) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++top] = ch;
    }

    // Pop a character from the stack
    char pop() {
        if (top == -1) {
            cout << "Stack Underflow!" << endl;
            return '\0';
        }
        return arr[top--];
    }

    // Check if stack is empty
    bool isEmpty() {
        return top == -1;
    }
};

int main() {
    Stack s;
    string str;

    cout << "Enter a string: ";
    getline(cin, str);

    // Push all characters of the string into the stack
    for (char ch : str) {
        s.push(ch);
    }

    // Pop characters to get reversed string
    string reversed = "";
    while (!s.isEmpty()) {
        reversed += s.pop();
    }

    cout << "Reversed string: " << reversed << endl;

    return 0;
}
