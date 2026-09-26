#include "Crow/include/crow.h"
#include "parking.h"

int main()
{
    crow::SimpleApp app;

    // Create parking system with 10 slots
    ParkingSystem parkingSystem(10);

    // Main dashboard
    CROW_ROUTE(app, "/")
    ([&parkingSystem]()
    {
        int available = parkingSystem.getAvailableSlots();
        int occupied = parkingSystem.getOccupiedSlots();
        int total = parkingSystem.getTotalSlots();

        std::string html = R"HTML(
<!DOCTYPE html>
<html>
<head>
    <title>ParkEase Kenya</title>

    <style>
        body {
            margin: 0;
            font-family: Arial, sans-serif;
            background: #f4f6f8;
        }

        header {
            background: #111827;
            color: white;
            padding: 20px 40px;
            display: flex;
            justify-content: space-between;
        }

        .container {
            padding: 30px 40px;
        }

        .cards {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 20px;
        }

        .card, .section {
            background: white;
            padding: 25px;
            border-radius: 12px;
            margin-bottom: 25px;
            box-shadow: 0 3px 10px rgba(0,0,0,0.08);
        }

        .number {
            font-size: 35px;
            font-weight: bold;
        }

        input, select {
            padding: 12px;
            width: 250px;
            margin: 5px;
            border: 1px solid #ccc;
            border-radius: 6px;
        }

        button {
            padding: 12px 20px;
            border: none;
            border-radius: 6px;
            background: #2563eb;
            color: white;
            cursor: pointer;
        }

        button:hover {
            background: #1d4ed8;
        }

        .slots {
            display: flex;
            gap: 10px;
            flex-wrap: wrap;
        }

        .slot {
            width: 80px;
            height: 60px;
            display: flex;
            align-items: center;
            justify-content: center;
            border-radius: 8px;
            font-weight: bold;
            background: #bbf7d0;
            color: #166534;
        }

        table {
            width: 100%;
            border-collapse: collapse;
        }

        th, td {
            padding: 12px;
            border-bottom: 1px solid #ddd;
            text-align: left;
        }

        th {
            background: #f3f4f6;
        }
    </style>
</head>

<body>

<header>
    <h1>ParkEase Kenya</h1>
    <span>Smart Parking Management System</span>
</header>

<div class="container">

    <div class="cards">

        <div class="card">
            <h3>Available Slots</h3>
            <div class="number">)HTML";

        html += std::to_string(available);

        html += R"HTML(</div>
        </div>

        <div class="card">
            <h3>Occupied Slots</h3>
            <div class="number">)HTML";

        html += std::to_string(occupied);

        html += R"HTML(</div>
        </div>

        <div class="card">
            <h3>Total Slots</h3>
            <div class="number">)HTML";

        html += std::to_string(total);

        html += R"HTML(</div>
        </div>

    </div>

    <div class="section">
        <h2>Parking Slots</h2>

        <div class="slots">)HTML";

        for (int i = 1; i <= total; i++)
        {
            html += "<div class=\"slot\">Slot " +
                    std::to_string(i) +
                    "</div>";
        }

        html += R"HTML(
        </div>
    </div>

    <div class="section">

        <h2>Vehicle Entry</h2>

        <form action="/park" method="POST">

            <input
                type="text"
                name="registration"
                placeholder="Vehicle Registration"
                required
            >

            <input
                type="text"
                name="type"
                placeholder="Vehicle Type"
                required
            >

            <button type="submit">
                Park Vehicle
            </button>

        </form>

    </div>

    <div class="section">

        <h2>Vehicle Exit</h2>

        <form action="/exit" method="POST">

            <input
                type="text"
                name="registration"
                placeholder="Vehicle Registration"
                required
            >

            <button type="submit">
                Process Exit
            </button>

        </form>

    </div>

</div>

</body>
</html>
        )HTML";

        return html;
    });


    // Vehicle entry
    CROW_ROUTE(app, "/park")
        .methods(crow::HTTPMethod::POST)
    ([&parkingSystem](const crow::request& req)
    {
        auto params = crow::query_string("?" + req.body);

        std::string registration = params.get("registration")
            ? params.get("registration")
            : "";

        std::string vehicleType = params.get("type")
            ? params.get("type")
            : "";

        bool success =
            parkingSystem.parkVehicle(registration, vehicleType);

        if (success)
        {
            return crow::response(
                "<h2>Vehicle Parked Successfully!</h2>"
                "<p>Registration: " + registration + "</p>"
                "<p><a href='/'>Return to Dashboard</a></p>"
            );
        }

        return crow::response(
            "<h2>Unable to Park Vehicle</h2>"
            "<p>The parking lot may be full or the vehicle is already parked.</p>"
            "<p><a href='/'>Return to Dashboard</a></p>"
        );
    });


    // Vehicle exit
    CROW_ROUTE(app, "/exit")
        .methods(crow::HTTPMethod::POST)
    ([&parkingSystem](const crow::request& req)
    {
        auto params = crow::query_string("?" + req.body);

        std::string registration = params.get("registration")
            ? params.get("registration")
            : "";

        int duration =
            parkingSystem.getParkingDuration(registration);

        int fee =
            parkingSystem.getVehicleFee(registration);

        if (duration < 0)
        {
            return crow::response(
                "<h2>Vehicle Not Found</h2>"
                "<p>No active parking record was found.</p>"
                "<p><a href='/'>Return to Dashboard</a></p>"
            );
        }

        std::string result =
            "<h2>Parking Exit</h2>"
            "<p><strong>Registration:</strong> " + registration + "</p>"
            "<p><strong>Parking Duration:</strong> " +
            std::to_string(duration) + " minutes</p>"
            "<p><strong>Amount to Pay:</strong> KSh " +
            std::to_string(fee) + "</p>"
            "<p><strong>Payment:</strong> Successful</p>"
            "<p><strong>Barrier:</strong> OPEN</p>";

        parkingSystem.exitVehicle(registration);

        result +=
            "<p><strong>Parking Slot:</strong> Now Available</p>"
            "<p><a href='/'>Return to Dashboard</a></p>";

        return crow::response(result);
    });


    app.port(18080).multithreaded().run();
}