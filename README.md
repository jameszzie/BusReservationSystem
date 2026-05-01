Bus Reservation System in C

Project Overview
It allows users to check schedules, book or cancel seats and view bus status boards in C.
The Bus Reservation System is a terminal-based application designed to digitize the management of bus ticketing. It provides a centralized platform where administrators and users can efficiently manage travel data.

Key Features:
- Check Schedules:** Real-time display of routes and ticket prices.
- Booking Queue:** A systematic way to add booking requests for batch processing.
- Cancellation System:** Allows users to release booked seats instantly.
- Visual Status Board:** A graphical console grid displaying occupied [X] vs. vacant [ ] seats.

Data Structures & Algorithms (DSA)
This project serves as a practical implementation of fundamental computer science concepts:

1. Arrays & Structures
Data Storage: Uses a `Bus` struct array to manage persistent data for the fleet (ID, route, and seat mapping).
Visual Board: Uses a 1D array mapped logically to represent a 20-seat layout per bus.

2. Linear Queue
Feature Supported: Booking System.
Logic: Implements FIFO (First-In-First-Out). Booking requests are held in a buffer (`enqueue`) and processed in the order they were received using `processQueue()`.

3. Stack
Feature Supported: Transaction History.
Logic: Implements LIFO (Last-In-First-Out) logic. Every finalized booking or cancellation is "pushed" onto a history stack to maintain a chronological log of user activity.

4. Linear Search
Feature Supported: Data Validation.
Logic: Utilized in `cancelSeat()` and `processQueue()` to iterate through the bus array and locate specific Bus IDs provided by user input.

5. Bubble Sort
Feature Supported: Fare Optimization.
Logic: The system uses Bubble Sort in `sortBusesByFare()` to organize the bus list from the most affordable to the most expensive before displaying the schedule.


How to Compile and Run

1. Prerequisites
Ensure a C compiler (e.g., GCC, Clang, or MinGW) is installed on your system.

2. Compilation
Open your terminal or command prompt and run:
```bash
gcc main.c -o bus_system
