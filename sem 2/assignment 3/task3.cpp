#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
    string userInput;
    string filename = "log.txt";
    ofstream file(filename, ios::app); 

    if (!file.is_open()) 
    {
        cerr << "Error: unable to open file for appending." << endl;
    }

    cout << "input string to append to the file: ";
    
    getline(cin, userInput);

    file << userInput << endl;

    file.close();
    return 0;
}