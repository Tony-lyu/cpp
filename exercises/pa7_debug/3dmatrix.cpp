// Program to read 3-dimensional matrix and display the elements as N^3 matrix
// TODO
// take the SIZE of the matrix as input from the user
// initize matrix using update_3d method (see comments below)
// display method must not be able to modify array elements (update the code as needed)
// display method must use a single loop/iterator to print the entire array with addresses
// display cannot use nested loops

// updates:
// get user input
// fix for loop syntax
// random generator for array values
// address and value printing

#include <iostream>

using namespace std; // added 


void update_3d(double*** Matrix_3d, int size);
void display_1d(double* Matrix_3d, int size);

int main(void)
{

	// get size from user
	int size;
    cout << "Enter the size of the 3D matrix: ";
    cin >> size;

    double*** Matrix_3d = new double**[size];

    for (int i = 0; i < size; ++i) {
        Matrix_3d[i] = new double*[size];
        for (int j = 0; j < size; ++j) {
            Matrix_3d[i][j] = new double[size];
        }
    }


	update_3d(Matrix_3d, size);
	// display the values
	display_1d(&Matrix_3d[0][0][0], size);

	return 0;

}

void update_3d(double*** matrix, int size)
{
	cout << "Entering N^3 elements of the matrix:" << endl;



	for (int i = 0; i < size; i++)
	{
		
		for (int j = 0; j < size; j++)
		{
			
			for (int k = 0; k < size; k++)
			{
				// generate number in range [-50, 50)

				matrix[i][j][k] = rand() % 100 - 50;
			}
		}
	}
}

// update as needed. 1 'for' loop only with 1 iterator to print all values with addresses
// must not be able to update the array.
// Share any observations.
void display_1d(double* matrix, int size) {

	
	int n = size * size * size;
	for (int i= 0; i < n; i++) {

	cout << (matrix + i) << ", " << *(matrix + i) << endl;
    }
}
