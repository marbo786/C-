#include <iostream>
using namespace std;
int main()
{
	int age[4]; //array ‘age’ of 4 ints 
	for(int j=0; j<4; j++) //get 4 ages
	{
		cout << "Enter an age: ";
		cin >> age[j]; //access array element
	}
	
	for(int i=0; i<4; i++) //display 4 ages
	cout << "You entered " << age[i] << endl; 
	return 0;
}
