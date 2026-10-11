// Completed by Aayush Shrestha
// Proof read by Samyog Nyaupane (Leader)

#ifndef CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H
#define CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H

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

    void createReservation(int resId, int studentId, const std::string& studentName, const std::string& resourceId, const std::string& date, const std::string& startTime, const std::string& endTime) {
        // 1. Check if the resource actually exists
        bool resourceExists = false;
        Resource* targetRes = nullptr;
        for (auto& res : resources) {
            if (res.id == resourceId) {
                resourceExists = true;
                targetRes = &res;
                break;
            }
        }

        if (!resourceExists) {
            std::cout << "Error: Resource " << resourceId << " does not exist.\n";
            return;
        }

        // 2. Check if resource is available. If not, trigger waitlist.
        if (targetRes->status == "Booked" || targetRes->status == "Unavailable") {
            std::cout << "Resource is currently booked. Add to waiting list? (Y/N): ";
            char choice;
            std::cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                Reservation waitRes = {resId, studentId, studentName, resourceId, date, startTime, endTime};
                waitList.enqueue(waitRes); // Pass the reservation object instead of separate parts
                std::cout << "Successfully added to the waiting list.\n";
            }
            return;
        }

        // 3. If safe, create the reservation and mark the resource as Booked
        Reservation newRes = {resId, studentId, studentName, resourceId, date, startTime, endTime};
        activeReservations.insertReservation(newRes);
        targetRes->status = "Booked"; 
        
        std::cout << "Reservation " << resId << " created successfully for " << studentName << ".\n";
    }

    void cancelReservation(int resId) {
        Reservation removed;
        if (activeReservations.removeReservation(resId, removed)) {
            cancelHistory.push(removed);
            std::cout << "Reservation " << resId << " cancelled. Added to history.\n";
        } else {
            std::cout << "Reservation " << resId << " not found.\n";
        }
    }

    void undoCancellation() {
        Reservation lastCancelled;
        
        if (cancelHistory.pop(lastCancelled)) {
            bool canRestore = true;
            for (auto& res : resources) {
                if (res.id == lastCancelled.resourceId) {
                    if (res.status == "Booked" || res.status == "Unavailable") {
                        canRestore = false;
                    } else {
                        res.status = "Booked"; 
                    }
                    break;
                }
            }

            if (!canRestore) {
                std::cout << "Error: Cannot undo. Resource " << lastCancelled.resourceId << " was booked by someone else.\n";
                cancelHistory.push(lastCancelled); 
            } else {
                activeReservations.insertReservation(lastCancelled);
                std::cout << "Restored reservation " << lastCancelled.reservationId << ".\n";
            }
        } else {
            std::cout << "No cancellations to undo.\n";
        }
    }

    void showActiveReservations() {
        std::cout << "\n--- Active Reservations ---\n";
        activeReservations.displayReservations();
    }

    void showWaitList() {
        std::cout << "\n--- Waiting List ---\n";
        waitList.displayWaitingList();
    }

    void showCancelHistory() {
        std::cout << "\n--- Cancellation History ---\n";
        cancelHistory.displayHistory();
    }

    // --- SORTING (Merge Sort) ---
    void merge(std::vector<Resource>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<Resource> L(n1), R(n2);

        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i].id <= R[j].id) { 
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) { arr[k] = L[i]; i++; k++; }
        while (j < n2) { arr[k] = R[j]; j++; k++; }
    }

    void mergeSortResources(std::vector<Resource>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortResources(arr, left, mid);
            mergeSortResources(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    void sortResources() {
        if (!resources.empty()) {
            mergeSortResources(resources, 0, resources.size() - 1);
            std::cout << "Resources successfully sorted by ID.\n";
        }
    }

    // --- SEARCHING (Binary Search) ---
    void searchResource(std::string targetId) {
        int left = 0;
        int right = resources.size() - 1;
        bool found = false;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (resources[mid].id == targetId) {
                std::cout << "\nResource Found: " << resources[mid].name 
                          << " | Status: " << resources[mid].status << "\n";
                found = true;
                break;
            }
            if (resources[mid].id < targetId) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        if (!found) {
            std::cout << "\nResource " << targetId << " not found.\n";
        }
    }

    // --- REPORTING MODULE ---
    void generateSystemReport() {
        std::cout << "\n===== CAMPUS RESOURCE SYSTEM REPORT =====\n";
        
        int totalResources = resources.size();
        int bookedResources = 0;
        
        std::cout << "--- Resource Utilization ---\n";
        for (const auto& res : resources) {
            if (res.status == "Booked" || res.status == "Unavailable") {
                bookedResources++;
                std::cout << res.id << " (" << res.name << "): 1 Active Booking\n";
            } else {
                std::cout << res.id << " (" << res.name << "): 0 Active Bookings\n";
            }
        }
        
        if (totalResources > 0) {
            double utilization = (static_cast<double>(bookedResources) / totalResources) * 100;
            std::cout << "\nTotal System Utilization: " << utilization << "%\n";
        }

        std::cout << "\n--- Waiting-List Statistics ---\n";
        bool anyoneWaiting = false;
        
        for (const auto& res : resources) {
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

#endif // CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H