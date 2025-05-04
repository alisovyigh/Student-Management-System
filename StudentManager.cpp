// StudentManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>
using std::ifstream;
using std::cout;
using std::vector;
using std::string;
using std::getline;
using std::stringstream;
using std::cin;
using std::endl;
using std::abort;
using std::ofstream;
using std::streamsize;
using std::numeric_limits;
using std::max;
using std::fixed;
using std::setprecision;
/// //////////////////////////////////////////////////////////////////////////////////////////


struct Student {
    string name;
    string surname;
    vector<int> grades;
    double averageScore;
};

//////////////////////////////////////////////////////////////////////////////////////////////

void averageScore(Student& s) {
    if (s.grades.empty()) s.averageScore = 0;
    else {
        double sum = 0;
        for (int g : s.grades) sum += g;
        s.averageScore = sum / s.grades.size();
    }

}

void add(vector<Student>& students) {
    Student s;
    int grade;
    cout << "Input name:\n";
    cin >> s.name;
    if (s.name == "Terminate") return;
    cout << "Input surname:\n";
    cin >> s.surname;
    cout << "Enter grades (end with 0): ";

    while (true) {
        if (!(cin >> grade)) {  
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number: ";
            continue;
        }
        if (grade == 0) {
            break;  
        }
        if (grade < 0) {
            cout << "Negative grades are not allowed. Try again: ";
            continue;
        }
        s.grades.push_back(grade);
    }

    if (!s.grades.empty()) {
        averageScore(s);
        students.push_back(s);
        cout << "Student added successfully.\n";
    }
    else {
        cout << "No valid grades entered. Student not added.\n";
    }
} 
//////////////////////////////////////////////////////////////////////////////////

void saveToFile(const vector<Student>& Students) {
    ofstream fr("students.txt");
    if (!fr) { 
        cout << "File error!\n"; 
    return; 
    }

    
    for (int i = 0; i < Students.size(); i++) {
        fr << Students[i].name << " " << Students[i].surname<<endl;
        for (int j = 0; j < Students[i].grades.size(); j++) {
            fr << Students[i].grades[j] << " ";
        }
        fr << "\n";
    }
    cout << "Data saved successfully!\n";
}
///////////////////////////////////////////////////////////////////////////////////////////


void input(vector<Student>& Students) {
    ifstream fd("students.txt");
    if (!fd) { cout << "File error!\n"; return; }

    

    string line;
    while (getline(fd, line)) {
        stringstream ss(line);
        Student s;
        ss >> s.name >> s.surname;

        int grade;
        while (ss >> grade) {
            s.grades.push_back(grade);
        }
        averageScore(s);
        Students.push_back(s);
    }
}
////////////////////////////////////////////////////////////////////////////////
void printStudents(const vector<Student>& Students) {
    for (int i = 0; i < Students.size(); i++) {
        cout << Students[i].name << " " << Students[i].surname << " | Grades: ";
        for (int j = 0; j < Students[i].grades.size(); j++) {
            cout << Students[i].grades[j] << " ";
        }
       cout << " | Average: " << fixed << setprecision(2) << Students[i].averageScore;
        cout << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////
void menu(vector<Student>& Students) {
    input(Students);
    
    int choice;
    
    do {
        cout << "Welcome to the SMS (Students Management System). What would you like to do?" << endl;
        cout << "Input the following numbers for the selected task:" << endl;
        cout << "1. Add a student. | 2. List all available students. | 3. Save all students. 4. Terminate program.\n";
        cin >> choice;
        switch (choice) {
            
        case 1: add(Students); cout << endl; break;
        case 2: printStudents(Students); cout << endl; break;
        case 3: saveToFile(Students); cout << endl; break;
        case 4: break;
        default: cout << "Invalid option, choose again." << endl;
        }
    } while (choice != 4);
}
int main() {
    vector<Student> Students;
    menu(Students);

    

    return 0;

}

             
