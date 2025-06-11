#include <iostream>
using namespace std;
#include "flight.hpp"

int main() {
  flight f = flight();
  // f.fillFirst() auto fills first class seats, uncomment for the line
  // below for testing. 
  
  // f.fillFirst();

  f.addPassenger("Groot", 2, 3);
  f.addPassenger("Hill", 2, 5);
  f.addPassenger("Iva", 3, 1);
  f.addPassenger("Jim", 3, 4);
  f.addPassenger("Kevin", 5, 5);
  f.addPassenger("Levy", 6, 1);
  f.addPassenger("Mike", 7, 4);
  f.addPassenger("Nancy", 7, 3);
  f.addPassenger("Omar", 8, 2);
  f.addPassenger("Pierce", 9, 2);
  f.addPassenger("Quin", 8, 5);
  f.addPassenger("Ryan", 10, 1);
  f.addPassenger("Sarah", 12, 4);

  f.login();

  // in case grader wants to check for admin reassign or cancel
  // use addPassenger(string name, int row, int column);
  // to manually add seats to flight before logging in

  // example use:
  // flight f1 = flight();
  // f.addPassenger("John", 1, 1);
  // f.addPassenger("Jane", 1, 2);
  // f.addPassenger("Jack", 5, 3);
  // f.login();


  // admin username: "Spongebob"
  // admin password: "Squarepants"
}