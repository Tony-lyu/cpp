#ifndef ORDER_HPP
#define ORDER_HPP

#include "Gift.h"
#include <string>
using namespace std;
class Order {
public:
    // to create an order
    Order(const string& customer, vector<Gift> gifts);
    // return the total price of the order
    const int total_price();
    // Pay for the gifts, show deliver options
    void pay();

private:
    string name;
    vector<Gift> gifts;
};

#endif 