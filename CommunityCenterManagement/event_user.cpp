#include "event_user.h"

void event_user::remove()
{
    this->removed = true;
}
bool event_user::is_removed() { return this->removed; }
std::string event_user::get_username() { return this->username; }
std::string event_user::get_event_id() { return this->event_id; }
event_user::event_user(std::string username, std::string eventid)
{
    this->username = username;
    this->event_id = eventid;
}

void event_user::change_status(RESERVATION_STATUS new_status) { this->status = new_status; }
RESERVATION_STATUS event_user::get_status()
{
    return this->status;
}