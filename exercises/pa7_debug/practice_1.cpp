// Program to check if the user-provided number is a palindrome

// TODO: Fix the bugs and make sure the program runs as expected.
// Provide a brief comment identifying each bug fixed.

#include <iostream>

using namespace std; // added to use cout 
bool func(int x);
int main() // int return type
{
        int input; // input should be int, initialized to 0
        cout << "enter an integer please";
        cin >> input;
        bool returned_val = func(input); // return value; func name; input name fixed
        if (!returned_val) // result reversed
        {
                cout << "It is not a palindrome" << endl; // "" for string, add ;

        }
        else
        {
                cout << "It is a palindrome" << endl;
        }


        return 0; // added ;

}

// the return value of your func should be true / false only
bool func(int n)
{

        if (n < 0) return false; // negative number is not palindrome
        int temp = 0; // initilize temp
        int cp = n; // initialize copy of input
        int remainder; // initialize remainder
        while (n != 0) // should be !=
        {
                remainder = n % 10; // should be remainder
                temp = temp * 10 + remainder; // assgin value to temp
                n = n / 10; // assign value to n
        }

        return cp == temp; // simplify and fix logic

}
