#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

void createBus()
{
    ofstream busData("Bus_Data.csv", ios::app);
    
    int lastID = 0; // Variable to store the last used ID

    // Find the last ID in the file
    string line;
    ifstream readFile("Bus_Data.csv");
    if (readFile.is_open()) {
        while (getline(readFile, line)) {
            stringstream ss(line);
            string idStr;
            getline(ss, idStr, ',');
            int id = stoi(idStr);
            if (id > lastID) {
                lastID = id;
            }
        }
        readFile.close();
    }

    int n_booking;
    cout << "\n\tInput the number of buses: ";
    cin >> n_booking;

    for (int i = 0; i < n_booking; i++) {
        int ID = lastID + 1; // Increment the ID
        lastID++;

        string driver_name, arrive, departure, from, to;
        cout << "\n\t\tBus Number: " << ID << endl;

        cout << "\t\tEnter Driver's name: ";
        cin >> driver_name;
        cout << "\t\tEnter Arrival time: ";
        cin >> arrive;
        cout << "\t\tEnter Departure: ";
        cin >> departure;
        cout << "\t\tFrom: ";
        cin >> from;
        cout << "\t\tTo: ";
        cin >> to;

        busData << ID << ','
                << driver_name << ','
                << arrive << ','
                << departure << ','
                << from << ','
                << to << endl;
    }

    busData.close();
    cout << "\n\t\tBus added successfully!" << endl;
}

void addBus()
{
    ofstream busData("Bus_Data.csv", ios::app);
    
    int lastID = 0; // Variable to store the last used ID

    // Find the last ID in the file
    string line;
    ifstream readFile("Bus_Data.csv");
    if (readFile.is_open()) {
        while (getline(readFile, line)) {
            stringstream ss(line);
            string idStr;
            getline(ss, idStr, ',');
            int id = stoi(idStr);
            if (id > lastID) {
                lastID = id;
            }
        }
        readFile.close();
    }

    int n_booking;
    cout << "\n\tEnter the number of buses you want to add: ";
    cin >> n_booking;

    for (int i = 0; i < n_booking; i++) {
        int ID = lastID + 1; // Increment the ID
        lastID++;

        string driver_name, arrive, departure, from, to;
        cout << "\n\tAdd Bus Number: " << ID << endl;

        cout << "\tEnter Driver's name: ";
        cin >> driver_name;
        cout << "\tEnter Arrival time: ";
        cin >> arrive;
        cout << "\tEnter Departure: ";
        cin >> departure;
        cout << "\tFrom: ";
        cin >> from;
        cout << "\tTo: ";
        cin >> to;

        busData << ID << ','
                << driver_name << ','
                << arrive << ','
                << departure << ','
                << from << ','
                << to << endl;
    }

    busData.close();
    cout << "\n\tBuses added successfully!" << endl;
}

void makeReservation()
{
    ofstream reservationData("Reservation_Data.csv", ios::app);
    
    int lastID = 0; // Variable to store the last used ID

    // Find the last ID in the file
    string line;
   ifstream readFile("Reservation_Data.csv");
    if (readFile.is_open()) {
        while (getline(readFile, line)) {
            stringstream ss(line);
            string idStr;
            getline(ss, idStr, ',');
            int id = stoi(idStr);
            if (id > lastID) {
                lastID = id;
            }
        }
        readFile.close();
    }

    int bus_number, seat_number, phone_number; 
    string name;
    cout << "\nEnter Bus Number: ";
    cin >> bus_number;
    cout << "Enter Seat Number: ";
    cin >> seat_number;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Phone Number: ";
    cin >> phone_number;

    ifstream busData("Bus_Data.csv");

    vector<string> row;
    string line2, word;
    int roll2 = 0;

    bool busFound = false;
    
    while (getline(busData, line2)) {
        row.clear();

        stringstream s(line2);
        
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        
        roll2 = stoi(row[0]);
        
        if (roll2 == bus_number) {
            busFound = true;
            
            ifstream reservationData("Reservation_Data.csv");
            bool seatAvailable = true;

            while (getline(reservationData, line)) {
                stringstream ss(line);
                string seatStr;
                getline(ss, seatStr, ',');
                int seatNumber = stoi(seatStr);

                if (seatNumber == seat_number) {
                    seatAvailable = false;
                    break;
                }
            }
            
            reservationData.close();
            
            if (seatAvailable) {
                reservationData.open("Reservation_Data.csv", ios::app);
                int ID = lastID + 1; // Increment the ID
                lastID++;
                
                reservationData << seat_number << ','
                                << row[1] << ','
                                << row[2] << ','
                                << row[3] << ','
                                << row[4] << ','
                                << row[5] << ','
                                << name << ','
                                << phone_number << endl;
                
                reservationData.close();
                cout << "\nSeat has been successfully reserved!" << endl;
            } else {
                cout << "\nSeat is already reserved!" << endl;
            }
            
            break;
        }
    }
    
    busData.close();
    
    if (!busFound) {
        cout << "\nBus not found!" << endl;
    }
}

