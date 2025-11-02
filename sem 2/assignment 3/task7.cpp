#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
    string userInput;
    string filename = "append_end.txt";
    ofstream file(filename, ios::ate);

    if (!file.is_open()) 
    {
        cerr << "Error: unable to open file for appending." << endl;
    }

    cout << "Enter the string to append to the EOF: ";
    
    getline(cin, userInput);

    file << userInput << endl; 

    file.close();
    return 0;
}