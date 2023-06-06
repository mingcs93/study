# set minimum cmake version
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# project name and language
project(unionFind LANGUAGES CXX)
set(target unionFind)


file(GLOB HEADER "*.hpp")
aux_source_directory(. SOURCES)

add_executable(${target} ${HEADER} ${SOURCES})