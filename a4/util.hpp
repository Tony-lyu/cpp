#include "student.hpp"
#include <vector>
#include <list>
using namespace std;

void read_csv(string filename, vector<Student> *students);
void group(vector<Student> *students, list<vector<Student>> *teams, int size);
void print_group(list<vector<Student>> *teams);
void printStudents(vector<Student> *students);
void save_teams(list<vector<Student>> *teams);
