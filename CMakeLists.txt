cmake_minimum_required(VERSION 3.10)
project(ChompAI)

set(CMAKE_CXX_STANDARD 17)

add_executable(chompAI src/main.cpp src/players.cpp src/chomp.cpp include/chomp.hpp)

find_package(Threads REQUIRED)
target_link_libraries(chompAI Threads::Threads)

# Ajouter des flags de compilation pour plus de détails (optionnel, mais recommandé)
set_target_properties(chompAI PROPERTIES COMPILE_FLAGS "-g -Wall -Wextra -pedantic -O3")