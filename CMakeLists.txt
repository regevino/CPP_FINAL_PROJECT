cmake_minimum_required(VERSION 3.13)
project(CPP_FINAL_PROJECT)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPP_FINAL_PROJECT main.cpp VLVector.hpp)
target_compile_options(CPP_FINAL_PROJECT PUBLIC -Wall)

add_executable(PRESUB PresubmissionTests.cpp VLVector.hpp)
target_compile_options(PRESUB PUBLIC -Wall)
