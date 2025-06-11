#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "Gift.h"
#include "Order.h"

using namespace std;
class User {
public:
    // constructor, to create a user 
    User(const string& username, const string& password);
    // to login with given username and pw
    virtual void login(const string& username, const string& password) = 0;
    // logout
    virtual void logout() = 0;
    // add the given gift to gift list
    virtual void addItem(const Gift& gift, int count) = 0;
    // checkout gifts
    virtual void checkout(const vector<Gift> giftList) = 0;

private:
    string username;
    string password;
};

#endif 
