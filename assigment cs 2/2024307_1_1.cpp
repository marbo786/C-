#include <iostream>
using namespace std;

int main(){

    int num;
    int power;
    int answer=1;
    
    cout<<"enter a number";
    cin>>num;
    cout<<"enter the power";
    cin>>power;

    for(int i=0;i<power;i++){

        answer= answer*num;
    }

   cout<<answer;
   return 0;

}