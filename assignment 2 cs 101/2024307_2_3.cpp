#include <iostream>
using namespace std;

int main() {

    int box[36] = {
        1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18,
        19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30,
        31, 32, 33, 34, 35, 36
    };

    int num1, num2;
    cout << "Enter two numbers between 1 and 36: ";
    cin >> num1 >> num2;

    if (num1 < 1 || num1 > 36 || num2 < 1 || num2 > 36) {
        cout << "Numbers must be between 1 and 36." << endl;
        return 1;
    }

    char coloura, colourb;

    // Determine color for num1
    if (box[num1 - 1] == 2 || box[num1 - 1] == 11 || box[num1 - 1] == 13 ||
        box[num1 - 1] == 18 || box[num1 - 1] == 19 || box[num1 - 1] == 24 ||
        box[num1 - 1] == 29 || box[num1 - 1] == 32) {
        coloura = 'r';
    } else if (box[num1 - 1] == 1 || box[num1 - 1] == 6 || box[num1 - 1] == 7 ||
               box[num1 - 1] == 12 || box[num1 - 1] == 17 || box[num1 - 1] == 20 ||
               box[num1 - 1] == 28 || box[num1 - 1] == 33) {
        coloura = 'g';
    } else if (box[num1 - 1] == 5 || box[num1 - 1] == 8 || box[num1 - 1] == 16 ||
               box[num1 - 1] == 21 || box[num1 - 1] == 27 || box[num1 - 1] == 34) {
        coloura = 'p';
    } else if (box[num1 - 1] == 4 || box[num1 - 1] == 9 || box[num1 - 1] == 15 ||
               box[num1 - 1] == 22 || box[num1 - 1] == 26 || box[num1 - 1] == 35) {
        coloura = 'o';
    } else if (box[num1 - 1] == 3 || box[num1 - 1] == 10 || box[num1 - 1] == 14 ||
               box[num1 - 1] == 23 || box[num1 - 1] == 25 || box[num1 - 1] == 30 ||
               box[num1 - 1] == 31 || box[num1 - 1] == 36) {
        coloura = 'b';
    }

    // Determine color for num2
    if (box[num2 - 1] == 2 || box[num2 - 1] == 11 || box[num2 - 1] == 13 ||
        box[num2 - 1] == 18 || box[num2 - 1] == 19 || box[num2 - 1] == 24 ||
        box[num2 - 1] == 29 || box[num2 - 1] == 32) {
        colourb = 'r';
    } else if (box[num2 - 1] == 1 || box[num2 - 1] == 6 || box[num2 - 1] == 7 ||
               box[num2 - 1] == 12 || box[num2 - 1] == 17 || box[num2 - 1] == 20 ||
               box[num2 - 1] == 28 || box[num2 - 1] == 33) {
        colourb = 'g';
    } else if (box[num2 - 1] == 5 || box[num2 - 1] == 8 || box[num2 - 1] == 16 ||
               box[num2 - 1] == 21 || box[num2 - 1] == 27 || box[num2 - 1] == 34) {
        colourb = 'p';
    } else if (box[num2 - 1] == 4 || box[num2 - 1] == 9 || box[num2 - 1] == 15 ||
               box[num2 - 1] == 22 || box[num2 - 1] == 26 || box[num2 - 1] == 35) {
        colourb = 'o';
    } else if (box[num2 - 1] == 3 || box[num2 - 1] == 10 || box[num2 - 1] == 14 ||
               box[num2 - 1] == 23 || box[num2 - 1] == 25 || box[num2 - 1] == 30 ||
               box[num2 - 1] == 31 || box[num2 - 1] == 36) {
        colourb = 'b';
    }

    // Compare the colors
    if (coloura == colourb) {
        cout << "Both have the same color." << endl;
    } else {
        cout << "Both do not have the same color." << endl;
    }

    return 0;
}
