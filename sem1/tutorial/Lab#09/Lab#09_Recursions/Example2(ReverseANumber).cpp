#include <iostream>
using namespace std;

int reverseNumber(int n) {
 
   static int temp=0;
   static int sum=0;
 
   if(n>0){
  
      temp = n%10; //separate out one last digit and store that in temp
     			   //e.g. 256%10 =6
	  sum = sum*10 + temp; //e.g. sum=6
     			   
      reverseNumber(n/10); //e.g. 256/10 =25


   } else {
  
     return sum;
   }
 
}

int main() {
 
  int n,reverse;

   cout<<"Enter number";
   cin >> n;

   reverse = reverseNumber(n);
 
   cout << "Reverse of number is" << reverse;
 
   return 0;
}
