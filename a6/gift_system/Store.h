#ifndef STORE_HPP
#define STORE_HPP

#include "Order.h"
#include "Gift.h"
#include <string>
using namespace std;
class Store {
public:
    // to create a Store
    Store(const string& name, const string&owner, vector<Gift> gifts);
    // print all the gifts and stock count
    void show();
    // sell the given gift n times, add price to storeCredit
    void sell(const string& gift, int count);
    // add a gift to the store
    void add(const string& gift, int count);
    // add stock 
    void addstock(const string& gift, int count);
    // remove the gift from the store
    void remove(const string& gift);

private:
    string name;
    string owner;
    vector<Gift> gifts;
    // how much money the store has
    int storeCredit;
};

#endif 