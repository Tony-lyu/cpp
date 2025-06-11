// This program allocated memory for an NxM integer array dynamicaly
// The program then prints the 2D array in a matrix form using a combination of * and [] operators
// Note: You can't use ** or [][] for printing the values (use a combination of * and [] only.

// Number of bugs/errors : 6
// line 21 : memory allocation should be int* 
// line 23 : momory allocation should be int
// line 26 : should use ; rather than ,
// line 30 : should use [] to access elements
// line 37 : should use M for column
// line 46 : should free array row with []

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int N = 3, M = 5;
	int i, j;

	// should be int*
	int **d_array = (int **)malloc(N * sizeof(int*)); // Allocating memory for 2D array (N rows)
	for (i = 0; i < N; i++) // for loop syntax

		d_array[i] = (int *)malloc(M * sizeof(int)); // Allocating memory for each row with M columns)
	// Initializing 2D array using [ ][ ] notation
	printf("Initializing array values!\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			d_array[i][j] = i + j; // accessing

		}
	}
	// Accessing 2D array using a combination of * and [] notation
	printf("\n");
	for (i = 0; i < N; i++)
	{

		for (j = 0; j < M; j++) // should be M or column

		{
			cout << *(d_array[i] + j);
		}
		cout << "\n";
	}

	// Deallocating 2D array
	for (i = 0; i < N; i++)

		free(d_array[i]); // correct free

}
