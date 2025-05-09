// File Name: Chap7Ex12.cpp
// Developer/Programmer: Bryan Hurley
// Date: 05/25
// Requirements: Grade Book app with file persistence, student search, and grade editing

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Display menu and return choice
int displayMenu() {
    int choice;
    cout << "\n--- Grade Book Menu ---\n";
    cout << "1. Add Student\n";
    cout << "2. Add Grades\n";
    cout << "3. Display All Students\n";
    cout << "4. Search Student\n";
    cout << "5. Edit Student Grades\n";
    cout << "6. Save and Exit\n";
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

// Validate input grade
int getValidatedGrade() {
    int grade;
    while (true) {
        cout << "Enter grade (0 - 100) or -1 to stop: ";
        cin >> grade;
        if ((grade >= 0 && grade <= 100) || grade == -1) return grade;
        cout << "Invalid input.\n";
    }
}

// Find minimum grade manually
int findMinGrade(const vector<int>& grades) {
    int min = grades[0];
    for (int g : grades) if (g < min) min = g;
    return min;
}

// Calculate average excluding lowest
double calculateAverage(const vector<int>& grades) {
    if (grades.empty()) return 0;
    if (grades.size() == 1) return grades[0];
    int sum = 0, min = findMinGrade(grades);
    for (int g : grades) sum += g;
    return (sum - min) / static_cast<double>(grades.size() - 1);
}

// Convert numeric average to letter grade
char getLetterGrade(double avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    return 'F';
}

// Load student data from file
void loadFromFile(vector<string>& studentNames, vector<vector<int>>& studentGrades, const string& filename) {
    ifstream file(filename);
    if (!file) return;
    string name;
    while (file >> name) {
        studentNames.push_back(name);
        vector<int> grades;
        int grade;
        while (file.peek() == ' ') file.get();
        while (file.peek() != '\n' && file >> grade) grades.push_back(grade);
        file.ignore(1000, '\n');
        studentGrades.push_back(grades);
    }
    file.close();
}

// Save student data to file
void saveToFile(const vector<string>& studentNames, const vector<vector<int>>& studentGrades, const string& filename) {
    ofstream file(filename);
    for (size_t i = 0; i < studentNames.size(); i++) {
        file << studentNames[i];
        for (int g : studentGrades[i]) file << " " << g;
        file << endl;
    }
    file.close();
    cout << "Data saved to file.\n";
}

// Search student by name
int findStudentIndex(const vector<string>& studentNames, const string& name) {
    for (size_t i = 0; i < studentNames.size(); i++) {
        if (studentNames[i] == name) return i;
    }
    return -1;
}

// Display specific student
void displayStudent(const vector<string>& studentNames, const vector<vector<int>>& studentGrades, int index) {
    cout << "\nStudent: " << studentNames[index] << "\nGrades: ";
    for (int g : studentGrades[index]) cout << g << " ";
    double avg = calculateAverage(studentGrades[index]);
    cout << "\nAverage: " << avg << "\nLetter: " << getLetterGrade(avg) << endl;
}

// Edit student grades
void editGrades(vector<vector<int>>& studentGrades, int index) {
    int choice;
    cout << "1. Add Grade\n2. Change Grade\n3. Delete Grade\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        int grade = getValidatedGrade();
        if (grade != -1) studentGrades[index].push_back(grade);
    }
    else if (choice == 2) {
        for (size_t i = 0; i < studentGrades[index].size(); i++)
            cout << i << ": " << studentGrades[index][i] << endl;
        int pos, newGrade;
        cout << "Enter index to change: "; cin >> pos;
        newGrade = getValidatedGrade();
        if (pos >= 0 && pos < studentGrades[index].size())
            studentGrades[index][pos] = newGrade;
    }
    else if (choice == 3) {
        for (size_t i = 0; i < studentGrades[index].size(); i++)
            cout << i << ": " << studentGrades[index][i] << endl;
        int pos;
        cout << "Enter index to delete: "; cin >> pos;
        if (pos >= 0 && pos < studentGrades[index].size())
            studentGrades[index].erase(studentGrades[index].begin() + pos);
    }
}

int main() {
    const string filename = "grades.txt";
    vector<string> studentNames;
    vector<vector<int>> studentGrades;
    loadFromFile(studentNames, studentGrades, filename);

    while (true) {
        int choice = displayMenu();

        if (choice == 1) {
            string name;
            cout << "Enter student name (or 'done'): ";
            cin.ignore(); getline(cin, name);
            while (name != "done") {
                studentNames.push_back(name);
                studentGrades.push_back({});
                cout << "Enter next name (or 'done'): ";
                getline(cin, name);
            }
        }
        else if (choice == 2) {
            for (size_t i = 0; i < studentNames.size(); i++) {
                cout << "\nEnter grades for " << studentNames[i] << ":\n";
                int grade;
                while ((grade = getValidatedGrade()) != -1) {
                    studentGrades[i].push_back(grade);
                }
            }
        }
        else if (choice == 3) {
            for (size_t i = 0; i < studentNames.size(); i++)
                displayStudent(studentNames, studentGrades, i);
        }
        else if (choice == 4) {
            string name;
            cout << "Enter student name: ";
            cin.ignore(); getline(cin, name);
            int index = findStudentIndex(studentNames, name);
            if (index != -1) displayStudent(studentNames, studentGrades, index);
            else cout << "Student not found.\n";
        }
        else if (choice == 5) {
            string name;
            cout << "Enter student name: ";
            cin.ignore(); getline(cin, name);
            int index = findStudentIndex(studentNames, name);
            if (index != -1) editGrades(studentGrades, index);
            else cout << "Student not found.\n";
        }
        else if (choice == 6) {
            saveToFile(studentNames, studentGrades, filename);
            break;
        }
        else {
            cout << "Invalid option.\n";
        }
    }
    return 0;
}
