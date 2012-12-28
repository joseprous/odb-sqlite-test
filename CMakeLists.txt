cmake_minimum_required (VERSION 2.8.9)
project (odb-sqlite-test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++0x -g")

ADD_CUSTOM_COMMAND (OUTPUT person-odb.cxx person-odb.hxx person-odb.ixx
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/person.hpp
  COMMAND odb
  ARGS --std c++11 --database sqlite --generate-query --generate-schema ${CMAKE_CURRENT_SOURCE_DIR}/person.hpp
)

add_executable(driver driver.cpp person.cpp ${CMAKE_CURRENT_BINARY_DIR}/person-odb.cxx)
target_link_libraries(driver odb odb-sqlite)