void displayAvailableSeats()
{
    ifstream busData("Bus_Data.csv");
    ifstream reservationData("Reservation_Data.csv");

    vector<int> reservedSeats;
    string line;

    while (getline(reservationData, line)) {
        stringstream ss(line);
        string seatStr;
        getline(ss, seatStr, ',');
        int seatNumber = stoi(seatStr);
        reservedSeats.push_back(seatNumber);
    }

    cout << "\n\tAvailable Seats:\n";

    while (getline(busData, line)) {
        stringstream ss(line);
        string seatStr;
        getline(ss, seatStr, ',');
        int seatNumber = stoi(seatStr);

        bool seatAvailable = true;
        for (int reservedSeat : reservedSeats) {
            if (seatNumber == reservedSeat) {
                seatAvailable = false;
                break;
            }
        }

        if (seatAvailable) {
            cout << "\tSeat Number: " << seatNumber << endl;
        }
    }

    busData.close();
    reservationData.close();
}

void cancelReservation()
{
    int seat_number;
    cout << "\nEnter the Seat Number to cancel the reservation: ";
    cin >> seat_number;

    ifstream reservationData("Reservation_Data.csv");
    string line;
    vector<string> reservationLines;

    while (getline(reservationData, line)) {
        stringstream ss(line);
        string seatStr;
        getline(ss, seatStr, ',');
        int seatNumber = stoi(seatStr);

        if (seatNumber != seat_number) {
            reservationLines.push_back(line);
        }
    }

    reservationData.close();

    ofstream rewriteData("Reservation_Data.csv");
    for (const string& reservationLine : reservationLines) {
        rewriteData << reservationLine << endl;
    }

    rewriteData.close();
    cout << "\nReservation successfully canceled!" << endl;
}

void listAllReservations()
{
    ifstream reservationData("Reservation_Data.csv");
    string line;

    cout << "\n\tAll Reservations:\n";
    while (getline(reservationData, line)) {
        stringstream ss(line);
        string data;
        while (getline(ss, data, ',')) {
            cout << data << "\t";
        }
        cout << endl;
    }

    reservationData.close();
}

int main()
{
    int choice;
    while (true) {
        cout << "\n\t*** BUS RESERVATION SYSTEM ***\n";
        cout << "\n\t1. Create Bus\n";
        cout << "\t2. Add Bus\n";
        cout << "\t3. Display Available Seats\n";
        cout << "\t4. Make Reservation\n";
        cout << "\t5. Cancel Reservation\n";
        cout << "\t6. List All Reservations\n";
        cout << "\t7. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createBus();
                break;
            case 2:
                addBus();
                break;
            case 3:
                displayAvailableSeats();
                break;
            case 4:
                makeReservation();
                break;
            case 5:
                cancelReservation();
                break;
            case 6:
                listAllReservations();
                break;
            case 7:
                exit(0);
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    }

    return 0;
}