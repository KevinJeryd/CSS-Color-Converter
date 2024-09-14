cmake_minimum_required(VERSION 3.16)
project(ColorConverterLib)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set(SOURCES ColorConverter.cpp ${INCLUDE_DIR}/ColorConverter.h)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})