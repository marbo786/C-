#include <iostream>
using namespace std;
void cube( int & ); // prototype
int main()
 {
	int number = 5;
	cout << "The original value of number is " << number;
	cube( number ); // pass number by value to cubeByValue
	cout << "\nThe new value of number is " << number << endl;
} // end main

// calculate and return cube of integer argument
void cube( int &n )
{
	n= n * n * n; // cube local variable n and return result
} // end function cubeByValue
