
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Patient {
public:
    int id;
    string name;
    int age;
    string disease;

    Patient(int i, string n, int a, string d) {
        id = i;
        name = n;
        age = a;
        disease = d;
    }

    void display() {
        cout << "\nPatient ID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nDisease: " << disease << "\n";
    }
};

class Hospital {
private:
    vector<Patient> patients;

public:
    void addPatient() {
        int id, age;
        string name, disease;

        cout << "Enter Patient ID: ";
        cin >> id;

        for (auto &p : patients) {
            if (p.id == id) {
                cout << "Patient ID already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();
        cout << "Enter Disease: ";
        getline(cin, disease);

        patients.emplace_back(id, name, age, disease);
        cout << "Patient added successfully!\n";
    }

    void displayPatients() {
        if (patients.empty()) {
            cout << "No patient records found.\n";
            return;
        }

        for (auto &p : patients) {
            p.display();
        }
    }

    void searchPatient() {
        int id;
        cout << "Enter Patient ID: ";
        cin >> id;

        for (auto &p : patients) {
            if (p.id == id) {
                p.display();
                return;
            }
        }

        cout << "Patient not found!\n";
    }

    void dischargePatient() {
        int id;
        cout << "Enter Patient ID to discharge: ";
        cin >> id;

        for (auto it = patients.begin(); it != patients.end(); it++) {
            if (it->id == id) {
                patients.erase(it);
                cout << "Patient discharged successfully!\n";
                return;
            }
        }

        cout << "Patient not found!\n";
    }

    void saveToFile() {
        ofstream file("patients.txt");

        for (auto &p : patients) {
            file << p.id << "\n"
                 << p.name << "\n"
                 << p.age << "\n"
                 << p.disease << "\n";
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("patients.txt");

        int id, age;
        string name, disease;

        while (file >> id) {
            file.ignore();
            getline(file, name);
            file >> age;
            file.ignore();
            getline(file, disease);

            patients.emplace_back(id, name, age, disease);
        }

        file.close();
    }
};

int main() {
    Hospital hospital;
    hospital.loadFromFile();

    int choice;

    do {
        cout << "\n===== HOSPITAL PATIENT MANAGEMENT =====\n";
        cout << "1. Add Patient\n";
        cout << "2. Display Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Discharge Patient\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: hospital.addPatient(); break;
            case 2: hospital.displayPatients(); break;
            case 3: hospital.searchPatient(); break;
            case 4: hospital.dischargePatient(); break;
            case 0:
                hospital.saveToFile();
                cout << "Records saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
