#include <iostream>
#include <limits>
using namespace std;

int global = 100;
int main() {
    int li = 10;
    //printing & loops
    li >= 10 ? cout<<"Bigger"<<endl : cout<<"Smaller"<<endl;
    for (int i = 10; i >= 0; i-=2) {
        cout<<i <<"\n";
    }
    for(int i = 10;i>=0; i--){
        cout<<i<<"\n";
    }
    //setting time seed to current time
    srand(time(nullptr));
    
    //generate random number
    for (int i = 0; i < 10; i++){
        for (int j = 5; j >0; j--) {
            cout<<rand()%10<<" ";
            cout<<endl;
        }
    }

    //case switch
    char cc;
    cin>>cc;
    switch(cc) {
        case 'a' : break;
        case 'b' : cout<< "you lost."<<endl; break;
        default : cout<<"letter is: "<< cc<<endl; break;  
    }

    //reference address
    int i = 100;
    int &j = i;
    cout<<"address:"<<&i<<", Value: "<<i<<endl;
    cout<<"address:"<<&j<<", Value: "<<j<<endl;
    j = 10;
    cout<<"address:"<<&i<<", Value: "<<i<<endl;
    cout<<"address:"<<&j<<", Value: "<<j<<endl;

    //to create a instance of struct student 
    Student s;
    s.id = 1;
    s.std_name = "John";
    s.print();
}

//define a struct 
//members of a struct is in default public 
struct Student {
  int id;
  string std_name;
  //struct can have functions within
  void print() {cout<<std_name<<" has id: "<<id<<endl; }
};

// numeric value comparasons: promote to looser bound

struct Flight {
    int seats[6][12];
    string names[6][12];
    
    //prints the seat assignment
    void print_seat();
    // prints boarding pass of a dude
    void print_boarding(string name);
    // assign a person a seat automatically
    void assign(string name, int row, int seat);
    // get a user input from user to manually assign seats
    void assign(string name);
};

struct Assignment {
    Flight f;
    
};

void print_seat() {
    for(auto& row: seats) {
        for (auto seat: row) {
            //prints seats
        }
    }
}

