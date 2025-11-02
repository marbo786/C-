#include <iostream>
#include <string>
using namespace std;


union salarydetails {

    double monthlysalary;

    struct{

        double hourlyrate;
        int hoursworked;

        double hourlydetails;
    };
};

class employee {

public:

    string name;
    int employeeid;
    bool issalaried;
    void displaysalary()
    {

        cout << "Employee Name: " << name << endl;
        cout << "Employee ID: " << employeeid << endl;
        if (issalaried) 
        {
            cout << "Salary Type: Salaried" << endl;
            cout << "Monthly Salary: " << salary.monthlysalary << endl;
        } else 
        {
            cout << "Salary Type: Hourly" << endl;
            cout << "Hourly Rate: " << salary.hourlyrate << endl;
            cout << "Hours Worked: " << salary.hoursworked << endl;
            cout << "Total Earnings: " << salary.hourlydetails << endl;
        }
    }
    salarydetails salary;

};


int main(){

    
    employee jbh;
    int id;
    string name;
    bool type;


    cout<<"add employee name: "<<endl;
    getline(cin,jbh.name);

    cout<<"add employee id: "<<endl;
    cin>>jbh.employeeid;

    cout<<"is the employee salaried or works hourly (1 for true 0 for false)"<<endl;
    cin>>jbh.issalaried;


    if(jbh.issalaried){

        jbh.salary.monthlysalary = 50000;
    }
    else{
        cout<<"Enter no of hours worked: ";
        cin>>jbh.salary.hoursworked;
        

        cout<<"set minimum wage for 1 hour: ";
        cin>>jbh.salary.hourlyrate;
        


        jbh.salary.hourlydetails = jbh.salary.hourlyrate*jbh.salary.hoursworked;
        
    }

    jbh.displaysalary();

    return 0;
    
}