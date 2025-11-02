/*generate 10 random numbers between 10 and 55 inclusive, without repetition of the sequence between program runs*/

#include <iostream.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
     // to prevent sequence repetition between runs     
     srand(time(NULL));  

  
     for(int i = 1; i <=10; i++)     // looping to print 10 numbers
     {
           cout<< 10 + rand( ) % 46;   // formula for numbers 
     }

     return 0;
}

/*random integers between 35 and 42 inclusive*/

//int num =35+rand( )% 8;
/*Generating random numbers within a specified range:
  In order to produce random integer numbers within a specified range, you need to manipulate the rand( ) function. 
 The formula is:

int number = a + rand( ) % n;

a = the first number in your range
n = the remaining number of terms in your range
(range computed by n= ((largest value - smallest value) + 1)  */
//Like we want to generate a random number between 1-6 then we use this function like -

//Num = 1+ rand() % 6;
