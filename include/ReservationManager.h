//
// Created by samyo on 9/10/2026.
//

#ifndef CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H
#define CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H
#include "Models.h"
#include "DataStructures.h"
#include <iostream>

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
};


#endif //CAMPUSRESERVATIONSYSTEM_RESERVATIONMANAGER_H
