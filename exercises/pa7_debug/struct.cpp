// This program includes a struct called car that is used to store information
// about a given car The program should ask the user for information about their
// car and initialize a car structure with the given information The program
// should also print the information using a pointer to the initialized struct
// The information printed using the struct and the pointer should be the same


#include <iostream>
#include <string>

using namespace std; // namespace inclueded
struct car
{
     string name; // string

     int modelYear;
     float speed;
};

int main()
{

     string n; // change to string

     int a;
     float w;

     struct car c;
     car *cPtr = &c;

     cout << "What is your favorite car's name: ";
     cin >> n;

     c.name = n; // change to c.name

     cout << "When was it launched : ";
     cin >> a; // cin 
     c.modelYear = a;

     cout << "How much speed does it give : ";
     cin >> w; // should be >>
     c.speed = w; // w is the value assigned 

     cout << "Car's name is " << c.name << ", and should be the same as " << cPtr->name
          << ".\n"; // use -> to access value, added space

     cout << "Car's model year is" << c.modelYear << ", and should be the same as "
          << cPtr->modelYear << ".\n"; // -> for accessing

     cout << "Car's speed is" << c.speed << ", and should be the same as "
          << cPtr->speed << ".\n";
}
