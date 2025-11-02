#include <iostream>
using namespace std;

int main()
{
	//diff ways to initialize char array
	
	//char v[3] = "asd"; //not valid in C++, valid in ISO C because four elements are required
   	
	char v[4] = "asd"; //valid in C++
    cout<<v<<endl;
	cout<<"Size of v: "<<sizeof(v)<<endl;
	
	char myword[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
	cout<<myword<<endl;
	
	char myword2[] = "Hello"; 
	cout<<myword2<<endl;

	char ch_arr[100];
	 //for entrire line including space until the new line character \n is found
    cout << "Enter a string: ";
    cin.get(ch_arr, 100);
    cout << "You entered: " << ch_arr << endl;

    return 0;
}
