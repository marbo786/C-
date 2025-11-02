/* Decrementing a Pointer : InfoBrother*/
 
#include<iostream> 
using namespace std;
main()
{
    int var[5] = {10,20,30,40,50}; //Array Declaration.
    int *ptr; //pointer point to int.
 
    ptr = &var[4]; //ptr point to the last address of Array:
 
    for (int i = 5; i > 0; i--) //Loop to show Address and Value:
    {
 	cout << "\n Address of var[" << i << "] = " <<ptr<<endl; //show the Address:
    	cout << "Value of var[" << i << "] = "<<*ptr<<endl; //show the value:
 
    	ptr--; // point to the Previous location:
     }
 
     return 0;
}
