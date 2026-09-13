cmake_minimum_required(VERSION 3.20)

project(
  SecureNet
  VERSION 0.1
)

file(GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(SecureNet
  STATIC
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

set_target_properties(SecureNet
  PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(SecureNet
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)