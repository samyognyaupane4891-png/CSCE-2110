# CSCE 2110 Campus Reservation System

 Team Members: Samyog Nyaupane, Aayush Shrestha, Siddhanta Tripathi
Course: CSCE 2110 (University of North Texas)

## Project Description
The Campus Reservation System is a comprehensive command-line application built in C++ 
to manage university resources. It implements custom Object-Oriented Data Structures 
(Linked Lists, Stacks, and Queues) to handle active bookings, cancellation histories, 
and waiting lists without relying on standard library equivalents for those structures.

For the final integration, the system includes custom-built Merge Sort and 
Binary Search algorithms to organize and locate resources, alongside a dynamic 
Reporting Module to track system utilization.

## Core Features
Resource Management: Load and view resources from a text database.
Reservation System (Linked List): Book resources with collision prevention.
Waitlist (Queue): Automatically queue students when resources are full.
Undo History (Stack): Cancel reservations and undo cancellations safely.
Sorting (Merge Sort): Custom algorithm to sort resources by ID.
Searching (Binary Search): Custom algorithm to locate resources efficiently.
System Reporting: Generates live utilization percentages and waitlist statistics.

## Compilation and Execution (UNT CELL Server)

This project is designed to compile and run on Linux environments, specifically the 
UNT CSE CELL machines.

### 1. Compile the Source Code
Navigate to the root directory of the project in your terminal and compile the program 
using `g++`:

g++ -std=c++11 src/main.cpp -I include -o reservation_system

### 2. Run the Executable
Once compiled successfully, run the generated executable:

./reservation_system

Note: Dear professor/TA, Please ensure the 'data/resources.txt' file remains in its 
relative directory so the 'ReservationManager'` can locate and load the initial dataset.