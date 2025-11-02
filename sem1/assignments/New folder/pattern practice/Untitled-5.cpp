#include <iostream>
using namespace std;

int main() {
    
    for (int i = 0; i < 32; i++) {
        cout << "*";
    }
    
    
    cout << endl;

    
    for (int i = 0; i < 16; i++) {
        
        for (int j = 0; j < 31; j++) {
            cout << " ";
        }
       
        cout << "*" << endl;
    }

    return 0;
}
