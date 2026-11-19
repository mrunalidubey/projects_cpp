
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Employee {
private:
    int id;
    string name;
    double basicSalary;
    double allowance;
    double deduction;

public:
    Employee(int i, string n, double salary) {
        id = i;
        name = n;
        basicSalary = salary;
        allowance = salary * 0.20;  // 20% allowance
        deduction = salary * 0.10;  // 10% deduction
    }

    int getId() {
        return id;
    }

    double calculateSalary() {
        return basicSalary + allowance - deduction;
    }

    void display() {
        cout << fixed << setprecision(2);
        cout << "\nEmployee ID: " << id;
        cout << "\nName: " << name;
        cout << "\nBasic Salary: Rs. " << basicSalary;
        cout << "\nAllowance: Rs. " << allowance;
        cout << "\nDeduction: Rs. " << deduction;
        cout << "\nNet Salary: Rs. " << calculateSalary();
        cout << "\n-----------------------------\n";
    }

    void save(ofstream &file) {
        file << id << "\n"
             << name << "\n"
             << basicSalary << "\n";
    }
};

class PayrollSystem {
private:
    vector<Employee> employees;

public:
    void addEmployee() {
        int id;
        string name;
        double salary;

        cout << "Enter Employee ID: ";
        cin >> id;

        for (auto &e : employees) {
            if (e.getId() == id) {
                cout << "Employee ID already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Employee Name: ";
        getline(cin, name);

        cout << "Enter Basic Salary: ";
        cin >> salary;

        if (salary <= 0) {
            cout << "Invalid salary!\n";
            return;
        }

        employees.emplace_back(id, name, salary);
        cout << "Employee added successfully!\n";
    }

    void displayEmployees() {
        if (employees.empty()) {
            cout << "No employee records found.\n";
            return;
        }

        for (auto &e : employees) {
            e.display();
        }
    }

    void searchEmployee() {
        int id;

        cout << "Enter Employee ID: ";
        cin >> id;

        for (auto &e : employees) {
            if (e.getId() == id) {
                e.display();
                return;
            }
        }

        cout << "Employee not found!\n";
    }

    void saveToFile() {
        ofstream file("employees.txt");

        for (auto &e : employees) {
            e.save(file);
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("employees.txt");

        int id;
        string name;
        double salary;

        while (file >> id) {
            file.ignore();
            getline(file, name);
            file >> salary;
            file.ignore();

            employees.emplace_back(id, name, salary);
        }

        file.close();
    }
};

int main() {
    PayrollSystem payroll;
    payroll.loadFromFile();

    int choice;

    do {
        cout << "\n===== EMPLOYEE PAYROLL SYSTEM =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                payroll.addEmployee();
                break;

            case 2:
                payroll.displayEmployees();
                break;

            case 3:
                payroll.searchEmployee();
                break;

            case 0:
                payroll.saveToFile();
                cout << "Employee records saved. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
