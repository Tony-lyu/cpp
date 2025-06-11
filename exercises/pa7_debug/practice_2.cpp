// Program to read integers into a 3X3 matrix and display them
// Todo: Fix bugs and makesure program works as intended.
// for each bug fix, add a comments specifying what you fixed.


#include <iostream>
using namespace std;

const int SIZE = 3;
void display(int Matrix[SIZE][SIZE]); // int matrix


int main()
{

  int Matrix[SIZE][SIZE];
  cout << "Enter 9 elements of the matrix:" << endl; // should be cout
  for (int i = 0; i < SIZE; i++) // int i
  {
    
    for (int j = 0; j < SIZE; j++) // for loop syntax
    {
      cin >> Matrix[i][j]; // reverse inner and out loop

    }
  }
  display(Matrix);
  return 0;
}


void display(int Matrix[SIZE][SIZE]) // size is int
{
  for (int i = 0; i < SIZE; i++) // for loop syntax
  {
    for (int j = 0; j < SIZE; j++) // j++

    {
      if (j == 2) {
        cout << Matrix[i][j];
      } else {
        cout << Matrix[i][j] << ", ";
      }
    }

    cout << endl;
  }
}
