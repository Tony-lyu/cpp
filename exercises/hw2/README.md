Project Summary
--------------------------------------------------------------
ADMIN CREDENTIALS:

USRNAME: Spongebob

PASSWORD: Squarepants

This program represents a flight seating system. Each flight has 72 seats in 12 rows. Each row has 6 seats, labeled A to H. there are 2 seats on one side, 3 in the middle and 1 on the other side. A and H are window seats, C and G are not being used, they are considered aisles. 

Users will need to enter their name, employee need to login with creds. 

Main menu for passengers:
1. seating map/ chart showing all seats and indicating if the seats are taken
2. get a seat assgined 
   - enter class of the seat
3. choose a seat manually
   - enter a class first
   - choose a seat manully or get one assigned(in the class chosen)
   - if chooing manully, enter row and seat letter
4. change or cancel seat assignment
   - determine user is changing seat or cancelling seat
   - change has an option of up and downgrade
   - the rest of the functionalities align with that of #3
5. print a boarding pass
6. quit

Main menu for employee
1. seating map
2. print names of all passengers and seat in tabular format
   - enter 1 to 6 for sorting schema
3. load previous seat assignmet manifest
4. save current seat assignment manifest
5. reassign or cancel seat assignment
   - first ask for passenger's name
   - the rest of functionalities is the same as #4 in passenger menu
6. quit


for choosing seat manually, enter F for first class, B for bussiness class, and E for economy class.

Row 1 is first class, rows 2-4 are business class, rows 5-12 are economy class.

Manifests are saved to and loaded from a file called manifest.txt under the same directory of which this program is saved. 
