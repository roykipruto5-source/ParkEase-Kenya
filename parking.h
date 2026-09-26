#ifndef PARKING_H
#define PARKING_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Represents a parking slot
struct ParkingSlot
{
    int slotNumber;
    bool occupied;
};

// Represents a vehicle
struct Vehicle
{
    string registrationNumber;
    string vehicleType;
    int slotNumber;
    time_t entryTime;
};

// Parking system class
class ParkingSystem
{
private:
    vector<ParkingSlot> parkingSlots;
    vector<Vehicle> parkedVehicles;

public:
    // Constructor
    ParkingSystem(int numberOfSlots);

    // Display available and occupied slots
    void displayParkingSlots();

    // Register a vehicle and assign a slot
    bool parkVehicle(string registrationNumber, string vehicleType);

    // Display vehicles currently parked
    void displayParkedVehicles();

    // Calculate parking fee
    int calculateFee(int minutes);

    // Remove a vehicle when it exits
    bool exitVehicle(string registrationNumber);

    // Web-system functions
    int getAvailableSlots();
    int getOccupiedSlots();
    int getTotalSlots();

    // Get the assigned slot for a vehicle
    int getVehicleSlot(string registrationNumber);

    // Calculate how long a vehicle has been parked
    int getParkingDuration(string registrationNumber);

    // Get parking fee for a vehicle
    int getVehicleFee(string registrationNumber);
};

#endif