cmake_minimum_required(VERSION 3.10)

project(RockPaperScissors LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source and header directories
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/tst)

# Include header directory
include_directories(${INCLUDE_DIR})

# Find GoogleTest and Threads
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# ---- Game Executable (NO TESTS!) ----
add_executable(game
    # Main application
    ${SOURCE_DIR}/main.cpp

    # Core game logic
    ${SOURCE_DIR}/SinglePlayerRpsGame.cpp
    ${SOURCE_DIR}/GameSessionFactory.cpp

    # Players
    ${SOURCE_DIR}/UserPlayer.cpp
    ${SOURCE_DIR}/ComputerPlayer.cpp

    # Messenger / I/O
    ${SOURCE_DIR}/ConsoleMessenger.cpp
)

target_include_directories(game PRIVATE ${INCLUDE_DIR})

target_link_libraries(game
    Threads::Threads
)

# ---- Test Executable (Linked with GTest & GMock) ----
add_executable(rps_tests
    # Test sources
    ${TEST_DIR}/test_UserPlayer.cpp
    ${TEST_DIR}/test_ComputerPlayer.cpp
    ${TEST_DIR}/test_ConsoleMessenger.cpp
    ${TEST_DIR}/test_GameSessionFactory.cpp
    # ${TEST_DIR}/test_SinglePlayerRpsGame.cpp

    # Same production sources so tests can link them
    ${SOURCE_DIR}/SinglePlayerRpsGame.cpp
    ${SOURCE_DIR}/GameSessionFactory.cpp
    ${SOURCE_DIR}/UserPlayer.cpp
    ${SOURCE_DIR}/ComputerPlayer.cpp
    ${SOURCE_DIR}/ConsoleMessenger.cpp
)

target_include_directories(rps_tests PRIVATE ${INCLUDE_DIR})

target_link_libraries(rps_tests
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
    Threads::Threads
)

# Enable GoogleTest test discovery
include(GoogleTest)
gtest_discover_tests(rps_tests)
