cmake_minimum_required(VERSION 3.20)
project(CampusReservationSystem)

set(CMAKE_CXX_STANDARD 17)

# Include the headers directory
include_directories(include)

# Compile all source files inside src/
file(GLOB SOURCES "src/*.cpp")

add_executable(CampusReservationSystem ${SOURCES}
        src/main.cpp
        include/Models.h
        include/DataStructures.h
        include/ReservationManager.h)
