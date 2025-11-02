#include<iostream>
using namespace std;

void swap(int *,int *);

int main( )

{
	int a = 10, b = 20;
	int *p, *q;
	cout<<"Before Swapping: ";
	cout<<"a: "<<a<<"\tb: "<<b<<endl;
	p = &a;
	q = &b;
	swap( p, q) ;
	cout<<"\nAfter Swapping: ";
	cout<<"a: "<<a<<"\tb: "<<b<<endl;
	

}
void swap( int *x, int *y )

{
	int  t = *x ;
	*x = *y;
	*y = t;
}


