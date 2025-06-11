#include "seat.hpp"
#include <vector>

struct flight {
    // to store manifest
    vector<Seat *> manifest;
    // to store seats on the flight
    vector<vector<Seat>> seats;
    // flight constructor
    flight();

    void init(); // initialize seats on flight
    void login(); // login as user or employee
    void passMenu(string name); // menu loop for passengers
    void adminMenu(); // menu loop for admins
    void chart(); // print seating chart
    void getSeat(string name, char c); // assign a seat for passenger
    void chooseSeat(string name, char c); // choose a seat for passenger
    void removeSeat(string name); // remove a seat for passenger
    void printBoardingPass(string name); // print boarding pass
    void printManifest(); // print manifest
    void loadManifest(); // load manifest from manifest.txt
    void saveManifest(); // save manifest to manifest.txt
    bool assigned(string name); // to check if seat is assigned
    void addPassenger(string name, int row, int column); // add passenger to flight
    void fillFirst(); // auto fill first class seats
};