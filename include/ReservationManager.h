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

class ReservationManager {
public:
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
    // Final project requirement: Generate system reports
    void generateSystemReport() {
        std::cout << "\n===== CAMPUS RESOURCE SYSTEM REPORT =====\n";

        int totalResources = resources.size();
        int bookedResources = 0;

        // 1. Resource Utilization
        std::cout << "--- Resource Utilization ---\n";
        for (const auto& res : resources) {
            // Using the helper function to count reservations dynamically
            int activeCount = activeReservations.countActiveForResource(res.id);

            std::cout << res.id << " (" << res.name << "): "
                      << activeCount << " Active Booking(s)\n";

            // Track total utilization if the resource is marked as booked
            if (res.status == "Booked" || res.status == "Unavailable") {
                bookedResources++;
            }
        }

        if (totalResources > 0) {
            double utilization = (static_cast<double>(bookedResources) / totalResources) * 100;
            std::cout << "\nTotal System Utilization: " << utilization << "%\n";
        }

        // 2. Waiting-List Statistics
        std::cout << "\n--- Waiting-List Statistics ---\n";
        bool anyoneWaiting = false;

        for (const auto& res : resources) {
            // Pulls waitlist numbers dynamically from the queue
            int waitCount = waitList.countWaitingForResource(res.id);
            if (waitCount > 0) {
                std::cout << res.id << " (" << res.name << "): " << waitCount << " student(s) waiting.\n";
                anyoneWaiting = true;
            }
        }

        if (!anyoneWaiting) {
            std::cout << "No students are currently on the waiting list.\n";
        }

        std::cout << "=========================================\n";
    }

};
#endif //CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H
