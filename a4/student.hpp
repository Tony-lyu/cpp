#include <string>
#include <vector>
using namespace std;

struct Student {
    string name;
    int cpp;
    int gdb;
    int algo;
    vector<string> workwith;
    vector<string> notwith;  
    bool placed = false;
};

typedef struct Student Student;
void print(Student *student);