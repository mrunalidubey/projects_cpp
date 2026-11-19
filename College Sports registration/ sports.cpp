
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Student {
public:
    int id;
    string name;
    string sport;

    Student(int i, string n, string s) {
        id = i;
        name = n;
        sport = s;
    }

    void display() {
        cout << "\nStudent ID: " << id;
        cout << "\nName: " << name;
        cout << "\nSport: " << sport << "\n";
    }
};

class SportsRegistration {
private:
    vector<Student> students;

public:
    void registerStudent() {
        int id;
        string name, sport;

        cout << "Enter Student ID: ";
        cin >> id;

        for (auto &s : students) {
            if (s.id == id) {
                cout << "Student is already registered!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "\nAvailable Sports:\n";
        cout << "1. Cricket\n";
        cout << "2. Football\n";
        cout << "3. Basketball\n";
        cout << "4. Badminton\n";
        cout << "5. Volleyball\n";

        cout << "Enter Sport Name: ";
        getline(cin, sport);

        students.emplace_back(id, name, sport);
        cout << "Registration successful!\n";
    }

    void displayRegistrations() {
        if (students.empty()) {
            cout << "No registrations found.\n";
            return;
        }

        for (auto &s : students) {
            s.display();
        }
    }

    void searchStudent() {
        int id;

        cout << "Enter Student ID: ";
        cin >> id;

        for (auto &s : students) {
            if (s.id == id) {
                s.display();
                return;
            }
        }

        cout << "Registration not found!\n";
    }

    void displayBySport() {
        string sport;
        bool found = false;

        cin.ignore();
        cout << "Enter Sport Name: ";
        getline(cin, sport);

        for (auto &s : students) {
            if (s.sport == sport) {
                s.display();
                found = true;
            }
        }

        if (!found) {
            cout << "No participants found for this sport.\n";
        }
    }

    void cancelRegistration() {
        int id;

        cout << "Enter Student ID: ";
        cin >> id;

        for (auto it = students.begin(); it != students.end(); it++) {
            if (it->id == id) {
                students.erase(it);
                cout << "Registration cancelled successfully!\n";
                return;
            }
        }

        cout << "Student registration not found!\n";
    }

    void saveToFile() {
        ofstream file("sports.txt");

        for (auto &s : students) {
            file << s.id << "\n"
                 << s.name << "\n"
                 << s.sport << "\n";
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("sports.txt");

        int id;
        string name, sport;

        while (file >> id) {
            file.ignore();
            getline(file, name);
            getline(file, sport);

            students.emplace_back(id, name, sport);
        }

        file.close();
    }
};

int main() {
    SportsRegistration sports;
    sports.loadFromFile();

    int choice;

    do {
        cout << "\n===== COLLEGE SPORTS REGISTRATION =====\n";
        cout << "1. Register Student\n";
        cout << "2. Display All Registrations\n";
        cout << "3. Search Student\n";
        cout << "4. Display Participants by Sport\n";
        cout << "5. Cancel Registration\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sports.registerStudent(); break;
            case 2: sports.displayRegistrations(); break;
            case 3: sports.searchStudent(); break;
            case 4: sports.displayBySport(); break;
            case 5: sports.cancelRegistration(); break;
            case 0:
                sports.saveToFile();
                cout << "Records saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
