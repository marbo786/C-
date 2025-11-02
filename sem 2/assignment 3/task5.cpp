#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
    string text;
    string filename = "data.txt";
    ifstream file(filename); 

    if (!file.is_open()) 
    {
        cerr << "Error: file not found." << endl;
    }

    file.seekg(10, ios::beg); 

    
    getline(file, text);
    cout << "text from the 10th byte: " << text << endl; 
    file.close();
    return 0;
}