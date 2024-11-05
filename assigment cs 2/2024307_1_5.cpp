#include <iostream>
using namespace std;

int main(){

    float distance;
    float cd70;
    float cg125;
    cout<<"input distance in kms: ";
    cin>> distance;
    cd70 = distance/50.2;
    cg125 =distance/40.5;

    cout<<"petrol needed for cd70: " <<cd70<< endl;
    cout<<"petrol needed for cg125: " <<cg125<<endl;

    return 0;
}