//by changing the number of arguments 

#include <iostream>
using namespace std;

int add(int a, int b)
{
	int sum =  a+b ;
	return sum;
}


float add(int a, int b, float c)
{	
	float add = a+b+c;
	return add;
}


int main()
{
	int var1,var2;
	var1 = 12;
	var2 = 4;
	
	float var3;
	var3 =14.5;
	
	int result1 =add(var1, var2);
	cout<<"Result from 1st definition: "<<result1<<endl<<endl;
	
	float result2 = add(var1, var2, var3);
	cout<<"Result from 2nd definition: "<<result2<<endl;
}
