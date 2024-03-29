cmake_minimum_required(VERSION 3.6.2)

set(TARGET_NAME Eshop)
project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        Product.cpp
        Inventory.cpp
        OrderItem.cpp
        Order.cpp
        Review.cpp)

set(TEST_FILES
        testy1.cpp
        testy2.cpp
        testy3.cpp
        testy4.cpp
        testy5.cpp)

set(GTEST_SOURCE_FILES
        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc)

add_library(tests OBJECT ${TEST_FILES})
add_library(gtest OBJECT ${GTEST_SOURCE_FILES})

find_package(Threads)

include_directories(GoogleTest)
add_executable(${TARGET_NAME} ${SOURCE_FILES} $<TARGET_OBJECTS:gtest> $<TARGET_OBJECTS:tests>)
target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.74.0 REQUIRED COMPONENTS serialization)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${TARGET_NAME} ${Boost_LIBRARIES})
endif()

# Enable warning messages
set(FLAGS_WARNINGS -Wall -Wextra -Wshadow -Wconversion -Wpedantic -pedantic)
set(FLAGS_AUTO_PATTERN -ftrivial-auto-var-init=pattern)
target_compile_options(${TARGET_NAME} PRIVATE ${FLAGS_WARNINGS})

# If available, enable automatic variable initialization to pattern
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "12")
        target_compile_options(${TARGET_NAME} PRIVATE ${FLAGS_AUTO_PATTERN})
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "8")
        target_compile_options(${TARGET_NAME} PRIVATE ${FLAGS_AUTO_PATTERN})
    endif ()
endif ()
