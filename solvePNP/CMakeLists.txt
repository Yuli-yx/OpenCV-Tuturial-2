cmake_minimum_required(VERSION 3.10)
project(solvePNP)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(solvePNP main.cpp SolvePNP.cpp )
target_link_libraries(solvePNP ${OpenCV_LIBS})

