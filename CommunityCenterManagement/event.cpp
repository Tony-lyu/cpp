#include "event.h"
event::event(std::string title, std::string id, std::string owner, time_t start, time_t end, EVENT_TYPE event_type, EVENT_LAYOUT event_layout)
{
    this->title = title;
    this->id = id;
    this->owner = owner;
    this->start_time = start;
    this->end_time = end;
    this->event_type = event_type;
    this->event_layout = event_layout;
}
int event::get_guest_count()
{
    return this->guests_count;
}
double event::get_price()
{
    return this->ticket_price;
}
bool event::set_price(double value)
{
    if (value >= 0)
    {
        this->ticket_price = value;
        return true;
    }
    return false;
}
std::string event::get_title()
{
    return this->title;
}
std::string event::get_id()
{
    return this->id;
}
bool event::is_removed()
{
    return this->removed;
}
void event::remove()
{
    this->removed = true;
}

time_t event::get_start_time()
{
    return this->start_time;
}
time_t event::get_end_time()
{
    return this->end_time;
}
EVENT_TYPE event::get_event_type()
{
    return this->event_type;
}
EVENT_LAYOUT event::get_event_layout()
{
    return this->event_layout;
}