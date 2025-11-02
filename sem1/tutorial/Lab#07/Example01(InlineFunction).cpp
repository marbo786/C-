#include <iostream>
 
using namespace std;

inline int Max(int x, int y) {
   return (x > y)? x : y;
}

// Main function for the program
int main() {
   cout << "Max (20,10): " << Max(20,10) << endl;
   cout << "Max (0,200): " << Max(0,200) << endl;
   cout << "Max (100,1010): " << Max(100,1010) << endl;
   
   return 0;
}
/*
1) When a function with a return statement is not returning any value and marked as inline
2) When a programmer tries to inline a function containing a loop (for, while, or do-while)
3) A function containing static variables cannot be made an inline function. 
4) If it contains any switch or go-to statements.

*/
