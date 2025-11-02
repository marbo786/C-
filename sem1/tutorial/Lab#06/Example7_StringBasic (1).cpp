
// C++ code to demonstrate the working of string functions

#include<iostream> 
#include<string> // for string class 
using namespace std; 
int main() 
{ 
    // Declaring string 
    string str; 
  	cout<<"Enter random string..";
    // Taking string input using getline() 
     
    getline(cin,str); 
  
    // Displaying string 
    cout << "The initial string is : "; 
    cout << str << endl; 
  
    // Using push_back() to insert a characters at end 
    // pushes 's' in this case 
    str.push_back('s'); 
  
    // Displaying string 
    cout << "The string after push_back operation is : "; 
    cout << str << endl; 
  
    // Using pop_back() to delete a character 
    // from end 
    // pops 's' in this case 
   // str.pop_back();
  
    // Displaying string 
   // cout << "The string after pop_back operation is : "; 
    //cout << str << endl; 
 	
	//String concatenation
  	string firstName = "Ahmad";
  	string lastName = "Ali";
	string fullname = firstName +" "+lastName;
  	cout<<endl<<"Full name = "<<fullname;
  	
    //string length() or size() funct
	cout<<endl<<"Full Name (length)="<<fullname.length()<<endl;
	
	//find(string) returns the integer index of the first occurance of the specified sting
	//and returns -1 in case of not found
	cout<<endl<<"Ali in full name starts from index: "<<fullname.find("Ali");
	
	//string erase(index) will erase all remaining characters after specified index
	cout<<endl<<"Removing last name from index 5="<<fullname.erase(6);
	
	//insert(index,str) insert the specified string at specified index
	cout<<endl<<"Inserting last name again to fullname="<<fullname.insert(6,"Ali");
	
	//replace(index,n,str) removes n characters in the string from the specified index and insert str
	cout<<endl<<"Replacing last name Ali from Hassan="<<fullname.replace(6,10,"Hassan");
	return 0; 
  
} 

