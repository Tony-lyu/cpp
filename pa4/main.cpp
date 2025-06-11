    // Read the file containing numbers.
    // Split the content into rows, and row into numbers.
    // Find size for the 2D vector and 3D array.
    // Create arrays.
    // Read the numbers into arrays.
    // Calculate the sum and print 

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip> 

using namespace std;

void fill_2d(const vector<vector<double>>& vec, const string& fil);
void fill_3d(double arr[][3][4], int depth, int row, int col, const string& file);
void print_2d(const vector<vector<double>>& vec);
void print_3d(double arr[][3][4], int depth, int row, int col);

int main() {
    ifstream infile("numbers.txt");
    string line;
    vector<double> nums;
    vector<vector<double>> vec2d;
    const int depth = 3, rows = 3, cols = 3;
    double arr3d[depth][rows][4] = {}; 

    while (getline(infile, line)) {
        istringstream iss(line);
        double num;
        vector<double> temp;
        while (iss >> num) {
            temp.push_back(num);
            nums.push_back(num);
        }
        vec2d.push_back(temp);
    }

    int count = 0;
    for (int i = 0; i < vec2d.size(); i++) {
        for (int j = 0; j < vec2d[i].size(); j++) {
            if (i < depth && j < rows) {
                arr3d[i][j][count % cols] = vec2d[i][j];
            }
            count++;
        }
    }

    fill_2d(vec2d, "2d.txt");
    fill_3d(arr3d, depth, rows, cols, "3d.txt");

    cout << "2D Vector:" << endl;
    print_2d(vec2d);
    cout << "3D Array:" << endl;
    print_3d(arr3d, depth, rows, cols);

    double sum = 0.0;
    for (double num : nums) {
        sum += num;
    }
    cout << "Sum : " << sum << endl;
    return 0;
}

void fill_2d(const vector<vector<double>>& vec, const string& file) {
    ofstream outfile(file);
    for (const auto& row : vec) {
        for (const auto& val : row) {
            outfile << setw(10) << val;
        }
        outfile << '\n';
    }
    outfile.close();
}

void fill_3d(double arr[][3][4], int depth, int row, int col, const string& file) {
    ofstream outfile(file);
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < row; j++) {
            for (int k = 0; k < col; k++) {
                outfile << setw(10) << arr[i][j][k];
            }
            outfile << '\n';
        }
        outfile << '\n';
    }
    outfile.close();
}

void print_2d(const vector<vector<double>>& vec) {
    for (const auto& row : vec) {
        for (const auto& val : row) {
            cout << setw(10) << val;
        }
        cout << '\n';
    }
}

void print_3d(double arr[][3][4], int depth, int row, int col) {
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < row; j++) {
            for (int k = 0; k < col; k++) {
                cout << setw(10) << arr[i][j][k];
            }
            cout << '\n';
        }
        cout << '\n'; // Separate layers
    }
}