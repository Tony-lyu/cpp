#include "student.hpp"
#include <iostream>
using namespace std;

// for debugging 
void print(Student *student) {
    cout << "Name: " << student->name<<endl;
    cout << "cpp: " << student->cpp<<endl;
    cout << "gdb: " << student->gdb<<endl;
    cout << "algo: " << student->algo<<endl;
    cout << "Work With: ";
    if (!student->workwith.empty()) {
        for (const auto& name : student->workwith) {
            cout << name << "; ";
        }
    } else {
        cout << "None";
    }
    cout << endl;

    cout << "Not With: ";
    if (!student->notwith.empty()) {
        for (const auto& name : student->notwith) {
            cout << name << "; ";
        }
    } else {
        cout << "None";
    }
    cout << endl;
    cout << endl;
}