cmake_minimum_required(VERSION 3.5)
project(minilang)

# Define options/variables
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# -I
include_directories(include)

# Load Flex and Bison
find_package(BISON)
find_package(FLEX)
if(NOT FLEX_FOUND)
    message(FATAL_ERROR "Flex package was not found")
elseif(NOT BISON_FOUND)
    message(FATAL_ERROR "Bison package was not found")
endif()

# Flex it!
FLEX_TARGET(miniflex ${PROJECT_SOURCE_DIR}/etc/flex/minilang.l  ${CMAKE_CURRENT_BINARY_DIR}/minilang_flex.cpp)

# Build c++ files
file(GLOB_RECURSE PROJECT_SOURCE_FILES src/*.cpp ${FLEX_miniflex_OUTPUTS})
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} fl)
