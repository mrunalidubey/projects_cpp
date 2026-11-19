
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Expense {
public:
    int id;
    string title;
    string category;
    double amount;

    Expense(int i, string t, string c, double a) {
        id = i;
        title = t;
        category = c;
        amount = a;
    }

    void display() {
        cout << "\nExpense ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nCategory: " << category;
        cout << "\nAmount: Rs. " << fixed << setprecision(2) << amount;
        cout << "\n-------------------------\n";
    }
};

class ExpenseTracker {
private:
    vector<Expense> expenses;

public:
    void addExpense() {
        int id;
        string title, category;
        double amount;

        cout << "Enter Expense ID: ";
        cin >> id;

        for (auto &e : expenses) {
            if (e.id == id) {
                cout << "Expense ID already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Expense Title: ";
        getline(cin, title);

        cout << "Enter Category (Food/Travel/Shopping): ";
        getline(cin, category);

        cout << "Enter Amount: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid amount!\n";
            return;
        }

        expenses.emplace_back(id, title, category, amount);
        cout << "Expense added successfully!\n";
    }

    void displayExpenses() {
        if (expenses.empty()) {
            cout << "No expenses recorded.\n";
            return;
        }

        for (auto &e : expenses) {
            e.display();
        }
    }

    void totalExpenses() {
        double total = 0;

        for (auto &e : expenses) {
            total += e.amount;
        }

        cout << "\nTotal Expenses: Rs. "
             << fixed << setprecision(2) << total << "\n";
    }

    void searchByCategory() {
        string category;
        bool found = false;

        cin.ignore();
        cout << "Enter Category: ";
        getline(cin, category);

        for (auto &e : expenses) {
            if (e.category == category) {
                e.display();
                found = true;
            }
        }

        if (!found) {
            cout << "No expenses found in this category.\n";
        }
    }

    void deleteExpense() {
        int id;

        cout << "Enter Expense ID to delete: ";
        cin >> id;

        for (auto it = expenses.begin(); it != expenses.end(); it++) {
            if (it->id == id) {
                expenses.erase(it);
                cout << "Expense deleted successfully!\n";
                return;
            }
        }

        cout << "Expense not found!\n";
    }

    void saveToFile() {
        ofstream file("expenses.txt");

        for (auto &e : expenses) {
            file << e.id << "\n"
                 << e.title << "\n"
                 << e.category << "\n"
                 << e.amount << "\n";
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("expenses.txt");

        int id;
        string title, category;
        double amount;

        while (file >> id) {
            file.ignore();
            getline(file, title);
            getline(file, category);
            file >> amount;
            file.ignore();

            expenses.emplace_back(id, title, category, amount);
        }

        file.close();
    }
};

int main() {
    ExpenseTracker tracker;
    tracker.loadFromFile();

    int choice;

    do {
        cout << "\n===== PERSONAL EXPENSE TRACKER =====\n";
        cout << "1. Add Expense\n";
        cout << "2. Display Expenses\n";
        cout << "3. Calculate Total Expenses\n";
        cout << "4. Search by Category\n";
        cout << "5. Delete Expense\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: tracker.addExpense(); break;
            case 2: tracker.displayExpenses(); break;
            case 3: tracker.totalExpenses(); break;
            case 4: tracker.searchByCategory(); break;
            case 5: tracker.deleteExpense(); break;
            case 0:
                tracker.saveToFile();
                cout << "Expenses saved successfully. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
