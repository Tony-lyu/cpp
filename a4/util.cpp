#include "util.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// translate skill level to int, return -1 if input is not valid
int skill_to_int(string skill) {
    if (skill == "Beginner") return 1;
    if (skill == "Intermediate") return 2;
    if (skill == "Advanced") return 3;
    return -1;
}

// handle workwith and notwith attribute
vector<string> split(string s) {
    vector<string> parts;
    string part;
    istringstream inputs(s);
    while(getline(inputs, part, ';')) {
        parts.push_back(part);
    }
    return parts;
}

// reads given csv files into the given vector of students
void read_csv(string filename, vector<Student>* students) {
    ifstream file(filename);
    string line;

    // ignore the header line
    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        vector<string> data;

        while (ss) {
            string s;
            if (!getline(ss, s, ',')) break;
            data.push_back(s);
        }

        Student student;
        student.name = data[0];
        student.cpp = skill_to_int(data[1]);
        student.gdb = skill_to_int(data[2]);
        student.algo = skill_to_int(data[3]);
        student.notwith = split(data[4]);
        student.workwith = split(data[5]);
        students->push_back(student);
        
    }
    file.close();
}
// for debugging
void printStudents(vector<Student> *students) {
    for (auto& student : *students) {
        print(&student);
    }
}

// get all student who has someone they don't want to work with
vector<Student> get_notwork(vector<Student> *students) {
    vector<Student> result;
    for (auto& student : *students) {
        if (!student.notwith.empty()) {
            result.push_back(student);
        }
    }
    return result;
}

// get all student who has someone they want to work with
vector<Student> get_wantwork(vector<Student> *students) {
    vector<Student> result;
    for (auto& student : *students) {
        if (!student.workwith.empty()) {
            result.push_back(student);
        }
    }
    return result;
}

// get all student who has not been placed
vector<Student> get_notplaced(vector<Student> *students) {
    vector<Student> result;
    for (auto& student : *students) {
        if (!student.placed) {
            result.push_back(student);
        }
    }
    return result;
}

// get all teams which has a total score for 'type' of less than 'value'
list<vector<Student>> get_below(list<vector<Student>> *teams, string type, int value) {
    list<vector<Student>> result;
    for (auto& team : *teams) {
        int total = 0;
        for (auto& student : team) {
            if (type == "c") {
                total += student.cpp;
            } else if (type == "gdb") {
                total += student.gdb;
            } else if (type == "algo") {
                total += student.algo;
            }
        }
        if (total < value) {
            result.push_back(team);
        }
    }
    return result;
}

// calculate average total skill in a team
// e.g., a total c++ skill of 30 in a dataset of 15 students, 
// forming  groups of 3, would have a group_sum for c++ skill of
// 30 / (15 / 3) = 6. so each team would have a total c++ skill of 6
int group_sum(vector<Student> *students, int size, string type) {
    int total = 0;
    for(auto& student : *students) {
        if (type == "c") {
            total += student.cpp;
        } else if (type == "gdb") {
            total += student.gdb;
        } else {
            total += student.algo;
        }
        
    }
    return total / (students->size() / size);
}

