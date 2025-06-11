#include "center.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <iomanip>

bool time_overlap(event e1, event e2)
{
    double d1 = difftime(e1.get_start_time(), e2.get_start_time());
    double d2 = difftime(e1.get_start_time(), e2.get_end_time());
    double d3 = difftime(e1.get_end_time(), e2.get_start_time());
    double d4 = difftime(e1.get_end_time(), e2.get_end_time());
    if (d1 >= 0 && d2 >= 0 && d3 >= 0 && d4 >= 0)
        return false;
    if (d1 <= 0 && d2 <= 0 && d3 <= 0 && d4 <= 0)
        return false;
    return true;
}
time_t parseDateTime(const char *datetimeString, const char *format)
{
    struct tm tmStruct;
    strptime(datetimeString, format, &tmStruct);
    return mktime(&tmStruct);
}

std::string DateTime(time_t time, const char *format)
{
    char buffer[90];
    struct tm *timeinfo = localtime(&time);
    strftime(buffer, sizeof(buffer), format, timeinfo);
    return buffer;
}

void center::set_budget(double value)
{
    if (value >= 0)
        this->budget = value;
}
bool center::add_user(user new_user)
{
    // check if username is not taken
    for (int i = 0; i < this->users.size(); i++)
    {
        if (this->users[i].GetUsername().compare(new_user.GetUsername()) == 0)
        {
            std::cout << "Error -- A user with given username already exist!\n";
            return false;
        }
    }
    this->users.push_back(new_user);
    std::cout << "Success -- User added!\n";
    return true;
}
bool center::add_event(event new_event)
{
    // check if event id is not taken
    for (int i = 0; i < this->events.size(); i++)
    {
        if (this->events[i].get_id().compare(new_event.get_id()) == 0)
        {
            std::cout << "Error -- An event with given id already exist!\n";
            return false;
        }
    }

    // check if the time is available
    bool overlap = false;
    for (int i = 0; i < this->events.size(); i++)
    {
        if (time_overlap(this->events[i], new_event))
        {
            std::cout << "Error -- There is already an event planned in given time!\n";
            return false;
        }
    }

    this->events.push_back(new_event);
    std::cout << "Success -- Event added!\n";
    return true;
}
bool center::cancel_event(std::string event_id)
{
    // check if event exist
    int index = -1;
    for (int i = 0; i < this->events.size(); i++)
    {
        if (this->events[i].get_id().compare(event_id) == 0)
            index = i;
    }
    if (index < 0)
    {
        std::cout << "Error -- Event is not available.\n";
        return false;
    }

    // remove user reservations
    for (int i = 0; i < this->event_users.size(); i++)
    {
        if (this->event_users[i].get_event_id().compare(event_id) == 0)
        {
            this->event_users[i].remove();
        }
    }

    // remove event
    this->events[index].remove();
    std::cout << "Success -- Event removed!\n";
    return true;
}
bool center::reserve_event(std::string username, std::string event_id)
{
    // find the user
    int index = -1;
    for (int i = 0; i < this->users.size(); i++)
    {
        if (this->users[i].GetUsername().compare(username) == 0)
            index = i;
    }
    if (index < 0)
    {
        std::cout << "Error -- User not found.\n";
        return false;
    }

    // find the event
    index = -1;
    for (int i = 0; i < this->events.size(); i++)
    {
        if (this->events[i].get_id().compare(event_id) == 0)
            index = i;
    }
    if (index < 0)
    {
        std::cout << "Error -- Event not found.\n";
        return false;
    }

    // check if reservation is possible
    if (this->events[index].get_guest_count() >= MAX_EVENT_ATTENDANCE)
    {
        std::cout << "Error -- Event reservation is full.\n";
        return false;
    }
    if (this->events[index].get_event_type() == EVENT_TYPE::PRIVATE)
    {
        std::cout << "Error -- Reservation for this event is not available.\n";
        return false;
    }

    // reserve
    event_user reservation = event_user(username, event_id);
    this->event_users.push_back(reservation);
}
bool center::cancel_reservation(std::string username, std::string event_id)
{
    // find the user
    int index = -1;
    for (int i = 0; i < this->users.size(); i++)
    {
        if (this->users[i].GetUsername().compare(username) == 0)
            index = i;
    }
    if (index < 0)
    {
        std::cout << "Error -- User not found.\n";
        return false;
    }

    // find the event
    index = -1;
    for (int i = 0; i < this->events.size(); i++)
    {
        if (this->events[i].get_id().compare(event_id) == 0)
            index = i;
    }
    if (index < 0)
    {
        std::cout << "Error -- Event not found.\n";
        return false;
    }

    // check if the reservation exist
    index = 0;
    for (int i = 0; i < this->event_users.size(); i++)
    {
        if (this->event_users[i].get_username().compare(username) == 0 &&
            this->event_users[i].get_event_id().compare(event_id) == 0)
            index = i;
    }

    // remove the reservation
    if (index < 0)
    {
        std::cout << "Error -- Event not found.\n";
        return false;
    }
    this->event_users[index].remove();
    this->event_users[index].change_status(RESERVATION_STATUS::CANCELED);
    std::cout << "Success -- Event canceled for given username!\n";
    return true;
}
void center::print_schedule()
{
    std::cout << "**************************************\n";
    std::cout << "Enter start time in format (yyyy-mm-dd): \n";
    std::string temp;
    std::cin >> temp;
    temp += " 00:00:00";
    time_t start = parseDateTime(temp.c_str(), TIME_FORMAT.c_str());

    // get endtime
    std::cout << "Enter end time in format (yyyy-mm-dd): \n";
    temp = "";
    std::cin >> temp;
    temp += " 00:00:00";
    time_t end = parseDateTime(temp.c_str(), TIME_FORMAT.c_str());

    std::vector<event> events;
    for (int i = 0; i < this->events.size(); i++)
    {
        if (difftime(start, this->events[i].get_start_time()) * difftime(this->events[i].get_end_time(), end) < 0)
        {
            events.push_back(this->events[i]);
        }
    }
    struct EventTimeComparer {
        bool operator()(event& e1, event& e2) const {
            return e1.get_start_time() < e2.get_start_time();
        }   
    } time_comparer;

std::sort(events.begin(), events.end(), time_comparer);


    if (events.size() == 0)
    {
        std::cout << "There is no event in given time\n";
    }
    else
    {
        for (int i = 0; i < events.size(); i++)
        {

            std ::cout << "------------------------------------------------------------- \n"
                       << "Title: " << std::setw(50) << events[i].get_title() << " ID: " << std::setw(10) << events[i].get_id() << "\n"
                       << "Start: " << std::setw(25) << DateTime(events[i].get_start_time(), TIME_FORMAT.c_str())
                       << "End: " << std::setw(25) << DateTime(events[i].get_end_time(), TIME_FORMAT.c_str()) << "\n"
                       << "Ticket Price: " << std::setw(10) << std::setprecision(2) << events[i].get_price() << "\n"
                       << "------------------------------------------------------------- \n";
        }
    }

    std::cout << "**************************************\n";
}

