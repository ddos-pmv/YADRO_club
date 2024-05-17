cmake_minimum_required(VERSION 3.28)
project(YADRO)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
        src/main.cpp
)

set(HEADERS
        src/computer_club.h
        src/computer_club.cpp
)

add_executable(YADRO ${SOURCES} ${HEADERS})
