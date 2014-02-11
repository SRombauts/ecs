# Main CMake file for compiling the library itself, examples and tests.
#
# Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT) 

cmake_minimum_required(VERSION 2.6)
project(ecs)

# Define useful variables to handle OS/Compiler differences
if (MSVC)
    set(CPPLINT_ARG_OUTPUT      "--output=vs7")
    set(CPPCHECK_ARG_TEMPLATE   "--template=vs")
    set(DEV_NULL                "NUL")
    # disable Visual Studio warnings for fopen() used in the example
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif (UNIX)
    set(CPPLINT_ARG_OUTPUT      "--output=eclipse")
    set(CPPCHECK_ARG_TEMPLATE   "--template=gcc")
    set(DEV_NULL                "/dev/null")
    if (CMAKE_COMPILER_IS_GNUCXX)
        # GCC flags
        add_definitions(-rdynamic -fstack-protector-all -Wall -Wextra -pedantic -Weffc++ -Wformat-security -Winit-self -Wswitch-default -Wswitch-enum -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wconversion -Wlogical-op -Winline -Wsuggest-attribute=pure -Wsuggest-attribute=const)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # Clang flags
        add_definitions(-fstack-protector-all -Wall -Wextra -pedantic -Weffc++ -Wformat-security -Winit-self -Wswitch-default -Wswitch-enum -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wconversion -Winline)
    endif ()
    message(STATUS "C++11 activated")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  # -std=c++11
endif ()
set(CPPLINT_ARG_VERBOSE "--verbose=3")
set(CPPLINT_ARG_LINELENGTH "--linelength=120")


## Core source code ##

# adding a new file require explicittly modifing the CMakeLists.txt
# so that CMake knows that it should rebuild the project (it is best practice)

# list of sources files of the library
set(ECS_SRC
 src/Manager.cpp
 src/System.cpp
)
source_group(src FILES ${ECS_SRC})

# list of headers
set(ECS_INC
 include/ecs/Component.h
 include/ecs/Entity.h
 include/ecs/Manager.h
 include/ecs/System.h
)
source_group(include FILES ${ECS_INC})

# All includes are relative to the "include" directory 
include_directories("${PROJECT_SOURCE_DIR}/include")

# add sources of the wrapper as a "ecs" static library
add_library(ecs ${ECS_SRC} ${ECS_INC})

# Position Independant Code for shared librarie
if(UNIX AND (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
    set_target_properties(ecs PROPERTIES COMPILE_FLAGS "-fPIC")
endif(UNIX AND (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))


# Optional additional targets:

option(ECS_RUN_CPPLINT "Run cpplint.py tool for Google C++ StyleGuide." ON)
if (ECS_RUN_CPPLINT)
    # add a cpplint target to the "all" target
    add_custom_target(ecs_cpplint
     ALL
     COMMAND python cpplint.py ${CPPLINT_ARG_OUTPUT} ${CPPLINT_ARG_VERBOSE} ${CPPLINT_ARG_LINELENGTH} ${ECS_SRC} ${ECS_INC}
     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
else()
    message(STATUS "ECS_RUN_CPPLINT OFF")
endif()

option(ECS_RUN_CPPCHECK "Run cppcheck C++ static analysis tool." ON)
if (ECS_RUN_CPPCHECK)
    # add a cppcheck target to the "all" target
    add_custom_target(ecs_cppcheck
     ALL
     COMMAND cppcheck -j 4 cppcheck --enable=style --quiet ${CPPCHECK_ARG_TEMPLATE} src
     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
else()
    message(STATUS "ECS_RUN_CPPCHECK OFF")
endif()

option(ECS_RUN_DOXYGEN "Run Doxygen C++ documentation tool." ON)
if (ECS_RUN_DOXYGEN)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # add a Doxygen target to the "all" target
        add_custom_target(ecs_doxygen
         ALL
         COMMAND doxygen Doxyfile > ${DEV_NULL}
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
    else()
        message(STATUS "Doxygen not found")
    endif()
else()
    message(STATUS "ECS_RUN_DOXYGEN OFF")
endif()

option(ECS_RUN_TESTS "Run test tools." ON)
if (ECS_RUN_TESTS)
    # TODO
    # add the example executable, linked with the wrapper library
    #add_executable(example examples/main.cpp)
    #target_link_libraries(example ecs)

    # add a "test" target:
    #enable_testing()

    # does the example runs successfully?
    #add_test(ExampleRun example)
else()
    message(STATUS "ECS_RUN_TESTS OFF")
endif()
