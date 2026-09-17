#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "Models.h"

// --- Linked List for Active Reservations ---
struct ReservationNode {
    Reservation data;
    ReservationNode* next;
    ReservationNode(Reservation r) : data(r), next(nullptr) {}
};

class ReservationList {
private:
    ReservationNode* head;
public:
    ReservationList() : head(nullptr) {}
    
    void insertReservation(Reservation r) {
        ReservationNode* newNode = new ReservationNode(r);
        newNode->next = head; // Insert at head for O(1) performance
        head = newNode;
    }

    bool removeReservation(int resId, Reservation& removedData) {
        ReservationNode* current = head;
        ReservationNode* prev = nullptr;

        while (current != nullptr) {
            if (current->data.reservationId == resId) {
                removedData = current->data;
                if (prev == nullptr) { head = current->next; } 
                else { prev->next = current->next; }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void displayReservations() const {
        ReservationNode* current = head;
        while (current != nullptr) {
            std::cout << "ID: " << current->data.reservationId 
                      << " | Student: " << current->data.studentName 
                      << " | Resource: " << current->data.resourceId << "\n";
            current = current->next;
        }
    }
};

// --- Stack for Cancellation History ---
struct StackNode {
    Reservation data;
    StackNode* next;
    StackNode(Reservation r) : data(r), next(nullptr) {}
};

class CancellationStack {
private:
    StackNode* top;
public:
    CancellationStack() : top(nullptr) {}

    void push(Reservation r) {
        StackNode* newNode = new StackNode(r);
        newNode->next = top;
        top = newNode;
    }

    bool pop(Reservation& restoredData) {
        if (top == nullptr) return false;
        restoredData = top->data;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    void displayHistory() const {
        StackNode* current = top;
        while (current != nullptr) {
            std::cout << "Cancelled ID: " << current->data.reservationId << "\n";
            current = current->next;
        }
    }
};

// --- Queue for Waiting List ---
struct QueueNode {
    StudentRequest data;
    QueueNode* next;
    QueueNode(StudentRequest s) : data(s), next(nullptr) {}
};

class WaitingQueue {
private:
    QueueNode* front;
    QueueNode* rear;
public:
    WaitingQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(StudentRequest s) {
        QueueNode* newNode = new QueueNode(s);
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    bool dequeue(StudentRequest& s) {
        if (front == nullptr) return false;
        s = front->data;
        QueueNode* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return true;
    }

    void displayWaitingList() const {
        QueueNode* current = front;
        while (current != nullptr) {
            std::cout << "Student ID: " << current->data.studentId 
                      << " waiting for Resource: " << current->data.resourceId << "\n";
            current = current->next;
        }
    }
};
#endif