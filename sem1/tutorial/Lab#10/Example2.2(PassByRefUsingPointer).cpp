#include <iostream>
using namespace std;
void cubeByValue( int * ); // prototype
int main()
 {
	int number = 5;
	cout << "The original value of number is " << number;
	cubeByValue( &number ); // pass number by value to cubeByValue
	cout << "\nThe new value of number is " << number << endl;
} // end main

// calculate and return cube of integer argument
void cubeByValue( int *nPtr )
{
	*nPtr= *nPtr * *nPtr * *nPtr; // cube local variable n and return result
} // end function cubeByValue
