#include <iostream>

using namespace std;


int main(){

    int* ptr = new int[5];

    cout<< "ENTER 5 VALUES IN THE ARRAY: ";
    
    for(int i = 0;i<5;++i){
    
        cin>> ptr[i];
    }


    cout<<"\n array elements: ";

    for(int i = 0; i<5;++i){

        cout<< ptr[i] << " ";
    }

    delete [] ptr;
    ptr = nullptr;

    
    return 0;
}