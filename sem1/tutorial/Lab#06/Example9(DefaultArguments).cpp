/*
Problem Statement:
A currency exchange office needs a program to convert amounts between different currencies. 
Your task is to create a C++ program that allows users to convert an amount from USD to a target 
currency (either EUR, GBP, or JPY). If the user doesn’t specify a currency, the default conversion will be to EUR. You will write a function that performs the conversion using default argument values.

Conversion rates:
1 USD = 0.85 EUR (default)
1 USD = 0.75 GBP
1 USD = 110.0 JPY
Requirements:
Define a user-defined function convertCurrency that takes the amount in USD and an optional target currency (specified as a string). If no target currency is provided, the function should default to converting the amount to EUR.
The function should return the converted amount and display a message with the result.
No arrays should be used in the program.
*/

#include <iostream>
#include <string>
using namespace std;

// Function to convert currency, default target currency is EUR
double convertCurrency(double amount, string currency = "EUR") {
    if (currency == "EUR") {
        return amount * 0.85;  // USD to EUR
    } else if (currency == "GBP") {
        return amount * 0.75;  // USD to GBP
    } else if (currency == "JPY") {
        return amount * 110.0;  // USD to JPY
    } else {
        cout << "Invalid currency. Defaulting to EUR." << endl;
        return amount * 0.85;  // Default to EUR
    }
}

int main() {
    double usdAmount;
    string targetCurrency;
    
    // Input amount in USD
    cout << "Enter amount in USD: $";
    cin >> usdAmount;
    
    // Input target currency (optional)
    cout << "Enter target currency (EUR, GBP, JPY) or press enter for default (EUR): ";
    cin.ignore();  // Ignore newline character from previous input
    getline(cin, targetCurrency);
    
    // Perform conversion
    double convertedAmount;
    if (targetCurrency.empty()) {
        // Use default argument if no currency is provided
        convertedAmount = convertCurrency(usdAmount);
        cout << "Converted amount (default to EUR): " << convertedAmount << " EUR" << endl;
    } else {
        // Convert to specified currency
        convertedAmount = convertCurrency(usdAmount, targetCurrency);
        cout << "Converted amount: " << convertedAmount << " " << targetCurrency << endl;
    }
    
    return 0;
}

