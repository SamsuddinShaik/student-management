#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <limits>

using namespace std;

class Student {
public:
    int id;
    char name[50];
    int age;
    char course[50];
    float marks;

    void input() {
        cout << "\nEnter Student ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Student Name: ";
        cin.getline(name, 50);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Course: ";
        cin.getline(course, 50);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "\n----------------------------------------";
        cout << "\nStudent ID : " << id;
        cout << "\nName       : " << name;
        cout << "\nAge        : " << age;
        cout << "\nCourse     : " << course;
        cout << "\nMarks      : " << marks;
        cout << "\n----------------------------------------\n";
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    if (!file) {
        cout << "\nError opening file!\n";
        return;
    }

    s.input();
    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();

    cout << "\nStudent added successfully!\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    bool found = false;
    cout << "\n========== STUDENT RECORDS ==========\n";

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        s.display();
        found = true;
    }

    file.close();

    if (!found)
        cout << "No student records found.\n";
}

void searchStudent() {
    Student s;
    int searchId;

    cout << "\nEnter Student ID to search: ";
    cin >> searchId;

    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id == searchId) {
            cout << "\nStudent found:\n";
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent with ID " << searchId << " not found.\n";
}

void updateStudent() {
    Student s;
    int searchId;

    cout << "\nEnter Student ID to update: ";
    cin >> searchId;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id == searchId) {
            cout << "\nCurrent student information:";
            s.display();

            cout << "\nEnter new information:\n";
            s.input();

            file.seekp(-static_cast<streamoff>(sizeof(s)), ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(s));

            found = true;
            cout << "\nStudent updated successfully!\n";
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent with ID " << searchId << " not found.\n";
}

void deleteStudent() {
    Student s;
    int deleteId;

    cout << "\nEnter Student ID to delete: ";
    cin >> deleteId;

    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    ofstream temp("temp.dat", ios::binary);
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id == deleteId) {
            found = true;
            continue;
        }

        temp.write(reinterpret_cast<char*>(&s), sizeof(s));
    }

    file.close();
    temp.close();

    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        cout << "\nStudent deleted successfully!\n";
    } else {
        remove("temp.dat");
        cout << "\nStudent with ID " << deleteId << " not found.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n\n========================================";
        cout << "\n       STUDENT MANAGEMENT SYSTEM";
        cout << "\n========================================";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\n========================================";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "\nThank you for using Student Management System!\n"; break;
            default: cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
