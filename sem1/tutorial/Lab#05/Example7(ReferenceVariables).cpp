 #include <iostream>

using namespace std;

int main() {
 
 int n = 5;          // this declares a variable, n 
  int & r = n;        // this declares r as a reference to n 
  
  cout<<"n="<<n<<endl;
  cout<<"r="<<&r<<endl;
  
  cout<<"&n="<<&n<<endl;
  cout<<"&r="<<&r<<endl;
  return 0;
}
