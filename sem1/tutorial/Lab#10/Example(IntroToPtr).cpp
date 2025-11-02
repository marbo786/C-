// Fig. 8.4: fig08_04.cpp
 // Pointer operators & and *.
#include <iostream>
using namespace std;

int main()
{
	int a = 7; // assigned 7 to a
	int *aPtr = &a; // initialize aPtr with the address of int variable
	
	cout << "The address of a is " << &a;
  	cout<< "\nThe value of aPtr is " <<aPtr ;
 	
	cout << "\n\nThe value of a is " << a;
 	cout << "\nThe value of *aPtr is " << *aPtr<< endl;
 	
 	int firstValue=5, secondValue=15;
 	int *p1, *p2;
 	
 	p1 = &firstValue;  //p1 = address of firstValue
 	p2 = &secondValue;	//p2 = address of secondValue
 	
 	*p1 = 10;		//value pointed by p1 =10
 	*p2 = *p1;		//value pointed by p2 = value pointed by p1
	
	cout<<"\n\nFirst value is "<<firstValue<<endl; //10
	cout<<"Second value is "<<secondValue<<endl;  //10
	
	p1 =p2;     //both are pointing to secondValue
	*p1 =20;    //now updating secondValue to 20
	
	cout<<"\n\nFirst value is "<<firstValue<<endl; // 10
	cout<<"Second value is "<<secondValue<<endl; 	//20
 	
 	return 0;
 } // end main
