set(SOURCES main.cpp timer.cpp session_log.cpp notification.cpp)
set(TEST_SOURCES test_timer.cpp test_session_log.cpp test_notification_manager.cpp test_notification.cpp)

# Include GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})

# Add test sources
add_executable(tests ${TEST_SOURCES})

# Link GoogleTest and pthread
target_link_libraries(tests ${GTest_LIBRARIES} pthread)

# Run tests
add_test(NAME TimerProjectTests COMMAND tests)
