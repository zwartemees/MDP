cmake_minimum_required(VERSION 3.19)

# set compiler
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")
#project

project(MDPresent)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<1:${CMAKE_CURRENT_SOURCE_DIR}>")
set(CMAKE_CXX_FLAGS "-lstdc++")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(mongoose STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/mongoose.c)

add_executable(MDP MDP.cpp)
target_link_libraries(MDP mongoose)