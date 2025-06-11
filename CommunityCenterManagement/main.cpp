#include "center.h"
#include "event.h"
#include "pay.h"
#include "user.h"
#include "event_user.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
const string DATA_FILE = "data.ccm";

const string DELIMITTER = "#########################";

time_t parseDateTime(const string& dateTimeStr) {
    struct tm tm;
    strptime(dateTimeStr.c_str(), "%Y-%m-%d %H:%M", &tm);
    return mktime(&tm);
}
void LoadData(string filename, center *center, vector<user> *users, vector<event> *events, vector<event_user> *event_users)
{
    // open the file
    ifstream input(filename);
    if (input)
    {
        string temp;

        // read initial comments
        getline(input, temp);
        getline(input, temp);

        // Read the budget
        getline(input, temp);
        getline(input, temp);
        center->set_budget(stod(temp));

        // read users info
        getline(input, temp); //delimiter
        getline(input, temp);
        int user_count = stoi(temp);
        if (user_count != 0) {
            for (int i = 0; i < user_count; i++) {
                getline(input, temp); 
                stringstream ss(temp);
                string username, password;
                int user_type;
                ss >> username >> password >> user_type;
                users->emplace_back(username, password, static_cast<USER_TYPES>(user_type));
            }
        }

        // read events 
        getline(input, temp);
        getline(input, temp);
        int event_count = stoi(temp);
        if (event_count != 0) {
            for (int i = 0; i < event_count; i++) {
               getline(input, temp);
               stringstream ss(temp);
               string title, id, owner, start, end;
              int event_type, event_layout, guests_count;
              double ticket_price;

              ss >> title >> id >> owner >> start >> end >> event_type >> event_layout >> guests_count >> ticket_price;
              events->emplace_back(title, id, owner, parseDateTime(start), parseDateTime(end),
                                         static_cast<EVENT_TYPE>(event_type), static_cast<EVENT_LAYOUT>(event_layout));
         }
        }
        // read event_users
        getline(input, temp);
        getline(input, temp);
        int event_user_count = stoi(temp);
        if (event_user_count != 0) {
            for (int i = 0; i < event_user_count; ++i) {
                getline(input, temp);
                stringstream ss(temp);
                string username, event_id;
                int status;
                ss >> username >> event_id;
                event_users->emplace_back(username, event_id);
            }
        }
        input.close();
    }
    else
    {
        cout << "Error opening database file!\n";
    }
}

void SaveData(string filename, center *center, vector<user> *users)
{
    ofstream output(filename);

    // initial comments
    output << "Community Center Management Data File\n"
           << "Last Saved: " << DateTime(time(0), TIME_FORMAT.c_str()) << endl; 

    output << DELIMITTER << "\n";

    // add center info

    output << (center ? center->get_budget() : 0) << "\n";
    output << DELIMITTER << "\n";
    // add users info
    output << (users ? users->size() : 0) << "\n";
    for (auto& user : *users) {
        output << user.GetUsername() << "\n"
               << user.Get_password() << "\n"
               << user.GetUser_type() << "\n";
    }

    output << DELIMITTER << "\n";
    // add events info
    output << center->events.size() << "\n";

    for (int i = 0; i < center->events.size(); i++)
    {
        output << center->events[i].get_title() << "\n"
               << center->events[i].get_id() << "\n";
    }

    output << DELIMITTER << "\n";
    // add event_users
    output << center->event_users.size() << "\n";
    for (int i = 0; i < center->event_users.size(); i++)
    {
        output << center->event_users[i].get_username() << "\n"
               << center->event_users[i].get_event_id() << "\n"
               << center->event_users[i].get_status() << "\n";
    }

    output << DELIMITTER << "\n";
    // Close the file
    output.close();
}
// checks if a user with given credentials exist. if a user found
// the "user" will be updated.
void check_login(string username, string password, user *new_user, vector<user> *users)
{
    for (auto& u : *users) {
        if (u.GetUsername() == username && u.check_password(password)) {
            new_user = &u; 
            cout << "Login successful!" << endl;
            return;
        }
    }
    cout << "Invalid username or password." << endl;
}
/// @brief checks if the new username is available and adds it to users
/// @param username
/// @param password
/// @param user
/// @param users
void check_signup(string username, string password, user*& current_user, vector<user>* users, center community_center, string type) {
    for (auto& u : *users) {
        if (u.GetUsername() == username) {
            cout << "Username is already taken." << endl;
            return;
        }
    }
    USER_TYPES u;
    if (type == "resident") {
        u = RESIDENT;
    } else if (type == "non-resident") {
        u = NON_RESIDENT;
    } else {
        cout << "Cannot create city account." << endl;
        return;
    }

    user new_user(username, password, u);
    users->push_back(new_user);
    current_user = &users->back(); 
    cout << "Signup successful! Welcome, " << username << "!" << endl;

    // Save to data file
    SaveData(DATA_FILE, &community_center, users);
}

