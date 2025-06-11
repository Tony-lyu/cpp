#ifndef SELLER_HPP
#define SELLER_HPP

#include "User.h"
#include <string>
#include <vector>

class Seller : public User {
public:
    // to create a Customer
    Seller(const string& username, const string& password);
    // to login with given username and pw
    void login(const string& username, const string& password);
    // logout
    void logout();
    // add the given gift to the store 
    void addItem(Gift& gift, int count); 


private:
    string username;
    string password;
};

#endif 