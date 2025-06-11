#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "User.h"
#include <string>
#include <vector>
using namespace std;
class Customer : public User {
public:
    // to create a Customer
    Customer(const string& username, const string& password);
    // to login with given username and pw
    void login(const string& username, const string& password);
    // logout
    void logout();
    // add the given gift to gift list
    void addItem(Gift& gift, int count); 
    // checkout gifts
    void checkout(vector<Gift> giftList);
private:
    string username;
    string password;
    vector<Gift> giftLists;
};

#endif 