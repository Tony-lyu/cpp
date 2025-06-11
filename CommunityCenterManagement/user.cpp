#include "user.h"
/// @brief checks if the password is valid.
///  A valid password must be at least 4 characters.
/// it should contain numbers, alphabets and special characters
/// @param password 
/// @return 
bool isPasswordValid(std::string password)
{
    // length >= 4
    if(password.length() < 4)
        return false;
    
    int spaces = 0 , digits = 0 , alphabets = 0 , specials = 0;

    for(int i =0 ; i < password.length() ; i ++)
    {
        if(isspace(password.at(i))!=0)
            spaces ++;
        else if(isalpha(password.at(i))!=0)
            alphabets ++;
        else if(isdigit(password.at(i))!=0)
            digits ++;
        else 
            specials ++;
    }
    // no space
    if(spaces > 0)
        return false;
    // contains numbers
    if(digits == 0)
        return false;
    // contains alphabets
    if(alphabets == 0)
        return false;
    // contain special charachter
     if(specials ==0 )
          return false;
    return true;
}
user::user(std::string username, std::string password , USER_TYPES user_type)
{
    this->username = username ;
    this->password = password;
    this->user_type = user_type;
}

std::string user::GetUsername(){
    return this->username;
}
std::string user::Get_password(){
    return this->password;
}
bool user::check_password(std::string password){
    return password.compare(this->password)==0;
}
bool user::change_password(std::string password)
{
    if(isPasswordValid(password))
    {
        this->password = password;
    }
    return false;
}
USER_TYPES user::GetUser_type(){
    return this->user_type;
}
bool user::set_userType(USER_TYPES user_type){
    this->user_type = user_type;
}