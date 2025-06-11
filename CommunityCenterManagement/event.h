#ifndef __EVENT__H
#define __EVENT__H
#include <string>
#include <ctime>
#include "user.h"
enum EVENT_TYPE
{
    PUBLIC,
    PRIVATE
};
enum EVENT_LAYOUT
{
    MEETING,
    LECTURE,
    WEDDING,
    DANCE_ROOM
};
class event
{
private:
    std::string title;
    std::string id;
    std::string owner;
    time_t start_time;
    time_t end_time;
    EVENT_TYPE event_type;
    EVENT_LAYOUT event_layout;
    int guests_count;

    double ticket_price;
    bool removed;

public:
    event(std::string title, std::string id , std::string owner , time_t start, time_t end , EVENT_TYPE event_type , EVENT_LAYOUT event_layout);
    int get_guest_count();
    double get_price();
    bool set_price(double value);
    std::string get_title();
    std::string get_id();
    bool is_removed();
    void remove();
    time_t get_start_time();
    time_t get_end_time();
    EVENT_TYPE get_event_type();
    EVENT_LAYOUT get_event_layout();


};
#endif