cmake_minimum_required(VERSION 3.5)
project(minilang)

# Define options/variables
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CURRENT_BUILD_DIR ${PROJECT_SOURCE_DIR}/cmake-build-debug)

# Prepare build directory
file(MAKE_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/include/bison
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/src/flex
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/src/bison)

# -I
include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/cpp/include)

# Load Flex and Bison
find_package(BISON)
find_package(FLEX)
if(NOT FLEX_FOUND)
    message(FATAL_ERROR "Flex package was not found")
elseif(NOT BISON_FOUND)
    message(FATAL_ERROR "Bison package was not found")
endif()

# Flex it!
flex_target(miniflex ${PROJECT_SOURCE_DIR}/etc/flex/minilang.l
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/src/flex/minilang_flex.cpp)

# Bison it!
bison_target(minibison ${PROJECT_SOURCE_DIR}/etc/bison/minilang.y
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/src/bison/minilang_bison.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/cpp/include/bison/minilang_bison.h)

# Build c++ files
add_executable(${PROJECT_NAME} ${BISON_minibison_OUTPUTS} ${FLEX_miniflex_OUTPUTS})
target_link_libraries(${PROJECT_NAME} ${FLEX_LIBRARIES} )
