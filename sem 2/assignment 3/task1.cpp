#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
    string line;
    string filename = "example.txt";
    ifstream file(filename); 

    if (!file.is_open()) 
    {
        cerr << "Error: file not found." << endl; 
    }

    
    while (getline(file, line)) 
    {
        cout << line << endl; 
    }

    file.close();
    
    return 0;
}