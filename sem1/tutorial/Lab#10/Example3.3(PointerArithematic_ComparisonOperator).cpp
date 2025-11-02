/*  Pointer Comparisons : InfoBrother*/
 
#include<iostream> 
using namespace std;
main()
{
   int var[5] = {10,20,30,40,50}; //Array Declaration.
   int *ptr; //pointer point to int.
 
   ptr = var; //ptr point to the first address of Array:
   int i=0; //Variable to use in while loop:
 
   
      for(int i=0; ptr<=&var[4]; ptr++, i++)
      {
	 cout << "\n Address of var[" << i << "] = " 
	      <<ptr<<endl; //show the Address:
 
    	 cout << "Value of var[" << i << "] = "
	      <<*ptr<<endl; //show the value:
 
	 

    }
 
    return 0;
}


