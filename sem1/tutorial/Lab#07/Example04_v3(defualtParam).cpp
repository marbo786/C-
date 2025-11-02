//If the function is overloaded with different data types that also contain the default arguments, it may result in an ambiguous match, which results in an error.


#include<iostream>  
using namespace std;

  
int sum(int x, int y, int z=0, int w=0) // Here there are two values in the default arguments   
{ // Both z and w are initialised to zero   
    return (x + y + z + w); // return sum of all parameter values  
}  

int sum(int x, int y, float z=0, float w=0) // Here sum is overloaded with two float parameter values   
{ // This results in ambiguity   
    return (x + y + z + w);  
} 
 
int main()  
{  
    //cout << sum(10, 15) << endl; // x = 10, y = 15, z = 0, w = 0  
    cout << sum(10, 15, 25) << endl; // x = 10, y = 15, z = 25, w = 0  
    cout << sum(10, 15, 25, 30) << endl; // x = 10, y = 15, z = 25, w = 30  
    return 0;  
}  
