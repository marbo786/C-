#include <iostream>
using namespace std;

int main(){

    float radius;
    float area;
    float circumference;
    

    cout<<"input the radius: ";
    cin>> radius;
    area = 4*3.14*radius*radius;
    circumference = (4*3.14*radius*radius*radius)/3;

    cout<< "the circumference is: "<<circumference<<endl;
    cout << "the area is: "<<area<<endl;

    return 0;
}