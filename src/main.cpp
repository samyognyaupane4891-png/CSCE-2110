#include "../include/ReservationManager.h"
#include <iostream>
#include <string>

int main() {
    ReservationManager manager;

    // Load the initial dataset
    manager.loadResources("data/resources.txt");

    int choice;
    do {
        std::cout << "\n===== Campus Resource Reservation System =====\n";
        std::cout << "1. View Resources\n";
        std::cout << "2. Create Reservation\n";
        std::cout << "3. Cancel Reservation\n";
        std::cout << "4. View Waiting Lists\n";
        std::cout << "5. Undo Cancellation\n";
        std::cout << "6. View Active Reservations\n";
        std::cout << "7. View Cancellation History\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter Choice: ";

        // Input validation to prevent infinite loops on bad input
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = 0;
        }

        if (choice == 1) {
            manager.displayResources();
        } else if (choice == 2) {
            int resId, studentId;
            std::string studentName, resourceId, date;

            std::cout << "Reservation ID: "; std::cin >> resId;
            std::cout << "Student ID: "; std::cin >> studentId;
            std::cin.ignore(); // Clear the newline character from the buffer
            std::cout << "Student Name: "; std::getline(std::cin, studentName);
            std::cout << "Resource ID: "; std::cin >> resourceId;
            std::cout << "Date (MM/DD/YYYY): "; std::cin >> date;

            manager.createReservation(resId, studentId, studentName, resourceId, date);
        } else if (choice == 3) {
            int resId;
            std::cout << "Reservation ID to cancel: "; std::cin >> resId;
            manager.cancelReservation(resId);
        } else if (choice == 4) {
            manager.showWaitList();
        } else if (choice == 5) {
            manager.undoCancellation();
        } else if (choice == 6) {
            manager.showActiveReservations();
        } else if (choice == 7) {
            manager.showCancelHistory();
        } else if (choice == 8) {
            std::cout << "Exiting system...\n";
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}