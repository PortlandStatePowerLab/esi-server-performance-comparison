# You should always specify a range with the newest
# and oldest tested versions of CMake. 
cmake_minimum_required(VERSION 3.14)

# set version
set(PROJECT_VERSION 1.0.0)
set(PROJECT_NAME ServerPerformance)

# This is your project statement. You should always list languages;
project(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add dependent macros
include(FetchContent)

add_subdirectory(ecs)
add_subdirectory(database)
#add_subdirectory(tests)