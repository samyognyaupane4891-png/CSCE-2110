// Completed by Samyog Nyaupane

#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <iostream>

// holds the basic info
struct Resource {
    std::string id;
    std::string name;
    std::string type;
    std::string status; // "Available" or "Unavailable"
};
// track the details for active booking
struct Reservation {
    int reservationId;
    int studentId;
    std::string studentName;
    std::string resourceId;
    std::string date;
    std::string startTime;
    std::string endTime;
};
// using it to push student into waitlist queue
struct StudentRequest {
    int studentId;
    std::string studentName;
    std::string resourceId;
};

#endif