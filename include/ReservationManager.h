/**
 * File: ReservationManager.h
 * Author: Teammate 3
 * Description: System logic for Campus Resource Reservation System
 */

#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Models.h"
#include "DataStructures.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ReservationManager {
private:
    std::vector<Resource> resources;
    ReservationList activeReservations;
    CancellationStack cancelHistory;
    WaitingQueue waitList;

public:
    // Reads resources from the text file
    void loadResources(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error: Could not open " << filename << "\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, name, type, status;
            
            std::getline(ss, id, '|');
            std::getline(ss, name, '|');
            std::getline(ss, type, '|');
            std::getline(ss, status, '|');

            resources.push_back({id, name, type, status});
        }
        file.close();
        std::cout << "Resources loaded successfully.\n";
    }

    void displayResources() {
        std::cout << "\n--- Campus Resources ---\n";
        for (const auto& res : resources) {
            std::cout << res.id << " | " << res.name << " | " << res.type << " | " << res.status << "\n";
        }
    }

    void createReservation(int resId, int studentId, const std::string& studentName, const std::string& resourceId, const std::string& date) {
        Reservation newRes = {resId, studentId, studentName, resourceId, date};
        
        // Pushes the new reservation to the Linked List
        activeReservations.insertReservation(newRes);
        std::cout << "Reservation " << resId << " created successfully for " << studentName << ".\n";
    }

    void cancelReservation(int resId) {
        Reservation removed;
        // If found in the linked list, remove it and push it to the stack
        if (activeReservations.removeReservation(resId, removed)) {
            cancelHistory.push(removed);
            std::cout << "Reservation " << resId << " cancelled. Added to history.\n";
        } else {
            std::cout << "Reservation " << resId << " not found.\n";
        }
    }

    void undoCancellation() {
        Reservation lastCancelled;
        // If the stack isn't empty, pop it and put it back in the linked list
        if (cancelHistory.pop(lastCancelled)) {
            activeReservations.insertReservation(lastCancelled);
            std::cout << "Restored reservation " << lastCancelled.reservationId << ".\n";
        } else {
            std::cout << "No cancellations to undo.\n";
        }
    }

    void showActiveReservations() {
        std::cout << "\n--- Active Reservations ---\n";
        std::cout << "Active reservations feature ready.\n";
    }

    void showWaitList() {
        std::cout << "\n--- Waiting List ---\n";
        std::cout << "Waitlist feature ready.\n";
    }

    void showCancelHistory() {
        std::cout << "\n--- Cancellation History ---\n";
        std::cout << "Cancellation history feature ready.\n";
    }
};

#endif