// group students, considering their preferences and skills
void group(vector<Student> *students, list<vector<Student>> *teams, int size) {
    vector<Student> not_with = get_notwork(students);
    // prioritize not with list first
    for (auto& student : *students) {
        bool placed = false;
        for (auto& team : *teams) {
            for (auto& teammate : team) {
                // check if the current teammate is in the student's not with list
                if (find(student.notwith.begin(), student.notwith.end(), teammate.name) != student.notwith.end()) {
                    break;
                }
            }

            // if the team is not full, add the student to the team
            if (team.size() < size) {
                team.push_back(student);
                student.placed = true;
                placed = true;
                break;
            }
        }
    }
    // then assign teammates for not with who has a want with
    for (auto& team : *teams) { // for each team
        if (team.size() == size) continue; 
        for (auto& dude : team) { // for each member of team
            if (!dude.workwith.empty()) { // if the member has someone they want to work with
                for (auto& buddy : dude.workwith) { // for each person they want to work with
                    for (size_t i = 0; i < students->size(); ++i) { // find the student
                        Student& student = (*students)[i]; 
                        if (student.name == buddy && !student.placed && team.size() < size) { // if they are not placed
                            if (find(student.notwith.begin(), student.notwith.end(), buddy) == student.notwith.end()) {
                                break;
                            }
                            team.push_back(student); // put them in a team
                            student.placed = true; // update placement 
                            break; 
                        }
                    }
                }
            }
        }
    }
    // then assign rest of person who has a want with
    vector<Student> notplaced = get_notplaced(students);
    vector<Student> wantwork = get_wantwork(&notplaced);
    for (auto& student : wantwork) { // for each student who has not been placed
        for (auto& buddy : student.workwith) { // for each person they want to work with
            for (size_t i = 0; i < students->size(); ++i) { // find that person
                Student& dude = (*students)[i]; 
                if (dude.name == buddy && !dude.placed) { // if they are not placed
                    if (find(dude.notwith.begin(), dude.notwith.end(), student.name) == dude.notwith.end()) {
                        bool placed = false;
                        for (auto& team : *teams){
                            if (team.size() + 2 <= size) {
                                team.push_back(student); // put them in a team
                                team.push_back(dude);
                                student.placed = true; // update placement 
                                dude.placed = true;
                                placed = true;
                                break; 
                            }
                        }
                    if (placed) break;
                    }
                }
            }
        }
        if (student.placed) break;
    }
    // now assign rest of students considering balanced skills
    notplaced = get_notplaced(students); // overwrite not placed
    // get score sum for a group
    int team_c, team_gdb, team_algo;
    team_c = group_sum(students, size, "c");
    team_gdb = group_sum(students, size, "gdb");
    team_algo = group_sum(students, size, "algo");
    // place all students in teams first, after this step, all students
    // will have a team assignment, valueing their want with and not with,
    // however, team skill is not balanced yet
    for (auto& team : *teams) { // for each team
        if (team.size() == size) continue; // if the team is not full
        Student s = notplaced.back(); 
        team.push_back(s);
        notplaced.pop_back();
        s.placed = true;
    }
    // algorithm to balance team skills
    // start with c skill
    list<vector<Student>> c_below = get_below(teams, "c", team_c);
    // get all other teams 
    list<vector<Student>> temp;
    for (auto& team : *teams) {
        if (find_if(c_below.begin(), c_below.end(), [&team](const vector<Student>& t) { return &t == &team; }) == c_below.end()) {
            temp.push_back(team);
        }
    }
    for (auto& team : c_below) {
        for (auto team_it = team.begin(); team_it != team.end(); ++team_it) {
            // Find the student with the lowest c skill in the team
            auto lowest_it = min_element(team.begin(), team.end(), [](const Student& a, const Student& b) {
                return a.cpp < b.cpp;
            });

            bool swap_made = false;
            for (auto& team : temp) {
                for (auto high_it = team.begin(); high_it != team.end(); ++high_it) {
                    if (high_it->cpp > lowest_it->cpp) {
                        iter_swap(lowest_it, high_it);
                        swap_made = true;
                        break; 
                    }
                }
                if (swap_made) break; 
            }
            if (!swap_made) break; 
        }
    }

    // proceed with algo
    list<vector<Student>> algo_below = get_below(teams, "algo", team_algo);
    // Get all other teams
    list<vector<Student>> temp_algo;
    for (auto& team : *teams) {
        if (find_if(algo_below.begin(), algo_below.end(), [&team](const vector<Student>& t) { return &t == &team; }) == algo_below.end()) {
            temp_algo.push_back(team);
        }
    }
    for (auto& team : algo_below) {
        for (auto team_it = team.begin(); team_it != team.end(); ++team_it) {
            // Find the student with the lowest c skill in the team
            auto lowest_it = min_element(team.begin(), team.end(), [](const Student& a, const Student& b) {
                return a.cpp < b.cpp;
            });

            bool swap_made = false;
            for (auto& team : temp_algo) {
                for (auto high_it = team.begin(); high_it != team.end(); ++high_it) {
                    if (high_it->cpp > lowest_it->cpp) {
                        iter_swap(lowest_it, high_it);
                        swap_made = true;
                        break; 
                    }
                }
                if (swap_made) break; 
            }
            if (!swap_made) break; 
        }
    }
    // finally, consider debugging
    list<vector<Student>> gdb_below = get_below(teams, "gdb", team_gdb);
    // Get all other teams
    list<vector<Student>> temp_gdb;
    for (auto& team : *teams) {
        if (find_if(gdb_below.begin(), gdb_below.end(), [&team](const vector<Student>& t) { return &t == &team; }) == gdb_below.end()) {
            temp_gdb.push_back(team);
        }
    }
    for (auto& team : gdb_below) {
        for (auto team_it = team.begin(); team_it != team.end(); ++team_it) {
            // Find the student with the lowest c skill in the team
            auto lowest_it = min_element(team.begin(), team.end(), [](const Student& a, const Student& b) {
                return a.cpp < b.cpp;
            });

            bool swap_made = false;
            for (auto& team : temp_gdb) {
                for (auto high_it = team.begin(); high_it != team.end(); ++high_it) {
                    if (high_it->cpp > lowest_it->cpp) {
                        iter_swap(lowest_it, high_it);
                        swap_made = true;
                        break; 
                    }
                }
                if (swap_made) break; 
            }
            if (!swap_made) break; 
        }
    }
}

void print_group(list<vector<Student>> *teams) {
    int team_num = 1; 
    for (const auto& team : *teams) {
        cout << "Team " << team_num << ": ";
        int total_c = 0, total_gdb = 0, total_algo = 0;
        for (const auto& student : team) {
            cout << student.name << " "; // Print each student's name followed by a space
            total_c += student.cpp; // Sum up C++ skills
            total_gdb += student.gdb; // Sum up GDB skills
            total_algo += student.algo; // Sum up algorithm skills
        }
        int total = total_c + total_algo + total_gdb;
        // Print the total skill scores for the team
        cout << "| Team C++: " << total_c << ", Team GDB: " << total_gdb << ", Team Algo: " << total_algo 
        << ", Team Total: " << total << endl;
        ++team_num; // Move to the next team
    }
}

void save_teams(list<vector<Student>> *teams) {
    string filename = "result.csv";
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return;
    }

    int group_num = 1;
    for (const auto& team : *teams) {
        file << "Group " << group_num; 
        for (const auto& student : team) {
            file << "," << student.name;
        }
        file << "\n"; 
        ++group_num; 
    }

    file.close(); 
    cout << "Team saved successful to: " << filename << endl;
}