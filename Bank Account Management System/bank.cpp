
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string name;
    double balance;

public:
    BankAccount(int acc, string n, double b) {
        accountNumber = acc;
        name = n;
        balance = b;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully!\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount!\n";
        } else if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            cout << "Withdrawal successful!\n";
        }
    }

    void display() {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder: " << name;
        cout << "\nBalance: Rs. " << balance << "\n";
    }

    void save(ofstream &file) {
        file << accountNumber << "\n"
             << name << "\n"
             << balance << "\n";
    }
};

class Bank {
private:
    vector<BankAccount> accounts;

public:
    void createAccount() {
        int acc;
        string name;
        double balance;

        cout << "Enter account number: ";
        cin >> acc;

        for (auto &a : accounts) {
            if (a.getAccountNumber() == acc) {
                cout << "Account already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter account holder name: ";
        getline(cin, name);

        cout << "Enter initial balance: ";
        cin >> balance;

        if (balance < 0) {
            cout << "Balance cannot be negative!\n";
            return;
        }

        accounts.emplace_back(acc, name, balance);
        cout << "Account created successfully!\n";
    }

    BankAccount* findAccount(int acc) {
        for (auto &a : accounts) {
            if (a.getAccountNumber() == acc) {
                return &a;
            }
        }
        return nullptr;
    }

    void depositMoney() {
        int acc;
        double amount;

        cout << "Enter account number: ";
        cin >> acc;

        BankAccount* a = findAccount(acc);

        if (a == nullptr) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter deposit amount: ";
        cin >> amount;
        a->deposit(amount);
    }

    void withdrawMoney() {
        int acc;
        double amount;

        cout << "Enter account number: ";
        cin >> acc;

        BankAccount* a = findAccount(acc);

        if (a == nullptr) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter withdrawal amount: ";
        cin >> amount;
        a->withdraw(amount);
    }

    void checkBalance() {
        int acc;

        cout << "Enter account number: ";
        cin >> acc;

        BankAccount* a = findAccount(acc);

        if (a == nullptr) {
            cout << "Account not found!\n";
        } else {
            a->display();
        }
    }

    void saveToFile() {
        ofstream file("accounts.txt");

        for (auto &a : accounts) {
            a.save(file);
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("accounts.txt");

        int acc;
        string name;
        double balance;

        while (file >> acc) {
            file.ignore();
            getline(file, name);
            file >> balance;
            file.ignore();

            accounts.emplace_back(acc, name, balance);
        }

        file.close();
    }
};

int main() {
    Bank bank;
    bank.loadFromFile();

    int choice;

    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.depositMoney(); break;
            case 3: bank.withdrawMoney(); break;
            case 4: bank.checkBalance(); break;
            case 0:
                bank.saveToFile();
                cout << "Data saved successfully. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
