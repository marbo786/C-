#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
    string filename = "truncate.txt";
    ofstream outFile(filename, ios::trunc);

    if (!outFile.is_open()) 
    {
        cerr << "Error: unable to open file for truncation." << endl;
    }

    outFile.close(); 

    cout << "File content has been erased." << endl;

    return 0;
}