#include <iostream>
using namespace std;
#include <math.h>

int main(){

    double x,y,z;
    double d;
    double area;
    cout<<"input x: ";
    cin>>x;
    cout<<"input y: ";
    cin>>y;
    cout<<"input z: ";
    cin>>z;

    d =(x+y+z)/2;

    area = sqrt(d*(d-x)*(d-y)*(d-z));
    cout<<"area is " <<area;

    return 0;

}