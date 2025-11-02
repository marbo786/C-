//by changing the type of arguments


#include <iostream>
using namespace std;
int add(int a, int b) // first definition
{
	cout<<"Function 1 "<<endl;
	cout<< a+b << endl<<endl;
	return 0;
}
float add(float a, float b)
{
	cout<<"Function 2 "<<endl;
	cout << a+b << endl<<endl;
	return 0;
}
int add(double a, double b)
{
	cout<<"Function 3 "<<endl;
	cout << a+b << endl <<endl;
	return 0;
}
int main()
{
	add(20, 40);
	add(23.45, 34.5);
	add(40.24, 20.433);
}
