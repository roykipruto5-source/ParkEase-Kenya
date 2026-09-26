#include <iostream>
#include "parking.h"

using namespace std;

int main() {

    // Create a parking system with 10 parking slots
    ParkingSystem parking(10);

    int choice;

    cout << "====================================\n";
    cout << "       PARKEASE KENYA SYSTEM\n";
    cout << "====================================\n";

    do {

        cout << "\n----------- MAIN MENU --------------\n";
        cout << "1. View Parking Slots\n";
        cout << "2. Park Vehicle\n";
        cout << "3. View Parked Vehicles\n";
        cout << "4. Vehicle Exit\n";
        cout << "5. Exit Program\n";
        
        cout << "------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                parking.displayParkingSlots();
                break;

            case 2: {
                string registrationNumber;
                string vehicleType;

                cout << "\nEnter vehicle registration number: ";
                cin >> registrationNumber;

                cout << "Enter vehicle type (Car/Bike/Van): ";
                cin >> vehicleType;

                parking.parkVehicle(
                    registrationNumber,
                    vehicleType
                );

                break;
            }

            case 3:
                parking.displayParkedVehicles();
                break;

            case 4:
             {
                 string registrationNumber;

                cout << "\nEnter vehicle registration number: ";
                 cin >> registrationNumber;

                  parking.exitVehicle(registrationNumber);

                  break;
            }
   
            case 5:
                  cout << "\nThank you for using ParkEase Kenya!\n";
                  break;

                default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    }  while (choice != 5);

    return 0;
}