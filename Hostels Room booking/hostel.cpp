
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Room {
public:
    int roomNumber;
    bool booked;

    Room(int number) {
        roomNumber = number;
        booked = false;
    }
};

class Booking {
public:
    int studentID;
    string studentName;
    int roomNumber;

    Booking(int id, string name, int room) {
        studentID = id;
        studentName = name;
        roomNumber = room;
    }

    void display() {
        cout << "\nStudent ID: " << studentID;
        cout << "\nStudent Name: " << studentName;
        cout << "\nRoom Number: " << roomNumber << "\n";
    }
};

class Hostel {
private:
    vector<Room> rooms;
    vector<Booking> bookings;

public:
    Hostel() {
        for (int i = 101; i <= 110; i++) {
            rooms.emplace_back(i);
        }
    }

    void displayRooms() {
        cout << "\n--- Room Availability ---\n";

        for (auto &r : rooms) {
            cout << "Room " << r.roomNumber << " : "
                 << (r.booked ? "Booked" : "Available") << "\n";
        }
    }

    void bookRoom() {
        int id, room;
        string name;

        cout << "Enter Student ID: ";
        cin >> id;

        for (auto &b : bookings) {
            if (b.studentID == id) {
                cout << "Student already has a booking!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Room Number: ";
        cin >> room;

        for (auto &r : rooms) {
            if (r.roomNumber == room) {
                if (!r.booked) {
                    r.booked = true;
                    bookings.emplace_back(id, name, room);
                    cout << "Room booked successfully!\n";
                } else {
                    cout << "Room is already booked!\n";
                }
                return;
            }
        }

        cout << "Invalid room number!\n";
    }

    void displayBookings() {
        if (bookings.empty()) {
            cout << "No bookings found.\n";
            return;
        }

        for (auto &b : bookings) {
            b.display();
        }
    }

    void searchBooking() {
        int id;
        cout << "Enter Student ID: ";
        cin >> id;

        for (auto &b : bookings) {
            if (b.studentID == id) {
                b.display();
                return;
            }
        }

        cout << "Booking not found!\n";
    }

    void cancelBooking() {
        int id;
        cout << "Enter Student ID: ";
        cin >> id;

        for (auto it = bookings.begin(); it != bookings.end(); it++) {
            if (it->studentID == id) {
                for (auto &r : rooms) {
                    if (r.roomNumber == it->roomNumber) {
                        r.booked = false;
                    }
                }

                bookings.erase(it);
                cout << "Booking cancelled successfully!\n";
                return;
            }
        }

        cout << "Booking not found!\n";
    }

    void saveToFile() {
        ofstream file("bookings.txt");

        for (auto &b : bookings) {
            file << b.studentID << "\n"
                 << b.studentName << "\n"
                 << b.roomNumber << "\n";
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("bookings.txt");

        int id, room;
        string name;

        while (file >> id) {
            file.ignore();
            getline(file, name);
            file >> room;
            file.ignore();

            for (auto &r : rooms) {
                if (r.roomNumber == room) {
                    r.booked = true;
                    break;
                }
            }

            bookings.emplace_back(id, name, room);
        }

        file.close();
    }
};

int main() {
    Hostel hostel;
    hostel.loadFromFile();

    int choice;

    do {
        cout << "\n===== HOSTEL ROOM BOOKING SYSTEM =====\n";
        cout << "1. View Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. Display Bookings\n";
        cout << "4. Search Booking\n";
        cout << "5. Cancel Booking\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: hostel.displayRooms(); break;
            case 2: hostel.bookRoom(); break;
            case 3: hostel.displayBookings(); break;
            case 4: hostel.searchBooking(); break;
            case 5: hostel.cancelBooking(); break;
            case 0:
                hostel.saveToFile();
                cout << "Booking records saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
