cmake_minimum_required(VERSION 3.10)
project(PomodoroTimer)

set(CMAKE_CXX_STANDARD 17)

# Add Crow library
include_directories(/path/to/crow/include)

# Add source files
add_executable(PomodoroTimer
    main.cpp
    timer.cpp
    session_log.cpp
    utils.cpp
)

# Link libraries
target_link_libraries(PomodoroTimer pthread)
