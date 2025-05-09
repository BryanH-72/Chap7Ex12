// File Name: Chapter7Ex12.cpp
// Developer/Programmer: YourName Here
// Date: 05/25
// Requirements: Grade Book app using arrays or vectors, calculate average (drop lowest grade),
// validate input, assign letter grades, no use of <limits> or <algorithm>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Menu module
int displayMenu() {
    int choice;
    cout << "\n--- Grade Book Menu ---\n";
    cout << "1. Add Student\n";
    cout << "2. Add Grades\n";
    cout << "3. Display Students and Grades\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Grade validation module
int getValidatedGrade() {
    int grade;
    while (true) {
        cout << "Enter a grade (0 - 100) or -1 to stop: ";
        cin >> grade;

        if (cin.fail()) {
            cin.clear();  // Clear error flag
            char dump;
            while (cin >> dump && dump != '\n');  // Discard invalid input
            cout << "Invalid input. Try again.\n";
        }
        else if ((grade >= 0 && grade <= 100) || grade == -1) {
            return grade;
        }
        else {
            cout << "Grade must be between 0 and 100.\n";
        }
    }
}

// Manual min finder
int findMinGrade(const vector<int>& grades) {
    if (grades.empty()) return 0;
    int min = grades[0];
    for (size_t i = 1; i < grades.size(); i++) {
        if (grades[i] < min) min = grades[i];
    }
    return min;
}

// Average calculator with lowest dropped
double calculateAverage(const vector<int>& grades) {
    if (grades.empty()) return 0;

    if (grades.size() == 1) {
        return grades[0];  // Only one grade, return it as the average
    }

    int min = findMinGrade(grades);
    int sum = 0;
    for (size_t i = 0; i < grades.size(); i++) {
        sum += grades[i];
    }
    sum -= min;
    return static_cast<double>(sum) / (grades.size() - 1);
}


// Letter grade mapper
char getLetterGrade(double avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    return 'F';
}

int main() {
    vector<string> studentNames;
    vector<vector<int>> studentGrades;

    while (true) {
        int choice = displayMenu();
        cin.ignore();

        if (choice == 1) {
            // Add students
            string name;
            cout << "Enter student name (or 'done' to finish): ";
            getline(cin, name);
            while (name != "done") {
                studentNames.push_back(name);
                studentGrades.push_back({});
                cout << "Enter another name (or 'done'): ";
                getline(cin, name);
            }

        }
        else if (choice == 2) {
            // Add grades
            if (studentNames.empty()) {
                cout << "No students found. Add students first.\n";
                continue;
            }

            for (size_t i = 0; i < studentNames.size(); i++) {
                cout << "\nEnter grades for " << studentNames[i] << ":\n";
                int grade;
                while (true) {
                    grade = getValidatedGrade();
                    if (grade == -1) break;
                    studentGrades[i].push_back(grade);
                }
            }

        }
        else if (choice == 3) {
            // Display students
            if (studentNames.empty()) {
                cout << "No students to display.\n";
                continue;
            }

            for (size_t i = 0; i < studentNames.size(); i++) {
                cout << "\nStudent: " << studentNames[i] << "\nGrades: ";
                for (int g : studentGrades[i]) {
                    cout << g << " ";
                }
                double avg = calculateAverage(studentGrades[i]);
                cout << "\nFinal Average: " << avg;
                cout << "\nLetter Grade: " << getLetterGrade(avg) << "\n";
            }

        }
        else if (choice == 4) {
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid menu option.\n";
        }
    }

    return 0;
}
