/*
Bank Account Balance Adjustment
Problem Statement:
	You are tasked with helping a bank manage customer account balances. 
	The bank wants to allow its customers to adjust their balances by adding or 
	deducting amounts during transactions (such as deposits or withdrawals). 
	You need to write a C++ program that will:

	>Allow the user to input their account balance.
	>Pass this balance by reference to two functions:
		1) One for depositing money (add an amount to the balance).
		2) One for withdrawing money (subtract an amount from the balance).
	The program should update the balance in real time using pass-by-reference and display the updated balance after each operation.
Requirements:
	The initial account balance must be passed to the functions by reference.
	Each function should take the reference to the balance and the transaction amount as parameters.
	Ensure that the withdrawal function doesn't allow the balance to go negative.
*/
#include <iostream>
using namespace std;

// Function for depositing money (pass balance by reference)
void deposit(double &balance, double amount) {
    balance += amount;
    cout << "Amount deposited: $" << amount << endl;
}

// Function for withdrawing money (pass balance by reference)
void withdraw(double &balance, double amount) {
    if (amount > balance) {
        cout << "Insufficient balance! Withdrawal failed." << endl;
    } else {
        balance -= amount;
        cout << "Amount withdrawn: $" << amount << endl;
    }
}

int main() {
    double balance, depositAmount, withdrawAmount;
    
    // Input initial balance
    cout << "Enter initial balance: $";
    cin >> balance;
    
    // Deposit money
    cout << "Enter deposit amount: $";
    cin >> depositAmount;
    deposit(balance, depositAmount);  // Balance is passed by reference
    cout << "Updated balance: $" << balance << endl;
    
    // Withdraw money
    cout << "Enter withdrawal amount: $";
    cin >> withdrawAmount;
    withdraw(balance, withdrawAmount);  // Balance is passed by reference
    cout << "Updated balance: $" << balance << endl;
    
    return 0;
}