bool center::make_payment(std::string username, std::string event_id)
{
    // find the user
    int index = -1;
    for (int i = 0; i < this->users.size(); i++)
    {
        if (this->users[i].GetUsername().compare(username) == 0)
            index = i;
    }
    if (index < 0)
    {
        std::cout << "Error -- User not found.\n";
        return false;
    }

    // find the event
    index = -1;
    for (int i = 0; i < this->events.size(); i++)
    {
        if (this->events[i].get_id().compare(event_id) == 0)
            index = i;
    }
    if (index < 0)
    {
        std::cout << "Error -- Event not found.\n";
        return false;
    }

    // check if the reservation exist
    index = -1;
    for (int i = 0; i < this->event_users.size(); i++)
    {
        if (this->event_users[i].get_username().compare(username) == 0 &&
            this->event_users[i].get_event_id().compare(event_id) == 0)
            index = i;
    }
    if (index < 0)
    {
        std::cout << "Error -- Event not found.\n";
        return false;
    }
    this->event_users[index].change_status(RESERVATION_STATUS::COMPLETED);
    std::cout << "Success -- Event reserved for given username!\n";
    return true;
}

void center::add_reservation(event_user event_user){
    this->event_users.push_back(event_user);
}
double center::get_budget()
{
    return this->budget;
}
