#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to display all employee numbers
void displayAllEmployeeNumbers() {
    ifstream file("employees.txt");
    if (!file) {
        cout << "Error: Could not open the employee records file!" << endl;
        return;
    }

    string line;
    cout << "List of Employee Numbers:" << endl;
    while (getline(file, line)) {
        if (line.find("Employee Number: ") == 0) { // Check if the line contains an employee number
            cout << line.substr(17) << endl; // Extract and display the employee number
        }
    }

    file.close();
}

// Function to search for an employee's details by Employee Number
void searchEmployeeDetails(const string& employeeNumber) {
    ifstream file("employees.txt");
    if (!file) {
        cout << "Error: Could not open the employee records file!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line == "Employee Number: " + employeeNumber) {
            found = true;
            cout << "Employee Details:" << endl;
            cout << line << endl;
            for (int i = 0; i < 4; i++) { // Read next 4 lines (details and separator)
                getline(file, line);
                if (line == "---") break; // End of record
                cout << line << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Error: Employee with Employee Number " << employeeNumber << " not found!" << endl;
    }

    file.close();
}

// Function to update employee salary
void updateEmployeeSalary(const string& employeeNumber, const string& newSalary) {
    fstream file("employees.txt");
    if (!file) {
        cout << "Error: Could not open the employee records file!" << endl;
        return;
    }

    string line;
    string tempFileContent;
    bool found = false;

    while (getline(file, line)) {
        if (line == "Employee Number: " + employeeNumber) {
            found = true;
            tempFileContent += line + "\n";

            for (int i = 0; i < 4; i++) {
                getline(file, line);
                if (line.find("Salary: ") == 0) {
                    line = "Salary: " + newSalary; // Update salary line
                }
                tempFileContent += line + "\n";
            }
        } else {
            tempFileContent += line + "\n";
        }
    }

    file.close();

    if (!found) {
        cout << "Error: Employee with Employee Number " << employeeNumber << " not found!" << endl;
        return;
    }

    ofstream outFile("employees.txt");
    outFile << tempFileContent; // Write updated content back to the file
    outFile.close();

    cout << "Salary updated successfully for Employee Number: " << employeeNumber << endl;
}

int main() {
    cout << "University Employee Record Management System" << endl;

    // Display all employee numbers
    displayAllEmployeeNumbers();

    cout << "\nEnter Employee Number to view details: ";
    string employeeNumber;
    cin >> employeeNumber;

    // Search and display employee details
    searchEmployeeDetails(employeeNumber);

    cout << "\nDo you want to update the salary for this employee? (yes/no): ";
    string choice;
    cin >> choice;

    if (choice == "yes") {
        string newSalary;
        cout << "Enter the updated salary: ";
        cin >> newSalary;
        updateEmployeeSalary(employeeNumber, newSalary);
    } else {
        cout << "No changes made. Goodbye!" << endl;
    }

    return 0;
}

