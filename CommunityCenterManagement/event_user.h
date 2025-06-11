#ifndef __EVENT_USER__H
#define __EVENT_USER__H
#include <string>
enum RESERVATION_STATUS
{
    PENDING,
    COMPLETED,
    CANCELED
};
class event_user
{
private:
    std::string username;
    std::string event_id;
    RESERVATION_STATUS status;
    bool removed;

public:
    event_user(std::string username, std::string eventid);
    void remove();
    bool is_removed();
    std::string get_username();
    std::string get_event_id();
    void change_status(RESERVATION_STATUS new_status);
    RESERVATION_STATUS get_status();
};
#endif