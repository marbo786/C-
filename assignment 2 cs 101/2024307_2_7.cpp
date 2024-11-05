#include <iostream>
#include <iomanip> // to set precision

using namespace std;

int main() {
  int gallons;
  int gallonT = 0;
  double bill = 0.0;

  cout << "input the number of gallons consumed: ";
  cin >> gallons;

  while (gallons != -1) {
    gallonT += gallons;

    if (gallonT <= 100) 
    {
      bill += gallons * 50;
    } else if (gallonT <= 350) 
    {
      bill += 100 * 50 + (gallons - 100) * 100;
    } else if (gallonT <= 600) 
    {
      bill += 100 * 50 + 250 * 100 + (gallons - 350) * 150;
    } else 
    {
      bill += 100 * 50 + 250 * 100 + 250 * 150 + (gallons - 600) * 250;
    }

    cout << "input the number of gallons consumed (-1 to stop): ";
    cin >> gallons;
  }

  bill += bill * 0.14; 

  cout <<fixed<<setprecision(2) << "Total bill: Rs. " << bill << endl;

  return 0;
}