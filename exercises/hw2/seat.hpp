#include <string>

using namespace std;

struct Seat {
    int row;
    char column;
    bool assigned;
    string name;
    // Seat construtor
    Seat(int row, char column, bool assigned, string name) : row(row), column(column), assigned(assigned), name(name) {}
};