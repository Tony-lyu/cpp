#include "flight.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
using namespace std;

// constant row of 12
const int ROW = 12;
// constant columns
const char columns[6] = {'A', 'B', 'D', 'E', 'F', 'H'};
// admin username and password
const string ADMIN_USR = "Spongebob";
const string ADMIN_PASS = "Squarepants";

// flight constructor
flight::flight() { init(); }

// initialize flight
void flight::init() {
  seats.resize(ROW);
  // add seats to flight
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < 6; j++) {
      Seat s(i + 1, columns[j], false, "");
      seats[i].push_back(s);
    }
  }
}

// print out flight chart, seats are represented by X if taken
void flight::chart() {
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < 6; j++) {
      if (i < 9) { // to make the chart look better, add space for alignment
        cout << " " << seats[i][j].row << seats[i][j].column;
      } else {
        cout << seats[i][j].row << seats[i][j].column;
      }
      if (seats[i][j].assigned) {
        cout << "[X] "; // seat taken
      } else {
        cout << "[ ] "; // seat availiable
      }
      if (seats[i][j].column == 'B' || seats[i][j].column == 'F') {
        cout << "     "; // space for aisle
      }
    }
    cout << endl;
  }
}

// determine if the person has a seat assigned
bool flight::assigned(string name) {
  for (auto &row : seats) {
    for (auto &seat : row) {
      if (seat.assigned && seat.name == name) {
        return true;
      }
    }
  }
  return false;
}

// randomly assign seats for passenger of given name
void flight::getSeat(string name, char c) {
  if (assigned(name)) { // check for existing seat assignment
    cout << "Sorry " << name << " you already have a seat assigned." << endl;
    return;
  }
  srand(time(0)); // time sead or rand
  bool seatLeft = false;
  for (auto &row : seats) { // check if there are seat availiable left
    for (auto &seat : row) {
      if (!seat.assigned) {
        seatLeft = true;
        break;
      }
    }
    if (seatLeft) {
      break;
    }
  }
  // if no seat left, return
  if (!seatLeft) {
    cout << endl;
    cout << "No seats available at this time, there ";
    cout << "will be another flight in 3 hours." << endl;
    return;
  }

  // get row for class
  int rowForClass = (c == 'F') ? 1 : (c == 'B') ? 2 : 12;
  // Randomly assign a seat
  while (true) {
    int r = (rowForClass == 1)   ? 0
            : (rowForClass == 2) ? rand() % 2 + 2
                                 : rand() % 8 + 5;
    int c = rand() % 6; // Random column index (0 to 5)

    // Check if the seat is available
    if (!seats[r][c].assigned) {
      seats[r][c].assigned = true;
      seats[r][c].name = name;
      cout << "Seat assigned: " << seats[r][c].row << columns[c] << endl;
      return;
    }
  }
}

// manully choose a seat for passenger of given name and class
void flight::chooseSeat(string name, char c) {
  if (assigned(name)) { // check for existing seat assignment
    cout << "Sorry " << name << " you already have a seat assigned." << endl;
    return;
  }
  chart(); // print out seat chart to see availiable seats
  int row;
  char column;
  cout << "Enter row number: "; // taken in row number
  cin >> row;
  if (!(row == 1 && c == 'F') && !(row > 1 && row < 5 && c == 'B') &&
      !(row > 4 && row < 13 && c == 'E')) { // check for invalid row number
    cout << "Invalid row number for your class. Please try again." << endl;
    return;
  }
  cout << "Enter column letter: ";
  cin >> column;
  for (auto &r : seats) {
    for (auto &s : r) {
      if (s.row == row && s.column == column) {
        if (!s.assigned) {
          s.assigned = true;
          s.name = name;
          cout << "Seat chosen: " << row << column << endl;
          return;
        } else {
          cout << "Seat is already taken." << endl;
          return;
        }
      }
    }
  }
  cout << "Invalid seat." << endl;
}

