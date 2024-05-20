cmake_minimum_required(VERSION 3.28)
project(YADRO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})



# Устанавливаем директории для вывода бинарных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Для отладочных и релизных конфигураций
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
endforeach()

# Добавьте путь к папке с данными к переменной CMAKE_SOURCE_DIR
set(DATA_DIR "${CMAKE_SOURCE_DIR}/data")

# Передайте путь к папке с данными в качестве определения препроцессора
add_definitions(-DDATA_DIR="${DATA_DIR}")

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
