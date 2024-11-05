#include <iostream>
using namespace std;
int main()
{
    char c[] = "Cisbest";
    int len = -1;
    // calculating string length
    while (c[++len] != '\0');
        // number of outer spaces to make pattern is controlled by space   
    int space = -1;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
            cout << " ";
        cout << c[i];
        // final row we print reverse string 
        if (i == len - 1)
        {
            // This loop mirrors part of the string in reverse order on the left side of the row
            for (int j = 1; j <= space/2; j++)
                cout << c[i-j];
            // This loop prints the initial part of the string from c[0] up to c[len - 2]
            for (int j = 0; j < len-1; j++)
                cout << c[j];
        }
        else
        {
            // spaces for middle of rows 
            for (int j = 0; j < space; j++)
                cout <<" ";
        }
        // The  part mirrors each character on the right side for all rows except the first.
        if (space != -1)
            cout << c[i];
        cout << endl;
        // increment by 2 to make it wider
        space = space + 2;
}
}