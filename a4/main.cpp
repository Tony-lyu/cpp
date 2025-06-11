#include "util.hpp"
#include <iostream>
#include <list>
#include <vector>
using namespace std;
int main(void) {
    cout<<"Please specify the csv file you want to work with"<<endl;
    string file;
    cin>>file;
    cout<<"Please specify team size for grouping"<<endl;
    int size;
    cin>>size;
    vector<Student> students;
    read_csv(file, &students);
    //printStudents(&students);

    // make sure students can be divided into even groups
    while (students.size() % size != 0) {
        cout << "please enter a group size that is a factor of " << students.size()<<endl;
        cout << "please re-enter group size: "<<endl;
        cin >> size;
    }
    int teamcount = students.size() / size;
    // initialize empty teams
    list<vector<Student>> teams;
    for (int i = 0; i < teamcount; ++i) {
        teams.push_back(vector<Student>()); 
    }

    group(&students, &teams, size);
    print_group(&teams);
    save_teams(&teams);
}