// remove a seat assignment for passenger of given name
void flight::removeSeat(string name) {
  for (auto &row : seats) {
    for (auto &seat : row) {
      if (seat.name == name) {
        seat.assigned = false;
        seat.name = "";
        cout << "Seat assignment removed for " << name << endl;
        return;
      }
    }
  }
  cout << "No seat found for " << name << endl; // no seat found for the name
  return;
}

// print boarding pass for passenger of given name
void flight::printBoardingPass(string name) {
  for (auto &row : seats) {
    for (auto &seat : row) {
      if (seat.name == name) { // get class
        string c = (seat.row == 1)                    ? "First Class"
                   : (seat.row >= 2 && seat.row <= 4) ? "Business Class"
                                                      : "Economy Class";
        cout << "########################################################"
             << endl; // to print nicer
        cout << "Boarding Pass for " << name << ": Seat " << seat.row
             << seat.column << ", Class: " << c << endl; // boarding pass
        cout << "########################################################"
             << endl;
        return;
      }
    }
  }
  cout << "No seat assigned to " << name << endl; // no seat found for the name
  return;
}

// show Menu for passenger, loop until user chooses to exit
void flight::passMenu(string name) {
  while (true) {
    // print menu
    cout << endl;
    cout << "please select the option you want to do" << endl;
    cout << "1. seating map/ chart showing all seats and indicating if the "
            "seats are taken"
         << endl;
    cout << "2. get a seat assgined" << endl;
    cout << "3. choose a seat manually" << endl;
    cout << "4. change or cancel seat assignment" << endl;
    cout << "5. print a boarding pass" << endl;
    cout << "6. quit" << endl;
    int n;
    while (!(cin >> n)) { // error handling
      cout << "Please enter a number between 1 and 6!\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch (n) { // switch on user option
    case 1:
      chart();
      break;
    case 2: // random seat assignment
      cout << "Enter your class (F for First Class, B for Business Class, E "
              "for economy class"
           << endl;
      char c;
      cin >> c;
      getSeat(name, c);
      break;
    case 3: // manual seat assignment
      cout << "Please enter class you want to choose: " << endl;
      cout << "Enter F for first class, B for business class, E for economy"
           << endl;
      char c1;
      cin >> c1;
      if (c1 == 'F' || c1 == 'B' || c1 == 'E') { // force class to be F, B, or E
        cout << "pleaes enter 1 if you want to choose seat manually, 2 if you "
                "want to choose seat randomly"
             << endl;
        int choice;
        cin >> choice;
        if (choice == 1) { // manual
          chooseSeat(name, c1);
          break;
        } else if (choice == 2) { // random assignment
          getSeat(name, c1);
          break;
        }
      } else {
        cout << "Invalid class" << endl;
        break;
      }
    case 4: // change or cancel seat assignment
      cout << "please enter 1 if you want to cancel the seat or 2 if you want "
              "to change the seat"
           << endl;
      int n;
      cin >> n;
      if (n == 1) {
        removeSeat(name);
        break;
      } else { // cancel the seat first
        removeSeat(name);
        cout << "Enter 1 if you want a upgrade, 2 if you want a downgrade, or "
                "anything else to keep the current class"
             << endl;
        int up;
        cin >> up;
        if (up == 1) { // upgrade
          cout << "Enter class you want to upgrade to (F for First Class, B "
                  "for Business Class)"
               << endl;
          char upgrade;
          cin >> upgrade;
          chooseSeat(name, upgrade);
          break;
        } else if (up == 2) { // downgrade
          cout << "Enter class you want to downgrade to (B for Business Class, "
                  "E for economy class)"
               << endl;
          char downgrade;
          cin >> downgrade;
          chooseSeat(name, downgrade);
          break;
        } else {
          char current;
          for (auto &r : seats) { // get current class
            for (auto &s : r) {
              if (s.name == name) {
                current = s.column;
                break;
              }
            }
          }
          chooseSeat(name, current); // keep the current class
        }
      }
    case 5:
      printBoardingPass(name);
      break;
    case 6: // quit loop
      return;
    }
  }
}

