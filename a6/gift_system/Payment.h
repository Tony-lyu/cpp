#ifndef PAYMENT_HPP
#define PAYMENT_HPP

#include "Gift.h"
#include "Order.h"
#include <string>
using namespace std;
class Payment {
public:
    // to create an order
    Payment();
    // return the total price of the order
    int total_price();
    // let user choose payment method
    void payment_method(const string& s);
    // let user complete payment, uses total_price and payment_method
    void pay();



private:
    string creditCard;
    string debitCard;
    int amount;
    bool success;
};

#endif 