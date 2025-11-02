#include <iostream>

using namespace std;


class VEHICLE {

    private:

        int password;

    public:

        VEHICLE(int c) {

            password = c;
        }

        friend int friendfunction(const VEHICLE&);
};


int friendfunction(const VEHICLE& obj){

    return obj.password;
}





int main(){

VEHICLE obj(69);

int temp = friendfunction(obj);
cout<<"THE PASSWORD IS: "<<temp;

    return 0;
}