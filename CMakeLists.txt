# Main CMake file for compiling the library itself, examples and tests.
#
# Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT) 

cmake_minimum_required(VERSION 2.6)
project(ecs)

# Define useful variables to handle OS differences:
if (WIN32)
    set(DEV_NULL                "NUL")
else (WIN32)
    set(DEV_NULL                "/dev/null")
endif (WIN32)
# then Compiler/IDE differences:
if (MSVC)
    set(CPPLINT_ARG_OUTPUT      "--output=vs7")
    set(CPPCHECK_ARG_TEMPLATE   "--template=vs")
    # disable Visual Studio warnings for fopen() used in the example
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else (MSVC)
    set(CPPLINT_ARG_OUTPUT      "--output=eclipse")
    set(CPPCHECK_ARG_TEMPLATE   "--template=gcc")
    if (CMAKE_COMPILER_IS_GNUCXX)
        # GCC flags
        add_definitions(-rdynamic -fstack-protector-all -Wall -Wextra -pedantic -Wformat-security -Winit-self -Wswitch-default -Wswitch-enum -Wfloat-equal -Wshadow -Wcast-qual -Wconversion -Wlogical-op -Winline -Wsuggest-attribute=pure -Wsuggest-attribute=const)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # Clang flags
        add_definitions(-fstack-protector-all -Wall -Wextra -pedantic -Wformat-security -Winit-self -Wswitch-default -Wswitch-enum -Wfloat-equal -Wshadow -Wcast-qual -Wconversion -Winline)
    endif (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "C++11 activated")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  # -std=c++11
endif (MSVC)
# and then common variables
set(CPPLINT_ARG_VERBOSE "--verbose=3")
set(CPPLINT_ARG_LINELENGTH "--linelength=120")


## Core source code ##

# adding a new file require explicittly modifing the CMakeLists.txt
# so that CMake knows that it should rebuild the project (it is best practice)

# list of sources files of the library
set(ECS_SRC
 ${PROJECT_SOURCE_DIR}/src/Manager.cpp
 ${PROJECT_SOURCE_DIR}/src/System.cpp
)
source_group(src FILES ${ECS_SRC})

# list of header files
set(ECS_INC
 ${PROJECT_SOURCE_DIR}/include/ecs/Component.h
 ${PROJECT_SOURCE_DIR}/include/ecs/ComponentType.h
 ${PROJECT_SOURCE_DIR}/include/ecs/ComponentStore.h
 ${PROJECT_SOURCE_DIR}/include/ecs/Entity.h
 ${PROJECT_SOURCE_DIR}/include/ecs/Manager.h
 ${PROJECT_SOURCE_DIR}/include/ecs/System.h
)
source_group(include FILES ${ECS_INC})

# list of test files of the library
set(ECS_TESTS
 tests/Manager_test.cpp
 tests/ComponentStore_test.cpp
)
source_group(tests FILES ${ECS_TESTS})

# list of example files of the library
set(ECS_EXAMPLES
 examples/basic/basic.cpp
)
source_group(basic FILES ${ECS_EXAMPLES})

# list of doc files of the library
set(ECS_DOC
 README.md
 LICENSE.txt
 ecs.dox
)
source_group(doc FILES ${ECS_DOC})

# All includes are relative to the "include" directory 
include_directories("${PROJECT_SOURCE_DIR}/include")

# add sources of the library as a "ecs" static library
add_library(ecs ${ECS_SRC} ${ECS_INC} ${ECS_DOC})

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
     COMMAND python ${PROJECT_SOURCE_DIR}/cpplint.py ${CPPLINT_ARG_OUTPUT} ${CPPLINT_ARG_VERBOSE} ${CPPLINT_ARG_LINELENGTH} ${ECS_SRC} ${ECS_INC}
    )
else (ECS_RUN_CPPLINT)
    message(STATUS "ECS_RUN_CPPLINT OFF")
endif (ECS_RUN_CPPLINT)

option(ECS_RUN_CPPCHECK "Run cppcheck C++ static analysis tool." ON)
if (ECS_RUN_CPPCHECK)
    # add a cppcheck target to the "all" target
    add_custom_target(ecs_cppcheck
     ALL
     COMMAND cppcheck -j 4 cppcheck --enable=style --quiet ${CPPCHECK_ARG_TEMPLATE} ${PROJECT_SOURCE_DIR}/src
    )
else (ECS_RUN_CPPCHECK)
    message(STATUS "ECS_RUN_CPPCHECK OFF")
endif (ECS_RUN_CPPCHECK)

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
    else(DOXYGEN_FOUND)
        message(STATUS "Doxygen not found")
    endif(DOXYGEN_FOUND)
else(ECS_RUN_DOXYGEN)
    message(STATUS "ECS_RUN_DOXYGEN OFF")
endif(ECS_RUN_DOXYGEN)

option(ECS_BUILD_EXAMPLES "Build examples." ON)
if (ECS_BUILD_EXAMPLES)
    # add the basic example executable
    add_executable(ecs_example_basic ${ECS_EXAMPLES})
    target_link_libraries(ecs_example_basic gtest_main ecs)
else(ECS_BUILD_EXAMPLES)
    message(STATUS "ECS_BUILD_EXAMPLES OFF")
endif(ECS_BUILD_EXAMPLES)

option(ECS_BUILD_TESTS "Build and run tests." ON)
if (ECS_BUILD_TESTS)
    if (MSVC)
        # Specific flags for gtest lib
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    endif (MSVC)    

    # add the subdirectory containing the CMakeLists.txt for the gtest library
    add_subdirectory(googletest) 
    include_directories("${PROJECT_SOURCE_DIR}/googletest/include")

    # add the unit test executable
    add_executable(ecs_tests ${ECS_TESTS})
    target_link_libraries(ecs_tests gtest_main ecs)

    # add a "test" target:
    enable_testing()

    # does the tests pass?
    add_test(UnitTests ecs_tests)

    if (ECS_BUILD_EXAMPLES)
        # does the example runs successfully?
        add_test(BasicExample ecs_example_basic)
    endif(ECS_BUILD_EXAMPLES)
else(ECS_BUILD_TESTS)
    message(STATUS "ECS_BUILD_TESTS OFF")
endif(ECS_BUILD_TESTS)

