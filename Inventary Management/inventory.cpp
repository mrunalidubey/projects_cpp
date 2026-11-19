
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Product {
public:
    int id;
    string name;
    int quantity;
    double price;

    Product(int i, string n, int q, double p) {
        id = i;
        name = n;
        quantity = q;
        price = p;
    }

    void display() {
        cout << "\nProduct ID: " << id;
        cout << "\nName: " << name;
        cout << "\nQuantity: " << quantity;
        cout << "\nPrice: Rs. " << price << "\n";
    }
};

class Inventory {
private:
    vector<Product> products;

public:
    void addProduct() {
        int id, quantity;
        string name;
        double price;

        cout << "Enter Product ID: ";
        cin >> id;

        for (auto &p : products) {
            if (p.id == id) {
                cout << "Product ID already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Product Name: ";
        getline(cin, name);

        cout << "Enter Quantity: ";
        cin >> quantity;

        cout << "Enter Price: ";
        cin >> price;

        if (quantity < 0 || price < 0) {
            cout << "Invalid quantity or price!\n";
            return;
        }

        products.emplace_back(id, name, quantity, price);
        cout << "Product added successfully!\n";
    }

    void displayProducts() {
        if (products.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        for (auto &p : products) {
            p.display();
        }
    }

    void searchProduct() {
        int id;
        cout << "Enter Product ID: ";
        cin >> id;

        for (auto &p : products) {
            if (p.id == id) {
                p.display();
                return;
            }
        }

        cout << "Product not found!\n";
    }

    void updateStock() {
        int id, quantity;
        cout << "Enter Product ID: ";
        cin >> id;

        for (auto &p : products) {
            if (p.id == id) {
                cout << "Enter quantity to add: ";
                cin >> quantity;

                if (quantity <= 0) {
                    cout << "Enter a positive quantity!\n";
                    return;
                }

                p.quantity += quantity;
                cout << "Stock updated successfully!\n";
                return;
            }
        }

        cout << "Product not found!\n";
    }

    void sellProduct() {
        int id, quantity;
        cout << "Enter Product ID: ";
        cin >> id;

        for (auto &p : products) {
            if (p.id == id) {
                cout << "Enter quantity to sell: ";
                cin >> quantity;

                if (quantity <= 0) {
                    cout << "Invalid quantity!\n";
                } else if (quantity > p.quantity) {
                    cout << "Insufficient stock!\n";
                } else {
                    p.quantity -= quantity;
                    cout << "Product sold successfully!\n";
                    cout << "Total bill: Rs. " << quantity * p.price << "\n";
                }
                return;
            }
        }

        cout << "Product not found!\n";
    }

    void saveToFile() {
        ofstream file("inventory.txt");

        for (auto &p : products) {
            file << p.id << "\n"
                 << p.name << "\n"
                 << p.quantity << "\n"
                 << p.price << "\n";
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("inventory.txt");

        int id, quantity;
        string name;
        double price;

        while (file >> id) {
            file.ignore();
            getline(file, name);
            file >> quantity >> price;
            file.ignore();

            products.emplace_back(id, name, quantity, price);
        }

        file.close();
    }
};

int main() {
    Inventory inventory;
    inventory.loadFromFile();

    int choice;

    do {
        cout << "\n===== INVENTORY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Stock\n";
        cout << "5. Sell Product\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: inventory.addProduct(); break;
            case 2: inventory.displayProducts(); break;
            case 3: inventory.searchProduct(); break;
            case 4: inventory.updateStock(); break;
            case 5: inventory.sellProduct(); break;
            case 0:
                inventory.saveToFile();
                cout << "Inventory saved successfully. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
