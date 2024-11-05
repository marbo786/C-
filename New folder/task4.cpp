#include <iostream>
using namespace std;

int main()
{
    int tax = 0;
    int salary;
    cout << "Enter your salary: ";
    cin >> salary;
    if (salary >= 50000)
    {
        if (salary > 150000)
        {
            tax = 0.3 * salary;
            cout << tax << endl;
        }
        else
            {

               
            if (salary > 100000 && salary <= 150000)
            {
                tax = 0.2 * salary;
                cout << tax << endl;
            }
            
            else
            {
                tax = 0.1 * salary;
                cout << tax << endl;
            }
            
            }

    }
    else
    {
        
        cout << tax;
    }

    return 0;
}