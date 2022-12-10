cmake_minimum_required(VERSION 3.24)
project(auto_clicker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(auto_clicker main.cpp action.cpp action.h task.cpp menu.h menu.cpp task_historical.h task_historical.cpp)