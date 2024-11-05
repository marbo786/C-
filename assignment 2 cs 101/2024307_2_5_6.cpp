#include <iostream>
using namespace std;

float bank[100];
int open[100], pins[100];
int total = 0, manager_pin = 2003;

void create(int value, int pin);
void balance(int acc, int pin);
void deposit(int acc, int value, int pin);
void withdraw(int acc, int value, int pin);
void close(int acc, int pin);
void interest(int rate);

int main()
{
    char type;
    float amount;
    int account, ir, pin; 
    do
    {
        cout << "Transaction Type?: ";
        cin >> type;
        cout << "Pin?: ";
        cin >> pin;
    } while (type != 'S' || pin != manager_pin);

    while (true)
    {

        cout << "Transaction Type?: ";
        cin >> type;
        cout << "Pin?: ";
        cin >> pin;
        if (type == 'E')
        {
            if (pin != manager_pin)
            {
                cout << "You are not authorised to perform this transaction" << endl;
            }
            else
            {
                for (int i = 0; i < 100; i++)
                {
                    bank[i] = 0;
                    open[i] = 0;
                }
                break;
            }
        }
        switch (type)
        {
            case 'O':
                cout << "Initial deposit?: ";
                cin >> amount;
                create(amount, pin);
                break;
            case 'B':
                cout << "Account Number?: ";
                cin >> account;
                balance(account, pin);
                break;
            case 'D':
                cout << "Account Number?: ";
                cin >> account;
                cout << "Amount?: ";
                cin >> amount;
                deposit(account, amount, pin);
                break;
            case 'W':
                cout << "Account Number?: ";
                cin >> account;
                cout << "Amount?: ";
                cin >> amount;
                withdraw(account, amount, pin);
                break;
            case 'C':
                cout << "Account Number?: ";
                cin >> account;
                close(account, pin);
                break;
            case 'I':
                if (pin != manager_pin)
                {
                    cout << "You are not authorised to perform this transaction" << endl;
                }
                else
                {
                    cout << "Interest Rate?: ";
                    cin >> ir;
                    interest(ir);
                }
                break;
            case 'P':
                if (pin != manager_pin)
                {
                    cout << "You are not authorised to perform this transaction" << endl;
                }
                else
                {
                    for (int i = 0; i < 100; i++)
                    {
                        if (open[i] != 0)
                        {
                            cout << "Account Number: " << 1001 + i << " Amount: " << bank[i] << endl;
                        }
                    }
                }
                break;
            
            default:
                cout << "Invalid Type" << endl;
        } 
    }
}

void create(int value, int pin)
{
    if (total == 100)
    {
        cout << "No more slots available" << endl;
    }
    else
    {
        total++;
        int j = 0;
        while (open[j] != 0)
        {
            j++;
        }
        bank[j] = value;
        open[j] = 1;
        pins[j] = pin;
        cout << "Account number: " << 1001 + j << endl;
    }
}

void balance(int acc, int pin)
{
    if (open[acc - 1001] == 0)
    {
        cout << "No account found" << endl;
    }
    else if (pins[acc - 1001] != pin)
    {
        cout << "Incorrect pin" << endl;
    }
    else
    {
        cout << "Account Number: " << acc << endl;
        cout << "Available balance: " << bank[acc - 1001] << endl;
    }
}

void deposit(int acc, int value , int pin)
{
    if (open[acc - 1001] == 0)
    {
        cout << "Account not found";
    }
    else if (pins[acc - 1001] != pin)
    {
        cout << "Incorrect pin" << endl;
    }
    else
    {
        bank[acc - 1001] += value;
        cout << "Account Number: " << acc << endl;
        cout << "Available balance: " << bank[acc - 1001] << endl;
    }
}

void withdraw(int acc, int value, int pin)
{
    if (open[acc - 1001] == 0)
    {
        cout << "Account not found";
    }
    else if (bank[acc - 1001] < value)
    {
        cout << "Insuficient funds";
    }
    else if (pins[acc - 1001] != pin)
    {
        cout << "Incorrect pin" << endl;
    }
    else
    {
        bank[acc - 1001] -= value;
        cout << "Account Number: " << acc << endl;
        cout << "Available balance: " << bank[acc - 1001] << endl;
    }
}

void close(int acc, int pin)
{
    if (open[acc - 1001] == 0)
    {
        cout << "Account not found";
    }
    else if (pins[acc - 1001] != pin)
    {
        cout << "Incorrect pin" << endl;
    }
    else
    {
        open[acc - 1001] = 0;
        bank[acc - 1001] = 0;
        total--;
    }
}

void interest(int rate)
{
    for (int i = 0; i < 100; i++)
    {
        if (open[i] == 1)
        {
            bank[i] += (bank[i] * rate / 100);
        }
    }
}
