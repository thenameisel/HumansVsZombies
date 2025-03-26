cmake_minimum_required(VERSION 3.30)
project(HumansVsZombies)

set(CMAKE_CXX_STANDARD 26)

add_executable(HumansVsZombies main.cpp
        City.cpp
        Human.cpp
        Organism.cpp
        Zombie.cpp)
