#include <iostream>
using namespace std;

int main(){

    float housea,transporta,medicala,grossa,houseb,transportb,medicalb,grossb,netdiff;
    int basicsalary;
    cout<<"enter your basic salary: ";
    cin>>basicsalary;
    housea = basicsalary*0.3;
    transporta = basicsalary*0.1;
    medicala = basicsalary*0.25;
    grossa = basicsalary + housea + transporta + medicala;

    houseb = basicsalary*0.4;
    transportb = basicsalary*0.15;
    medicalb = basicsalary*0.35;
    grossb = basicsalary + houseb + transportb +medicalb;

    netdiff = grossb - grossa;

    cout<<"net difference between the two salaries is: "<<netdiff<<endl;

    return 0;

}