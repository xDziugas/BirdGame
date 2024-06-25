cmake_minimum_required(VERSION 3.28)
project(BirdGame)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/SFML/SFML-2.6.1/lib/cmake/SFML")

include_directories("C:/SFML/SFML-2.6.1/include/SFML")
include_directories(include)

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)

add_executable(BirdGame main.cpp
        src/Bird.cpp
        include/Bird.h
        src/Background.cpp
        include/Background.h
        src/Ground.cpp
        include/Ground.h)
target_link_libraries(BirdGame sfml-audio sfml-graphics sfml-system sfml-window)
