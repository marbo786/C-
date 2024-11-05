#include <iostream>
using namespace std;

int main()
{
    int num;
    int reversenum = 0;

    cout<<"input the num you want to reverse: ";
    cin>>num;

    while(num>0){
        // getting the last digit from user entered num
        int x = num%10;
        reversenum = reversenum*10+ x;
        // removing that last digit from num
        num = num/10;
    }
    cout<<"the reverse num is: "<<reversenum;
    return 0;
}