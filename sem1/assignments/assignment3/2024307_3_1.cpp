#include <iostream>
#include <string>
using namespace std;

void SWAP(string familyDetails[2][10], int i, int j) 
{
    swap(familyDetails[0][i], familyDetails[0][j]);
    swap(familyDetails[1][i], familyDetails[1][j]);
}

void SelectionSort(string familyDetails[2][10], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) 
        {
            if (familyDetails[1][j] > familyDetails[1][minIndex]) // p has ascii value of 80 while N has 78. 
            {
                minIndex = j;
            }
        }
        SWAP(familyDetails, i, minIndex);
    }
}

int TRANSFER_NON_COVID(string family[2][10], string iffat[2][10], int familySize) 
{
    int iffatSize = 0;
    for (int i = 0; i < familySize; i++) 
    {
        if (family[1][i] == "N") 
        {
            iffat[0][iffatSize] = family[0][i];
            iffat[1][iffatSize] = family[1][i];
            iffatSize++;
        }
    }
    return iffatSize;
}

void display(string arr[][10], int n){
    for (int z = 0; z < n; z++){
        cout << "  " << arr[0][z] << ": " << arr[1][z];
    }
}



int main(){

    string family[2][10] = 
    {
        {"Amna  ", "Father", "Mother", "Sister", "Brother1", "Brother2", "Grandfather", "Grandmother", "Uncle", "Aunt"},
        {"P", "N", "P", "N", "P", "N", "N", "N", "N", "N"}
    };

    int n = 10;

    string iffatDetails[2][10];

    int familySize = 10;

    
    cout << "Unsorted Family Details:" << endl;
    display(family, familySize);

    SelectionSort(family, familySize);

    cout << "\nSorted Family Details:" << endl;
    display(family, familySize);

    int iffatSize = TRANSFER_NON_COVID(family, iffatDetails, familySize);

    cout << "\nIffat's House Details:" << endl;
    display(iffatDetails, iffatSize);

    return 0;
}