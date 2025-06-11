// This program should read any string (including spaces) from the user and print it using a character pointer
// The program is setup to use pointer offset notation to get each character of the string

// Number of bugs/errors : 8


#include <iostream> // fix import
#include <string>

using namespace std;


int main() // return type
{
  char s[200]; // increase size
  char *cPtr; // should be a pointer
  cin.getline(s, sizeof(s)); // to include space
  cPtr = s;
  while (*cPtr != '\0') // while logic
  {
    cout << *cPtr; // first print
    cPtr++; // then incerase

  }
  cout << "\n";
  return 0;
}
