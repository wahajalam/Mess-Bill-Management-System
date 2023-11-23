#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<algorithm>

using namespace std;

// Structure to represent a Student
struct Student {
    string name;
    string rollNumber;
    string messStatus;
};

// Function to write student data to the file
void writeToFile(const vector<Student>& students) {
    ofstream file("students.csv");
    if (file.is_open()) {
        // Write each student's data to the file in CSV format
        for (const auto& student : students) {
            file << student.name << "," << student.rollNumber << "," << student.messStatus << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

// Function to read student data from the file
vector<Student> readFromFile() {
    vector<Student> students;
    ifstream file("students.csv");
    if (file.is_open()) {
        // Read each line from the file and parse it into Student structure
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, rollNumber, messStatus;
            getline(ss, name, ',');
            getline(ss, rollNumber, ',');
            getline(ss, messStatus, ',');
            students.push_back({name, rollNumber, messStatus});
        }
        file.close();
    } else {
        cout << "Unable to open file for reading." << endl;
    }
    return students;
}

// Function to register a new student
void registerStudent(vector<Student>& students) {
    Student newStudent;
    cout << "Enter name: ";
    getline(cin, newStudent.name);
    cout << "Enter roll number: ";
    getline(cin, newStudent.rollNumber);
    newStudent.messStatus = "OUT"; // Default status is OUT
    students.push_back(newStudent);
    writeToFile(students); // Update the file with the new student data
    cout << "Student registered successfully." << endl;
}

// Function to search for a student's record
void searchStudent(const vector<Student>& students) {
    string rollNumber;
    cout << "Enter roll number to search: ";
    getline(cin, rollNumber);

    // Search for the student with the given roll number
    for (const auto& student : students) {
        if (student.rollNumber == rollNumber) {
            cout << "Name: " << student.name << endl;
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Mess Status: " << student.messStatus << endl;
            return;
        }
    }

    cout << "Student not found." << endl;
}

// Function to change mess status (IN/OUT) for a student
void changeMessStatus(vector<Student>& students) {
    string rollNumber;
    cout << "Enter roll number to change mess status: ";
    getline(cin, rollNumber);

    // Search for the student with the given roll number
    for (auto& student : students) {
        if (student.rollNumber == rollNumber) {
            cout << "Current Mess Status: " << student.messStatus << endl;
            cout << "Enter new Mess Status (IN/OUT): ";
            getline(cin, student.messStatus);
            writeToFile(students); // Update the file with the changed mess status
            cout << "Mess status changed successfully." << endl;
            return;
        }
    }

    cout << "Student not found." << endl;
}

// Function to delete a student's record
void deleteStudent(vector<Student>& students) {
    string rollNumber;
    cout << "Enter roll number to delete student record: ";
    getline(cin, rollNumber);

    // Remove the student with the given roll number from the vector
    auto it = remove_if(students.begin(), students.end(), [rollNumber](const Student& student) {
        return student.rollNumber == rollNumber;
    });

    // Check if the student was found and removed
    if (it != students.end()) {
        students.erase(it, students.end());
        writeToFile(students); // Update the file after deleting the student record
        cout << "Student record deleted successfully." << endl;
    } else {
        cout << "Student not found." << endl;
    }
}

// Function to show the total number of IN/OUT students
void showTotalInOut(const vector<Student>& students) {
    int inCount = 0, outCount = 0;

    // Count the number of IN and OUT students
    for (const auto& student : students) {
        if (student.messStatus == "IN") {
            inCount++;
        } else if (student.messStatus == "OUT") {
            outCount++;
        }
    }

    // Display the total counts
    cout << "Total IN students: " << inCount << endl;
    cout << "Total OUT students: " << outCount << endl;
}

// Function to calculate the total mess bill
void calculateTotalMessBill(const vector<Student>& students) {
    // Add your logic to calculate the total mess bill based on student data
    // For simplicity, let's assume a fixed bill amount for each student (e.g., $50)
    double billAmount = 300;
    double totalBill = billAmount * students.size();
    cout << "Total Mess Bill: PKR " << totalBill << "/-"<< endl;
}

// Function to display the menu
void displayMenu() {
    cout << "1: REGISTERATION OF A NEW STUDENT" << endl;
    cout << "2: SEARCH THE STUDENT'S RECORD" << endl;
    cout << "3: CHANGE THE MESS STATUS (IN / OUT)" << endl;
    cout << "4: DELETE A STUDENT'S RECORD" << endl;
    cout << "5: SHOW THE TOTAL NUMBER OF IN/OUT STUDENTS" << endl;
    cout << "6: CALCULATE THE TOTAL MESS BILL" << endl;
    cout << "0: EXIT" << endl;
}

// Main function
int main() {
    vector<Student> students = readFromFile();

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice (0-6): ";
        cin >> choice;
        cin.ignore(); // Clear newline character from the buffer

        // Switch statement to handle different menu options
        switch (choice) {
            case 1:
                registerStudent(students);
                break;
            case 2:
                searchStudent(students);
                break;
            case 3:
                changeMessStatus(students);
                break;
            case 4:
                deleteStudent(students);
                break;
            case 5:
                showTotalInOut(students);
                break;
            case 6:
                calculateTotalMessBill(students);
                break;
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 0 and 6." << endl;
        }
    } while (choice != 0);

    return 0;
}
