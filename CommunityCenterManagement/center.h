#ifndef __CENTER__H
#define __CENTER__H

#include "event.h"
#include "user.h"
#include "event_user.h"
const int MAX_EVENT_ATTENDANCE = 25;
const std::string TIME_FORMAT = "%Y-%m-%d %H:%M:%S";

time_t parseDateTime(const char *datetimeString, const char *format);

std::string DateTime(time_t time, const char *format);

class center
{
private:
public:
    double budget;

    std::vector<event> events;
    std::vector<event_user> event_users;
    std::vector<user> users;
    double get_budget();
    void set_budget(double value);
    /// @brief adds new user to database.
    /// @param new_user
    /// @return true if new user is added.
    bool add_user(user new_user);
    /// @brief adds new event to events list.
    /// @param new_event
    /// @return true if the event has unique id and schedule is not conflicting.
    bool add_event(event new_event);
    /// @brief cancels event and removes all reservations
    /// @param event
    /// @return true if the event is in event list and is removed.
    bool cancel_event(std::string event_id);
    /// @brief reserves event for given user.
    /// @param username
    /// @param event_id
    /// @return true if user and event is valid and the user reserved the event.
    bool reserve_event(std::string username, std::string event_id);
    /// @brief
    /// @param username
    /// @param event_id
    /// @return true if user and event is valid and user reservation is removed.
    bool cancel_reservation(std::string username, std::string event_id);
    /// @brief pays for a reservation
    /// @param username
    /// @param event_id
    /// @return true if user and event is valid and reservation is pending.
    bool make_payment(std::string username, std::string event_id);
    /// @brief asks for filters and prints reservation list for given period
    void print_schedule();
    /// @brief directly inserts reservation -- for loading only
    /// @param event_user
    void add_reservation(event_user event_user);
};
#endif