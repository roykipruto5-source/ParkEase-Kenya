#include "parking.h"

// Constructor
ParkingSystem::ParkingSystem(int numberOfSlots)
{
    for (int i = 1; i <= numberOfSlots; i++)
    {
        ParkingSlot slot;
        slot.slotNumber = i;
        slot.occupied = false;

        parkingSlots.push_back(slot);
    }
}

// Display parking slots
void ParkingSystem::displayParkingSlots()
{
    cout << "\n========== PARKEASE KENYA ==========\n";
    cout << "        PARKING SLOT DISPLAY\n";
    cout << "====================================\n";

    for (const ParkingSlot& slot : parkingSlots)
    {
        cout << "Slot " << slot.slotNumber << " : ";

        if (slot.occupied)
            cout << "OCCUPIED";
        else
            cout << "AVAILABLE";

        cout << endl;
    }

    cout << "====================================\n";
}

// Park a vehicle
bool ParkingSystem::parkVehicle(string registrationNumber,
                                string vehicleType)
{
    // Prevent duplicate vehicle registration
    for (const Vehicle& vehicle : parkedVehicles)
    {
        if (vehicle.registrationNumber == registrationNumber)
        {
            cout << "\nVehicle is already parked.\n";
            return false;
        }
    }

    // Find an available slot
    for (ParkingSlot& slot : parkingSlots)
    {
        if (!slot.occupied)
        {
            slot.occupied = true;

            Vehicle vehicle;
            vehicle.registrationNumber = registrationNumber;
            vehicle.vehicleType = vehicleType;
            vehicle.slotNumber = slot.slotNumber;

            // Record current entry time
            vehicle.entryTime = time(nullptr);

            parkedVehicles.push_back(vehicle);

            cout << "\nVehicle successfully parked!\n";
            cout << "Registration: " << registrationNumber << endl;
            cout << "Vehicle Type: " << vehicleType << endl;
            cout << "Assigned Slot: " << slot.slotNumber << endl;

            return true;
        }
    }

    cout << "\nSorry, the parking lot is FULL.\n";

    return false;
}

// Display parked vehicles
void ParkingSystem::displayParkedVehicles()
{
    cout << "\n========== PARKED VEHICLES ==========\n";

    if (parkedVehicles.empty())
    {
        cout << "No vehicles currently parked.\n";
        return;
    }

    for (const Vehicle& vehicle : parkedVehicles)
    {
        cout << "Registration: "
             << vehicle.registrationNumber << endl;

        cout << "Vehicle Type: "
             << vehicle.vehicleType << endl;

        cout << "Parking Slot: "
             << vehicle.slotNumber << endl;

        cout << "------------------------------------\n";
    }
}

// Calculate parking fee
int ParkingSystem::calculateFee(int minutes)
{
    if (minutes <= 30)
        return 0;
    else if (minutes <= 120)
        return 50;
    else if (minutes <= 240)
        return 100;
    else if (minutes <= 360)
        return 300;
    else
        return 500;
}

// Get total number of slots
int ParkingSystem::getTotalSlots()
{
    return parkingSlots.size();
}

// Get number of available slots
int ParkingSystem::getAvailableSlots()
{
    int available = 0;

    for (const ParkingSlot& slot : parkingSlots)
    {
        if (!slot.occupied)
            available++;
    }

    return available;
}

// Get number of occupied slots
int ParkingSystem::getOccupiedSlots()
{
    return getTotalSlots() - getAvailableSlots();
}

// Get vehicle slot
int ParkingSystem::getVehicleSlot(string registrationNumber)
{
    for (const Vehicle& vehicle : parkedVehicles)
    {
        if (vehicle.registrationNumber == registrationNumber)
        {
            return vehicle.slotNumber;
        }
    }

    return -1;
}

// Get parking duration
int ParkingSystem::getParkingDuration(string registrationNumber)
{
    for (const Vehicle& vehicle : parkedVehicles)
    {
        if (vehicle.registrationNumber == registrationNumber)
        {
            time_t currentTime = time(nullptr);

            double seconds = difftime(currentTime, vehicle.entryTime);

            int minutes = static_cast<int>(seconds / 60);

            return minutes;
        }
    }

    return -1;
}

// Get current vehicle fee
int ParkingSystem::getVehicleFee(string registrationNumber)
{
    int minutes = getParkingDuration(registrationNumber);

    if (minutes < 0)
        return -1;

    return calculateFee(minutes);
}

// Vehicle exit
bool ParkingSystem::exitVehicle(string registrationNumber)
{
    for (int i = 0; i < parkedVehicles.size(); i++)
    {
        if (parkedVehicles[i].registrationNumber == registrationNumber)
        {
            int slotNumber = parkedVehicles[i].slotNumber;

            // Automatically calculate parking duration
            int minutes = getParkingDuration(registrationNumber);

            int fee = calculateFee(minutes);

            cout << "\n========== PARKING EXIT ==========\n";
            cout << "Registration: " << registrationNumber << endl;
            cout << "Parking Duration: " << minutes << " minutes" << endl;
            cout << "Amount to Pay: KSh " << fee << endl;
            cout << "==================================\n";

            // Release parking slot
            for (ParkingSlot& slot : parkingSlots)
            {
                if (slot.slotNumber == slotNumber)
                {
                    slot.occupied = false;
                    break;
                }
            }

            // Remove vehicle
            parkedVehicles.erase(parkedVehicles.begin() + i);

            cout << "\nPayment successful!\n";
            cout << "Barrier: OPEN\n";
            cout << "Slot " << slotNumber << " is now AVAILABLE.\n";

            return true;
        }
    }

    cout << "\nVehicle not found in the parking system.\n";

    return false;
}