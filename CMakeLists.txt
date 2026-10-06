cmake_minimum_required(VERSION 3.28)
project(particle_simulation LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 3 CONFIG QUIET COMPONENTS Graphics Window System)

if(NOT SFML_FOUND)
    include(FetchContent)

    message(STATUS "SFML 3 was not found; downloading it with CMake")
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
    )
    FetchContent_MakeAvailable(SFML)
endif()

add_executable(particle-simulation
    main.cpp
    source/verlet.cpp
    source/solver.cpp
    source/circleSimulation.cpp
)

target_include_directories(particle-simulation PRIVATE include)

target_link_libraries(particle-simulation PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

set_target_properties(particle-simulation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/ARIAL.TTF"
    "${CMAKE_BINARY_DIR}/bin/ARIAL.TTF"
    COPYONLY
)

include(GNUInstallDirs)
install(TARGETS particle-simulation
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(FILES ARIAL.TTF
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)
