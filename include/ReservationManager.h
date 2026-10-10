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
    // Helper function for Merge Sort
    void merge(std::vector<Resource>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<Resource> L(n1), R(n2);

        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            // Using your struct's 'id' variable
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

    // Main Merge Sort function
    void mergeSortResources(std::vector<Resource>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortResources(arr, left, mid);
            mergeSortResources(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    // The function you will call from your main.cpp menu
    void sortResources() {
        if (!resources.empty()) {
            mergeSortResources(resources, 0, resources.size() - 1);
            std::cout << "Resources successfully sorted by ID.\n";
        }
    }

    // Binary Search for Resource by ID (Requires list to be sorted first!)
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


};
#endif //CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H
