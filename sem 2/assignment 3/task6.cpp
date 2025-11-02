#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
    string filename = "write_test.txt";
    ofstream file(filename); 

    if (!file.is_open()) 
    {
        cerr << "Error: unable to open file for writing." << endl;
    }

    file.seekp(5, ios::beg);  
    file << "Hello world!"; 

    file.close();
    return 0;
}