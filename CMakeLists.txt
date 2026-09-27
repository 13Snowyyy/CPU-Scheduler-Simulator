cmake_minimum_required(VERSION 3.16)
project(CPU_Scheduler_Simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(cpu_scheduler_simulator
    src/main.cpp
    src/FCFS.cpp
    src/SJF.cpp
    src/Priority.cpp
    src/RoundRobin.cpp
    src/Metrics.cpp
    src/GanttChart.cpp
)

enable_testing()

add_executable(test_scheduler
    tests/test_scheduler.cpp
    src/FCFS.cpp
    src/SJF.cpp
    src/Priority.cpp
    src/RoundRobin.cpp
    src/Metrics.cpp
    src/GanttChart.cpp
)

add_test(NAME scheduler_tests COMMAND test_scheduler)
