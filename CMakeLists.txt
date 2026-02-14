cmake_minimum_required(VERSION 3.16)

set(projectName "wastewater_system")

option(SIM "Build for simulation" OFF)

if(SIM)
    message(STATUS "Building for simulation")
    add_definitions(-DSIM_TIME)
endif()
project(${projectName})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#add_subdirectory(experiments)
add_subdirectory(tests)
