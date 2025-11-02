#include <iostream>
using namespace std;
int main()
{
    char c[] = "Cisbest";
    int len = -1;
    while (c[++len] != '\0');
        
    int space = -1;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
            cout << " ";
        cout << c[i];
        if (i == len - 1)
        {
            for (int j = 1; j <= space/2; j++)
                cout << c[i-j];
            for (int j = 0; j < len-1; j++)
                cout << c[j];
        }
        else
        {
            for (int j = 0; j < space; j++)
                cout << " ";
        }
        if (space != -1)
            cout << c[i];
        cout << endl;
        space+=2;
}
}