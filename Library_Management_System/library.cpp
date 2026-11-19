
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        issued = false;
    }

    void display() {
        cout << "\nBook ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: " << (issued ? "Issued" : "Available");
        cout << "\n";
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id) {
                cout << "Book ID already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.emplace_back(id, title, author);
        cout << "Book added successfully!\n";
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }

        for (auto &b : books) {
            b.display();
        }
    }

    void searchBook() {
        int id;
        cout << "Enter Book ID: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id) {
                b.display();
                return;
            }
        }

        cout << "Book not found!\n";
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id) {
                if (!b.issued) {
                    b.issued = true;
                    cout << "Book issued successfully!\n";
                } else {
                    cout << "Book is already issued.\n";
                }
                return;
            }
        }

        cout << "Book not found!\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id) {
                if (b.issued) {
                    b.issued = false;
                    cout << "Book returned successfully!\n";
                } else {
                    cout << "Book was not issued.\n";
                }
                return;
            }
        }

        cout << "Book not found!\n";
    }

    void saveToFile() {
        ofstream file("books.txt");

        for (auto &b : books) {
            file << b.id << "\n"
                 << b.title << "\n"
                 << b.author << "\n"
                 << b.issued << "\n";
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("books.txt");

        int id, status;
        string title, author;

        while (file >> id) {
            file.ignore();
            getline(file, title);
            getline(file, author);
            file >> status;
            file.ignore();

            Book b(id, title, author);
            b.issued = status;
            books.push_back(b);
        }

        file.close();
    }
};

int main() {
    Library lib;
    lib.loadFromFile();

    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.displayBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.issueBook(); break;
            case 5: lib.returnBook(); break;
            case 0:
                lib.saveToFile();
                cout << "Data saved. Thank you!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