void create_event(center* community_center) {
    string title, id, owner, temp;
    string start, end;
    int event_type, event_layout, guests_count;
    double ticket_price;
    getline(cin, temp);
    cout << "Enter event title: ";
    getline(cin, title);
    cout << "Enter event ID: ";
    getline(cin, id);
    cout << "Enter event owner username: ";
    getline(cin, owner);
    cout << "Enter start time (YYYY-MM-DD HH:MM): ";
    getline(cin, start);
    cout << "Enter end time (YYYY-MM-DD HH:MM): ";
    getline(cin, end);
    cout << "Enter event type (0 for PUBLIC, 1 for PRIVATE): ";
    cin >> event_type;
    cout << "Enter event layout (0 for MEETING, 1 for LECTURE, 2 for WEDDING, 3 for DANCE_ROOM): ";
    cin >> event_layout;
    cout << "Enter guest count: ";
    cin >> guests_count;
    cout << "Enter ticket price: ";
    cin >> ticket_price;
    cin.ignore();  // Ignore the newline left in the input buffer

    time_t start_time = parseDateTime(start.c_str(), "%Y-%m-%d %H:%M");
    time_t end_time = parseDateTime(end.c_str(), "%Y-%m-%d %H:%M");

    event new_event(title, id, owner, start_time, end_time, static_cast<EVENT_TYPE>(event_type), static_cast<EVENT_LAYOUT>(event_layout));
    new_event.set_price(ticket_price);

    if (community_center->add_event(new_event)) {
        cout << "Event successfully added!" << endl;
        SaveData(DATA_FILE, community_center, nullptr); 
    } else {
        cout << "Failed to add event. There may be an ID conflict or timing overlap." << endl;
    }
}

int main()
{
    vector<user> users;
    vector<event> events;
    vector<event_user> event_users;
    center community_center;

    LoadData(DATA_FILE, &community_center, &users, &events, &event_users);

    int option;
    user *current_user = NULL;
    bool program_exit = false;
    while (program_exit == false)
    {
        // initial menu for login and sign up
        cout << "Welcome to Community Center Management System!\n"
             << "1. login\n"
             << "2. sign up\n"
             << "3. exit\n";

        cin >> option;
        string username, password, type;
        switch (option)
        {
        case 1:

            cout << "Enter your username and password.\n";
            cout << "         username: ";
            cin >> username;
            cout << "         password: ";
            cin >> password;

            // check if logged in
            check_login(username, password, current_user, &users);
            break;
        case 2:
            cout << "         username: ";
            cin >> username;
            cout << "         password: ";
            cin >> password;
            cout << "         user_type: ";
            cin >> type;

            check_signup(username, password, current_user, &users, community_center, type);
            break;
        case 3:
            program_exit = true;
            break;

        default:
            break;
        }

        string temp;
        while (current_user != NULL)
        {
            cout << "Welcome to Community Center Management System!\n"
                 << "       1. View schedule\n"
                 << "       2. Create Event\n"
                 << "       3. Request a reservation\n"
                 << "       4. Make Payment\n"
                 << "       5. Cancel a reservation\n"
                 << "       6. exit\n";

            cin >> option;

            switch (option)
            {
            case 1:
                community_center.print_schedule();
                break;
            case 2:
                create_event(&community_center);
                break;
            case 3:
                cout << "Enter event id: ";
                cin >> temp;
                community_center.reserve_event(current_user->GetUsername(), temp);
                break;
            case 4:
                cout << "Enter event id: ";
                cin >> temp;
                community_center.make_payment(current_user->GetUsername(), temp);
                break;
            case 5:
                cout << "Enter event id: ";
                cin >> temp;
                community_center.cancel_reservation(current_user->GetUsername(), temp);
                break;
            case 6:
                current_user = NULL;
            default:
                cout << "\t Invalid option!\n";
                break;
            }
        }
    }

    SaveData(DATA_FILE, &community_center, &users);
}