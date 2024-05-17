cmake_minimum_required(VERSION 3.28)
project(YADRO)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
        src/main.cpp
        src/event.cpp
        src/computer_club.cpp
)

set(HEADERS
        src/computer_club.h
        src/event.h

)

add_executable(YADRO ${SOURCES} ${HEADERS})
