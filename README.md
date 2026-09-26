ParkEase Kenya

Web-Based Parking Management System

ParkEase Kenya is a C++-based web parking management system designed to simplify vehicle entry, parking slot allocation, parking duration tracking, fee calculation, and vehicle exit management.
The system provides a web-based dashboard where users can view parking availability, register vehicles, and process vehicle exits.

Project Objectives

* Display available and occupied parking slots.
* Automatically assign available parking slots to vehicles.
* Record vehicle registration numbers and vehicle types.
* Record the vehicle entry time.
* Calculate parking duration automatically.
* Calculate parking fees based on the parking duration.
* Release parking slots when vehicles exit.
* Provide a simple web-based interface for interacting with the parking system.

 Main Features

1. Parking Slot Management

The system manages a parking area containing 10 parking slots.

Each slot can have one of two states:

* Available
* Occupied

The dashboard displays the total number of slots, available slots, and occupied slots.

2. Vehicle Registration

When a vehicle enters the parking area, the system records:

* Vehicle registration number
* Vehicle type
* Assigned parking slot
* Entry time

The system also prevents the same vehicle registration number from being parked twice at the same time.

 3. Automatic Slot Allocation

When a vehicle is registered, the system searches for the first available parking slot and assigns it to the vehicle.

If all slots are occupied, the system reports that the parking lot is full.

4. Parking Duration

The system records the vehicle's entry time using the C++ time functions.

When the vehicle exits, the system calculates the parking duration automatically based on the current time.

### 5. Parking Fee Calculation

The parking charges used by ParkEase Kenya are:

| Parking Duration |     Fee |
| ---------------- | ------: |
| Up to 30 minutes |   KSh 0 |
| Up to 2 hours    |  KSh 50 |
| Up to 4 hours    | KSh 100 |
| Up to 6 hours    | KSh 300 |
| Over 6 hours     | KSh 500 |

6. Vehicle Exit

When a vehicle exits, the system:

1. Searches for the vehicle registration number.
2. Calculates the parking duration.
3. Calculates the parking fee.
4. Processes the simulated payment.
5. Opens the simulated parking barrier.
6. Releases the assigned parking slot.
7. Makes the slot available for another vehicle. 
System Modules

Parking Slot Module

Responsible for:

* Creating parking slots.
* Tracking slot availability.
* Counting available and occupied slots.

Vehicle Management Module

Responsible for:

* Registering vehicles.
* Assigning parking slots.
* Preventing duplicate parked vehicles.
* Finding vehicles during exit.

Fee Calculation Module

Responsible for calculating the parking fee according to the defined parking duration rules.

Web Interface Module

Provides the browser-based interface for:

* Viewing parking availability.
* Registering vehicles.
* Processing vehicle exits.
* Viewing parking information.

Data Structures

Vector

The system uses C++ `vector` containers to store parking slots and currently parked vehicles.

**Why vector was used:**

* It dynamically manages the number of elements.
* It provides easy insertion and removal.
* It allows the system to loop through parking slots and vehicles efficiently.
* It is part of the standard C++ library.

 Structures

Two structures are used:
 ParkingSlot

Stores:

* Slot number
* Occupied status

Vehicle

Stores:

* Registration number
* Vehicle type
* Assigned slot number
* Entry time

Structures group related information together and make the system easier to manage.

 Algorithms

Slot Allocation Algorithm

1. Start when a vehicle requests parking.
2. Check whether the registration number is already parked.
3. Search the parking slots from the first slot.
4. Find the first available slot.
5. Mark the slot as occupied.
6. Store the vehicle information.
7. Record the entry time.
8. Return the assigned slot.

Fee Calculation Algorithm

1. Calculate the parking duration in minutes.
2. Compare the duration against the defined fee ranges.
3. Assign the corresponding parking fee.
4. Return the calculated fee.

Vehicle Exit Algorithm

1. Receive the vehicle registration number.
2. Search the list of parked vehicles.
3. Retrieve the assigned slot.
4. Calculate parking duration.
5. Calculate the parking fee.
6. Process the simulated payment.
7. Mark the parking slot as available.
8. Remove the vehicle from the active parking list.
9. Open the simulated barrier.

Technologies Used

* **C++** — Core system logic
* **Crow C++ Framework** — Web server and HTTP handling
* **HTML** — Web interface
* **Git** — Version control
* **GitHub** — Source code repository
* **Visual Studio Code** — Development environment
* **MSYS2 UCRT64** — C++ compilation environment

Project Structure

```text
ParkEase-Kenya/
│
├── main.cpp
├── parking.cpp
├── parking.h
├── web.cpp
├── README.md
└── .gitignore
```

File Descriptions

**main.cpp**
Contains the console-based entry point for testing the parking system.

**parking.h**
Contains the declarations of the parking system, parking slots, and vehicle structures.

**parking.cpp**
Contains the implementation of parking management, vehicle registration, fee calculation, duration calculation, and vehicle exit functionality.

**web.cpp**
Contains the Crow-based web server and browser interface.

**README.md**
Contains project documentation.

**.gitignore**
Prevents unnecessary files such as compiled executables and local dependencies from being uploaded to GitHub.

Requirements

To build and run the project, you need:

* Windows
* C++ compiler supporting modern C++
* MSYS2 UCRT64
* Visual Studio Code
* Crow C++ framework
* Git

Running the Web Application

Open the MSYS2 UCRT64 terminal and navigate to the project directory:

```bash
cd "C:\Users\Royhm\Desktop\ParkEase Kenya"
```

Compile the web application:

```bash
g++ web.cpp parking.cpp -o ParkEaseWeb -pthread -I"Crow/include" -lws2_32 -lmswsock
```

Run the application:

```bash
./ParkEaseWeb
```

Open a web browser and visit:

```text
http://localhost:18080
```

## System Workflow

```text
Vehicle Arrives
       ↓
Enter Registration & Vehicle Type
       ↓
Check Available Slots
       ↓
Assign Parking Slot
       ↓
Record Entry Time
       ↓
Vehicle Parks
       ↓
Vehicle Requests Exit
       ↓
Calculate Parking Duration
       ↓
Calculate Parking Fee
       ↓
Simulated Payment
       ↓
Barrier Opens
       ↓
Release Parking Slot
       ↓
Slot Becomes Available
```

Current Scope

The current version is a functional prototype demonstrating the main parking management processes.

Payment is simulated rather than connected to a real payment provider. The system currently stores active parking information in memory while the application is running.

Future Improvements

Possible future versions could include:

* Integration with M-Pesa or other payment services.
* A permanent database such as MySQL or PostgreSQL.
* User authentication and administrator accounts.
* Parking history and transaction reports.
* Automatic number plate recognition.
* Multiple parking locations.
* Different parking rates for different vehicle types.
* Real electronic barrier integration.
* Improved responsive mobile interface.

 Author
Roy Kipruto
Software Engineering Student
Multimedia University of Kenya

Project Status

Functional Prototype — Completed

The core parking management and web functionality has been implemented and tested.
