//
// Created by samyo on 9/10/2026.
//

#ifndef CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H
#define CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H
#include "Models.h"
#include "DataStructures.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
feature/project-skeleton

class ReservationManager {
public:

    ReservationList activeReservations;
    CancellationStack cancelHistory;
    WaitingQueue waitList;

    void cancelReservation(int resId) {
        Reservation removed;
        // Trying to remove from active resrvation frst... :)
        if (activeReservations.removeReservation(resId, removed)) {
            cancelHistory.push(removed);
            std::cout << "Reservation " << resId << " cancelled. Added to history.\n";
        } else {
            std::cout << "Reservation " << resId << " not found.\n";
        }
    }

    void undoCancellation() {
        Reservation lastCancelled;
        // Pop the most recently cancled resrvation
        if (cancelHistory.pop(lastCancelled)) {
            activeReservations.insertReservation(lastCancelled);
            std::cout << "Restored reservation " << lastCancelled.reservationId << ".\n";
        } else {
            std::cout << "No cancellations to undo.\n";
        }
    }

    void showWaitList() {
        std::cout << "\n--- Waiting List ---\n";
        waitList.displayWaitingList();
    }

    void showCancelHistory() {
        std::cout << "\n--- Cancellation History ---\n";
        cancelHistory.displayHistory();
    }






    std::vector<Resource> resources;

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
};
#endif //CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H
