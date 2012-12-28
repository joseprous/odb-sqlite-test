cmake_minimum_required (VERSION 2.8.9)
project (odb-sqlite-test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++0x -g")

add_executable(driver driver.cpp person.cpp person-odb.cxx)
target_link_libraries(driver odb odb-sqlite)
