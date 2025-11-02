# include <iostream>

using namespace std;


class vehicle {

    public:
    
         void start(){

            cout<<"starting a vehicle"<<endl;
        }

        virtual void stop(){

            cout<<"stopping a vehicle"<<endl;
        }
};

class Car : public vehicle{

    public:
         void start(){

        cout<<"starting a CAR"<<endl;
        }

         void stop(){

        cout<<"stopping a CAR"<<endl;
        }
    
};

int main(){
    vehicle* ptr;
    
    Car car;

     ptr = &car;

    ptr->start();
    ptr->stop();

}