cmake_minimum_required(VERSION 3.10)
project(ChompAI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc-14)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-14) 


find_package(OpenMP REQUIRED)


add_executable(chompAI
    src/main.cpp
    src/players.cpp
    src/chomp.cpp
)

target_compile_options(chompAI PRIVATE ${OpenMP_CXX_FLAGS})
target_link_libraries(chompAI PRIVATE ${OpenMP_CXX_FLAGS}) 

target_compile_options(chompAI PRIVATE -O3 -Wall -Wextra -Wpedantic)

find_package(Threads REQUIRED)
target_link_libraries(chompAI PRIVATE Threads::Threads)