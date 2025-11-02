#include <iostream>
using namespace std;

int main()
{
    float percent;
    cout << "Enter your percentage: ";
    cin >> percent;
    if (percent >= 40)
    {
        if (percent >= 80)
            cout << "You passed with distintion" << endl;
        else
            {
                if (percent >= 60 && percent < 80)
                cout << "You passed with first division" << endl;
                else
                {
                    if (percent >= 40 && percent < 50)
                        cout << "You passed with third division";

                    else

                        cout << "You passed with second division" << endl;
                }
            }
                
    }
    else
        
    cout << "You Failed";
        
    return 0;
}