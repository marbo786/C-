#include <iostream>
using namespace std;
int nSum(int n) 
{ 
    // base condition to terminate the recursion when N = 0 
    if (n == 0) { 
        return 0; 
    } 
  
    // recursive case / recursive call 
    int res = n + nSum(n - 1); 
  
    return res; 
} 
int main() {
 
  int num;

   cout<<"Enter number  ";
   cin >> num;

   
 
   cout << "Sum of all below number upto "<<num<<" is " << nSum(num);
 
   return 0;
}
