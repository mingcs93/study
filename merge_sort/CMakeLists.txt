# set minimum cmake version
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# project name and language
project(mergeSort LANGUAGES CXX)
set(target mergeSort)


file(GLOB HEADER "*.hpp")
aux_source_directory(. SOURCES)

add_executable(${target} ${HEADER} ${SOURCES})