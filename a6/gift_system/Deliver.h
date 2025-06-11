#ifndef DELIVER_HPP
#define DELIVER_HPP

#include "User.h"
#include <string>
#include <vector>
using namespace std;
class Deliver : public User {
public:
    // to create a Delivery
    Deliver(bool deliver);
    // to update delivery options
    void delivery_options(string& from, string& to, string time);
    // calculate price for the delivery
    double get_price();
    

private:
    bool deliver;
    string from_address;
    string to_address;
    string time;
    double price;

};

#endif 