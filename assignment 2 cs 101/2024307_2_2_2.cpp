#include <iostream>
using namespace std;

int main() {
    for (int base = 0;base < 16;base ++) {  
        if (base < 15) {  
            int stepNum = base/3;  
            int lastSpace;

            
            for (int extSpace = 0;extSpace < (25 - stepNum * 5);extSpace++)
            {
                cout <<" ";
                lastSpace = extSpace;
            }

            cout <<"*";  

            int rem = base % 3;  
            if (rem == 0)
            {  
                cout <<"*****";  
            } else {
                cout <<"     ";  
            }

            
            for (int Space = 0; Space < (24 - lastSpace); Space++)
            {
                cout <<" ";
            }

            cout <<"*"; 
        } 
        else {  
            for (int m = 0; m < 32; m++)
            {
                cout <<"*";
            }
        }

        cout <<endl;  
    }

    return 0;
}
