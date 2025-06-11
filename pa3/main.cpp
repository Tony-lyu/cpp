#include <bitset>
#include <iostream>
#include <limits>
// AUTHOER: ETHAN SAM
//          TONY LYU

using namespace std;

class Athlete {
  // private member variables (one static and one non-static)
private:
  int age;
  static string team;
  // public member variables (one static and one non-static)
public:
  string name;
  static string sport;

  // getters and setters
  void set_name(string n) { name = n; }
  void set_sport(string s) { sport = s; }
  string get_name(void) { return name; }
  string get_sport(void) { return sport; }
  void set_age(int a) { age = a; }
  void set_team(string t) { team = t; }
  int get_age(void) { return age; }
  string get_team(void) { return team; }
  // function prototype for print function
  void print();
};
// initializing static member variables
string Athlete::team = "Team 0";
string Athlete::sport = "Tennis";

// implementation of print function for Athlete class
void Athlete::print() {
  cout << "Name: " << name << endl
       << "Age: " << age << endl
       << "Sport: " << sport << endl
       << "Team: " << team << endl
       << "Name's address:" << &name << endl
       << "Sport's address: " << static_cast<void *>(&sport) << endl
       << "Age's address: " << &age << endl
       << "Team's address: " << static_cast<void *>(&team) << endl
       << endl;
}

int main() {
  // create athlete1 and athlete2
  Athlete athlete1, athlete2;
  // print athlete1 and athlete2 addresses
  cout << "Athlete1's address: " << &athlete1 << endl;
  cout << "Athlete2's address: " << &athlete2 << endl;
  // set athlete1 and athlete2 fields
  athlete1.set_name("Tony");
  athlete1.set_sport("Soccer");
  athlete1.set_age(21);
  athlete1.set_team("Team 1");
  athlete2.set_name("Ethan");
  athlete2.set_sport("Basketball"); // both athletes play basketball because this sets the sport for both athletes
  athlete2.set_age(20);
  athlete2.set_team("Team 2"); // both athletes are on team 2 because this sets team for both athletes
  // print out athlete values and addresses
  athlete1.print();
  athlete2.print();
  // athlete1 and athlete2 have same team and sport because we set the static member variable, the address of the static member variables is the same for both athletes too. 
  // athlete1 and athlete2 have different names and ages though because we set the non-static member variable for them separately
  // ages address is the same as the respective athlete's address, maybe because the address for the athlete object is a pointer to the starting point on the stack where the object is stored. Since the age is the first non-static variable, it gets the same address as the object. Adding on that observation, the address of the name variable is close to the one of the age variable, since name is the nexting variable in the object.
}
