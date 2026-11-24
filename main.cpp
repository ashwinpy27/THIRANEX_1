#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string course;
    float marks;
};

const string FILE_NAME = "students.txt";

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool idExists(const vector<Student>& students, int id) {
    for (const auto& student : students) {
        if (student.id == id) return true;
    }
    return false;
}

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file(FILE_NAME);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Student s;
        string idText, ageText, marksText;

        if (getline(ss, idText, '|') &&
            getline(ss, s.name, '|') &&
            getline(ss, ageText, '|') &&
            getline(ss, s.course, '|') &&
            getline(ss, marksText, '|')) {
            try {
                s.id = stoi(idText);
                s.age = stoi(ageText);
                s.marks = stof(marksText);
                students.push_back(s);
            } catch (...) {
                // Skip any damaged or incorrectly formatted record.
            }
        }
    }
    return students;
}

bool saveStudents(const vector<Student>& students) {
    ofstream file(FILE_NAME);
    if (!file) return false;

    for (const auto& s : students) {
        file << s.id << '|'
             << s.name << '|'
             << s.age << '|'
             << s.course << '|'
             << s.marks << '\n';
    }
    return file.good();
}

void displayOne(const Student& s) {
    cout << left << setw(8) << s.id
         << setw(24) << s.name
         << setw(8) << s.age
         << setw(20) << s.course
         << fixed << setprecision(2) << s.marks << '\n';
}

void displayStudents() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n------------------------ STUDENT RECORDS ------------------------\n";
    cout << left << setw(8) << "ID"
         << setw(24) << "Name"
         << setw(8) << "Age"
         << setw(20) << "Course"
         << "Marks\n";
    cout << string(68, '-') << '\n';

    for (const auto& s : students) displayOne(s);
}

void addStudent() {
    vector<Student> students = loadStudents();
    Student s;

    cout << "\nEnter student ID: ";
    if (!(cin >> s.id)) {
        cout << "Invalid ID. Please enter a number.\n";
        clearInput();
        return;
    }

    if (idExists(students, s.id)) {
        cout << "A student with this ID already exists.\n";
        clearInput();
        return;
    }

    cout << "Enter student name: ";
    clearInput();
    getline(cin, s.name);

    cout << "Enter age: ";
    if (!(cin >> s.age) || s.age <= 0) {
        cout << "Invalid age.\n";
        clearInput();
        return;
    }

    cout << "Enter course: ";
    clearInput();
    getline(cin, s.course);

    cout << "Enter marks: ";
    if (!(cin >> s.marks) || s.marks < 0 || s.marks > 100) {
        cout << "Invalid marks. Enter a value from 0 to 100.\n";
        clearInput();
        return;
    }

    if (s.name.empty() || s.course.empty() ||
        s.name.find('|') != string::npos ||
        s.course.find('|') != string::npos) {
        cout << "Name/course cannot be empty or contain the | character.\n";
        return;
    }

    students.push_back(s);

    if (saveStudents(students))
        cout << "Student added successfully!\n";
    else
        cout << "Error: Could not save the student record.\n";
}

void updateStudent() {
    vector<Student> students = loadStudents();
    int id;

    cout << "\nEnter the ID of the student to update: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        clearInput();
        return;
    }

    for (auto& s : students) {
        if (s.id == id) {
            cout << "\nCurrent details:\n";
            cout << "Name: " << s.name << "\nAge: " << s.age
                 << "\nCourse: " << s.course << "\nMarks: " << s.marks << '\n';

            cout << "\nEnter new name: ";
            clearInput();
            getline(cin, s.name);

            cout << "Enter new age: ";
            if (!(cin >> s.age) || s.age <= 0) {
                cout << "Invalid age. Update cancelled.\n";
                clearInput();
                return;
            }

            cout << "Enter new course: ";
            clearInput();
            getline(cin, s.course);

            cout << "Enter new marks: ";
            if (!(cin >> s.marks) || s.marks < 0 || s.marks > 100) {
                cout << "Invalid marks. Update cancelled.\n";
                clearInput();
                return;
            }

            if (s.name.empty() || s.course.empty() ||
                s.name.find('|') != string::npos ||
                s.course.find('|') != string::npos) {
                cout << "Name/course cannot be empty or contain the | character.\n";
                return;
            }

            if (saveStudents(students))
                cout << "Student updated successfully!\n";
            else
                cout << "Error: Could not save the updated record.\n";
            return;
        }
    }

    cout << "Student with ID " << id << " was not found.\n";
}

void deleteStudent() {
    vector<Student> students = loadStudents();
    int id;

    cout << "\nEnter the ID of the student to delete: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        clearInput();
        return;
    }

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            cout << "Delete record for " << it->name << "? (y/n): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                students.erase(it);
                if (saveStudents(students))
                    cout << "Student deleted successfully!\n";
                else
                    cout << "Error: Could not save the changes.\n";
            } else {
                cout << "Deletion cancelled.\n";
            }
            return;
        }
    }

    cout << "Student with ID " << id << " was not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       STUDENT MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid menu number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice. Select 1 to 5.\n";
        }
    } while (choice != 5);

    return 0;
}
