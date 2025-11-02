/*	

4 Types of user defined functions
	1. Function with no arguments and no return value
	2. Function with no arguments and a return value
	3. Function with arguments and no return value
	4. Function with arguments and a return value
	
	
Type 1: 

In the following program, prime() is called from the main() with 0no arguments.
prime() takes the positive number from the user and checks whether the number is a prime number or not.
Since, return type of prime() is void, no value is returned from the function.
 */
 
 # include <iostream>
using namespace std;

void prime();

int main()
{
    // No argument is passed to prime()
    prime();
    return 0;
}

// Return type of function is void because value is not returned.
void prime()
{
    int num, i, flag = 0;
    cout << "Enter a positive integer enter to check: ";
    cin >> num;

    for(i = 2; i <= num/2; ++i)
    {
        if(num % i == 0)
        {
            flag = 1; 
            break;
        }
    }
    if (flag == 1)
    {
        cout << num << " is not a prime number.";
    }
    else
    {
        cout << num << " is a prime number.";
    }
}

