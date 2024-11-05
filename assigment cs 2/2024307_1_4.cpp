#include <iostream>
using namespace std;

int main(){


    int age,months,days;

    cout<<"enter age in years: ";
    cin>>age;

    days = age * 365;
    months = age * 12;

    cout<<"your age in months is: " <<months<<endl;
    cout<<"your age in days is: " <<days<<endl;
    return 0;
}