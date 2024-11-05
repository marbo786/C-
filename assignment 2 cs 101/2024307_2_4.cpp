#include <iostream>
#include <bitset> // needed to present the value in binary format.
using namespace std;

// Function to convert binary to Gray code
unsigned int bintoG(unsigned int num) {
    // the ^ operator is for xor gate which only returns 1 if the bits are different
    // the >> operator is used to perform right shift which is a common operation used to divide in binary.
    return num ^ (num >> 1);
}

int main() {
    unsigned int num;

    cout << "input a non-zero 16-bit integer: ";
    cin >> num;

    //  number is within the 16-bit range check
    if (num == 0 || num > 65535) {
        cout << "input a non-zero 16-bit integer (1 to 65535).\n";
        return 1;
    }

    
    unsigned int grayCode = bintoG(num);

    // Display the Gray code in binary format
    cout << "Gray code in binary: " << bitset<16>(grayCode)<<endl;

    return 0;
}