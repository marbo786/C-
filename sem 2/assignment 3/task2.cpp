#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
    string filename = "output.txt";
    ofstream file(filename);

    if (!file.is_open()) 
    {
        cerr << "Error: unable to open file for writing." << endl;
    }

    cout << "input string to write to the file: ";
    string userInput;
    getline(cin, userInput);

    file << userInput << endl; 

    file.close();
    return 0;
}