// show menu for admin, loop until user chooses to exit
void flight::adminMenu() {
  while (true) { // loop until user chooses to exit
    // print menu
    cout << endl;
    cout << "please select the option you want to do" << endl;
    cout << "1. seating map/ chart showing all seats and indicating if the "
            "seats are taken"
         << endl;
    cout << "2. print passenger manifest" << endl;
    cout << "3. load previous manifest" << endl;
    cout << "4. save current manifest" << endl;
    cout << "5. reassign or cancel seat assignment" << endl;
    cout << "6. quit" << endl;
    int n;
    while (!(cin >> n)) {
      cout << "Please enter a number between 1 and 6!\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch (n) { // switch on user input
    case 1:
      chart(); // print seating chart
      break;
    case 2:
      printManifest(); // print passenger manifest
      break;
    case 3:
      loadManifest(); // load previous manifest
      break;
    case 4:
      saveManifest(); // save current manifest
      break;
    case 5: { // change or cancel seat for passenger
      cout << "please enter 1 if you want to cancel the seat or 2 if you want "
              "to change the seat"
           << endl;
      int i;
      while (!(cin >> i)) {
        cout << "Please enter 1 or 2!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      string name;
      cout << "please enter the name of the passenger" << endl;
      cin >> name;
      if (i == 1) {
        removeSeat(name);
        break;
      } else {
        removeSeat(name);
        cout << "Please enter F for first class, B for business class, E for "
                "economy"
             << endl;
        char c;
        while (!(cin >> c)) {
          cout << "Please enter F, B or E!\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        chooseSeat(name, c);
        break;
      }
    }
    case 6: // quit loop
      return;
    }
  }
}

// login flight system
void flight::login() {
  // check for passenger or admin
  cout << "Please press 1 if you are a passenger, 2 if you are an admin"
       << endl;
  int passenger;
  while (!(cin >> passenger)) {
    cout << "Please enter 1 or 2!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  if (passenger == 1) {                       // passenger login
    cout << "Please enter your name" << endl; // get user's name
    string name;
    cin.ignore();
    std::getline(cin, name);
    for (auto &row : seats) {
      for (auto seat : row) {
        if (seat.name == name) { // avoid duplicate name here
          cout << "Please add a last name or middle name initial." << endl;
          std::getline(cin, name);
          break;
        }
      }
    }
    cout << "Welcome on board " << name << endl; // print welcome message
    passMenu(name);                              // start passenger menu loop
    return;
  } else { // admin login
    while (true) {
      cout << "Please enter your username" << endl;
      string usrname;
      cin >> usrname;
      if (usrname == ADMIN_USR) { // check for admin creds
        cout << "Please enter your password" << endl;
        string pass;
        cin >> pass;
        if (pass == ADMIN_PASS) { // check for admin creds
          break;
        } else {
          cout << "Wrong password" << endl;
        }
      } else {
        cout << "Wrong username" << endl;
      }
    }
  }
  adminMenu(); // start admin menu loop
}

// print passenger manifest
void flight::printManifest() {
  manifest.clear();
  // put all assigned seats into manifest
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < 6; j++) {
      if (seats[i][j].assigned) {
        manifest.push_back(&seats[i][j]);
      }
    }
  }

  // Ask user for sorting preference
  cout << "Choose sorting option: \n1. Seat Number Ascending\n2. Seat Number "
          "Descending\n";
  cout << "3. Name A-Z\n4. Name Z-A\n5. Class F\n 6. Class E\n";
  int choice;
  while (!(cin >> choice)) {
    cout << "Please enter a number!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  // switch on user choice
  switch (choice) {
  case 1: // Seat Number Ascending
    sort(manifest.begin(), manifest.end(), [](const Seat *a, const Seat *b) {
      // if row number is the same, sort by column number
      return a->row == b->row ? a->column < b->column : a->row < b->row;
    });
    break;
  case 2: // Seat Number Descending
    sort(manifest.begin(), manifest.end(), [](const Seat *a, const Seat *b) {
      // if row number is the same, sort by column number in reverse order
      return a->row == b->row ? a->column > b->column : a->row > b->row;
    });
    break;
  case 3: // Name A-Z
    sort(manifest.begin(), manifest.end(), [](const Seat *a, const Seat *b) {
      // directly compare the names
      return a->name < b->name;
    });
    break;
  case 4: // Name Z-A
    sort(manifest.begin(), manifest.end(), [](const Seat *a, const Seat *b) {
      // directly compare the names in reverse order
      return a->name > b->name;
    });
    break;
  case 5: // Class F first
    sort(manifest.begin(), manifest.end(), [](const Seat *a, const Seat *b) {
      // since class is determined by row number, sort by row number
      return a->row == b->row ? a->column < b->column : a->row < b->row;
    });
    break;
  case 6: // Class E first
    sort(manifest.begin(), manifest.end(), [](const Seat *a, const Seat *b) {
      // sice class is determined by row number, sort by row number in reverse
      return a->row == b->row ? a->column > b->column : a->row > b->row;
    });
    break;
  default:
    cout << "Invalid choice. Default sort to seat number ascending." << endl;
    sort(manifest.begin(), manifest.end(), [](const Seat *a, const Seat *b) {
      return a->row == b->row ? a->column < b->column : a->row < b->row;
    });
  }

  // Print sorted manifest
  cout << left << setw(15) << "Name" << setw(10)
       << "Seat" // offset for formatting
       << "Class" << endl;
  cout << "-----------------------------------" << endl;
  for (const auto &seat : manifest) {
    // determine passenger class
    string classType = (seat->row <= 1)   ? "First"
                       : (seat->row <= 4) ? "Business"
                                          : "Economy";
    cout << left << setw(15) << seat->name << setw(10)
         << to_string(seat->row) + seat->column << classType << endl;
  }
}

// load previous manifest
void flight::loadManifest() {
  ifstream file("manifest.txt"); // read from the file manifest.txt
  string line, name;
  int row;
  char column;

  if (file.is_open()) { // if file is open
    manifest.clear();   // Clear current manifest
    while (getline(file, line)) {
      stringstream ss(line);
      getline(ss, name, ',');
      ss >> row;
      ss.ignore(); // Ignore the comma
      ss >> column;

      // Find the seat and add it to the manifest
      for (auto &rowVec : seats) {
        for (auto &seat : rowVec) {
          if (seat.row == row && seat.column == column) {
            seat.name = name;
            seat.assigned = true;
            manifest.push_back(&seat);
            break;
          }
        }
      }
    }
    file.close();
    cout << "Manifest loaded successfully." << endl;
  } else {
    cout << "Unable to open file for reading." << endl;
  }
}

// save current manifest
void flight::saveManifest() {
  ofstream outFile("manifest.txt");     // save to file manifest.txt
  if (outFile.is_open()) {              // if file is open
    for (const auto &seat : manifest) { // save contends of manifest
      outFile << seat->name << "," << seat->row << "," << seat->column << "\n";
    }
    outFile.close();
    cout << "Manifest saved successfully." << endl;
  } else {
    cout << "Unable to open file for writing." << endl;
  }
}

// manually add a passenger
void flight::addPassenger(string name, int row, int column) {
  // no checks for seat availability needed for this function
  // because it is only used for testing admin functionalities
  // all seats would be avaialble for passengers.
  Seat s(row, columns[column - 1], true, name);
  seats[row - 1][column - 1] = s;
}

void flight::fillFirst() {
  // fill first class seats for testing
  addPassenger("Amy", 1, 1);
  addPassenger("Brandon", 1, 2);
  addPassenger("Cindy", 1, 3);
  addPassenger("Dirk", 1, 4);
  addPassenger("Ellen", 1, 5);
  addPassenger("Frank", 1, 6);
}