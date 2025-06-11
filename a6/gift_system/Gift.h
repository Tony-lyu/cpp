#ifndef GIFT_HPP
#define GIFT_HPP

#include "Store.h"
#include <string>
using namespace std;
class Gift {
public:
    // to create a Gift
    Gift(const string& name, int price, int count, Store store);
    // to sell the gift
    void sell(int count);
    // add stock
    void addstock(int count);
    // getter for price
    int get_price();

private:
    string name;
    int price;
    int count;
    Store store;
};

#endif 