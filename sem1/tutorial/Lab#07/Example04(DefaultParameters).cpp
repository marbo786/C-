/*Construct a C++ module that calculates volume of a box (as given by formula below). Program must have two functions; Main and showVolume. Main accepts length, width, height from the user and send them as an arguments in function call. Taking Length as an input is mandatory but Width and Height are optional. Function showVolume must implement default values for width and height as 5, in case of no width and height values provided by user. 
Box_Volume = Length*Width*Height
*/

#include <iostream>
using namespace std;

void showVolume(int l, int w = 5, int h = 5);
int main()
{

	int length,width,height;
	char ch;
	cout<<"For calculating Box Volume"<<endl;
	cout<<"Enter length: ";
	cin>>length;
	cout<<endl<<"Do you have value of both width and height? (y/n)";
	cin>>ch;
	if(ch=='y'){
		cout<<"Enter Width: ";
		cin>>width;
		cout<<"Enter height: ";
		cin>>height;
		showVolume(length,width,height);
	} else {
		cout<<"Width(default)=5\nHeight(default)=5\n";
		showVolume(length);
	}
	return 0;
}
void showVolume(int l, int w, int h)
{
	int volume;
	volume=l*w*h;
	cout<<endl<<"Box Volume:"<<volume;
}

