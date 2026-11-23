cmake_minimum_required(VERSION 3.16)
project(LeaderBoard_Kata LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(LeaderBoard
    include/Driver.h
    include/IRankingStrategy.h
    include/LeaderBoard.h
    include/Race.h
    include/SelfDrivingCar.h
    source/Driver.cpp
    source/LeaderBoard.cpp
    source/Race.cpp
    source/SelfDrivingCar.cpp
)

target_include_directories(LeaderBoard PUBLIC include)

add_executable(LeaderBoard_Test
    tests/LeaderBoard_Test.cpp
)

target_link_libraries(LeaderBoard_Test PRIVATE LeaderBoard)

if(MSVC)
    target_compile_options(LeaderBoard PRIVATE /W4 /permissive-)
    target_compile_options(LeaderBoard_Test PRIVATE /W4 /permissive-)
endif()