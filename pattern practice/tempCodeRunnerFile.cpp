#include <iostream>

using namespace std;

int main() {
    // Character array holding the text
    char text[] = {'t', 's', 'e', 'b', 's', 'i', 'C', 'i', 's', 'b', 'e', 's', 't'};
    
    // Printing the upper part of the pattern
    for (int i = 6; i >= 0; --i) {  // Start from index 6 and go downwards
        // Print spaces for alignment
        for (int j = 0; j < i; ++j) {
            cout << " ";
        }
        // Print the left side characters
        cout << text[6 - i]; // Ascending in array

        // If it's not the first line, print spaces between characters
        if (i != 6) {
            for (int j = 0; j < 2 * (6 - i) - 1; ++j) {
                cout << " ";
            }
            // Print the right side character (same as the left side)
            cout << text[6 - i];
        }
        cout << endl;
    }
    
    // Printing the bottom line of the pattern
    for (int i = 0; i < 13; ++i) {  // The bottom line has 13 characters (full array)
        cout << text[i] << " ";
    }
    cout << endl;

    return 0;
}
