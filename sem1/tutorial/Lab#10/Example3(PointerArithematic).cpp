/* Incrementing a Pointer : InfoBrother*/
 
#include<iostream> 
using namespace std;
main()
{
	int var[5] = {10,20,30,40,50}; //Array Declaration.
	int *ptr; //pointer point to int.
 
	ptr = var; // let us have array address in pointer.
 
	for (int i = 0; i < 5; i++) //Loop to show Address and Value:
	{
	   cout << "\n Address of var[" << i << "] = " <<ptr<<endl; //show the Address:
   	   cout << "Value of var[" << i << "] = "<<*ptr<<endl; //show the value:
 
           ptr++; // point to the next location (incrementation)
	}
 
	return 0;
}
