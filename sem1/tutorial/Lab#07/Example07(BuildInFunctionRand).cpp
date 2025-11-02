/*Design a C++ program that generate 10 random numbers using rand() function defined in the library <cstdlib>.
 Use pseudo-random number generator to generate a different succession of results in the subsequent calls to rand.
 Ask for max range up to that random numbers should be generated. Display the numbers and give a check for prime number (if any), 
 maximum & minimum in the list. 
 Apply maximum modularity in your code using functions in which arguments should be used as passed by reference.


*/



#include <iostream>
#include <cstdlib>
#include<time.h>
using namespace std;

void is_prime(int &num){
	bool flag;
	for(int j = 2; j <=(num/2); ++j) 
        if(num%j==0) 
				flag =1;
	if(flag==0) 
		cout<<"   is prime number";
}


int main()
{
    int num, range, min, max;
	srand(time(NULL));
 	cout<<"Enter max range for random numbers... ";
 	cin>>range;
 	cout<<endl;
	 max=0;
 	min=range;
   for (int i = 1; i <= 10; i++)
   {
      	num = rand() % range +1;
     	 cout<<num;
	  
	  	is_prime(num);
	   
	  	if(num>max) 
	  		max=num;
		
		if(num<min) 
	  		min = num;
	  	cout<<endl;	
   }
   cout<<"\nMax number is "<<max<<endl;
   cout<<"Min number is "<<min<<endl;
 
   return 0;
}
	

