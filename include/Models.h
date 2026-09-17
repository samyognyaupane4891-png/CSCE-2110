#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <iostream>


struct Resource {
    std::string id;
    std::string name;
    std::string type;
    std::string status; // "Available" or "Unavailable"
};

struct Reservation {
    int reservationId;
    int studentId;
    std::string studentName;
    std::string resourceId;
    std::string date;
};
std::string startTime;
std::string endTime;

struct StudentRequest {
    int studentId;
    std::string studentName;
    std::string resourceId;
};

#endif