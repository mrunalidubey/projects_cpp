
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    int roll;
    string name;
    float marks;

    Student() {}

    Student(int r, string n, float m) {
        roll = r;
        name = n;
        marks = m;
    }

    void display() {
        cout << roll << "\t" << name << "\t" << marks << endl;
    }
};

class StudentManagement {
private:
    vector<Student> students;

public:
    void addStudent() {
        int roll;
        string name;
        float marks;

        cout << "Enter Roll Number: ";
        cin >> roll;

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Marks: ";
        cin >> marks;

        students.push_back(Student(roll, name, marks));

        cout << "Student Added Successfully!\n";
    }

    void displayStudents() {
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }

        cout << "\nRoll\tName\tMarks\n";

        for (auto &s : students) {
            s.display();
        }
    }

    void searchStudent() {
        int roll;
        cout << "Enter Roll Number: ";
        cin >> roll;

        for (auto &s : students) {
            if (s.roll == roll) {
                cout << "Student Found:\n";
                s.display();
                return;
            }
        }

        cout << "Student Not Found!\n";
    }

    void deleteStudent() {
        int roll;
        cout << "Enter Roll Number: ";
        cin >> roll;

        for (auto it = students.begin();
             it != students.end(); it++) {

            if (it->roll == roll) {
                students.erase(it);
                cout << "Student Deleted!\n";
                return;
            }
        }

        cout << "Student Not Found!\n";
    }

    void saveToFile() {
        ofstream file("students.txt");

        for (auto &s : students) {
            file << s.roll << " "
                 << s.name << " "
                 << s.marks << endl;
        }

        file.close();
        cout << "Records Saved!\n";
    }

    void loadFromFile() {
        ifstream file("students.txt");

        Student s;
        while (file >> s.roll >> s.name >> s.marks) {
            students.push_back(s);
        }

        file.close();
    }
};

int main() {
    StudentManagement sm;
    sm.loadFromFile();

    int choice;

    do {
        cout << "\n--- STUDENT MANAGEMENT SYSTEM ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Save Records\n";
        cout << "0. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sm.addStudent(); break;
            case 2: sm.displayStudents(); break;
            case 3: sm.searchStudent(); break;
            case 4: sm.deleteStudent(); break;
            case 5: sm.saveToFile(); break;
            case 0:
                sm.saveToFile();
                cout << "Thank You!\n";
                break;
            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 0);

    return 0;
}
