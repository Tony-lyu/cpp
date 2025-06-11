#ifndef __USER__H
#define __USER__H
#include <string>
#include <vector>
#include "event.h"

enum USER_TYPES {
    CITY, RESIDENT, NON_RESIDENT
};

class user{
    private:
        std::string username;
        std::string password;
        USER_TYPES user_type;

    public:
        user(std::string username, std::string password , USER_TYPES user_type);
        std::string GetUsername();
        std::string Get_password();
        bool check_password(std::string password);
        USER_TYPES GetUser_type();

        bool change_password(std::string new_password);
        bool set_userType(USER_TYPES user_type);

};
#endif