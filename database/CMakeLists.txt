FetchContent_Declare(
  redis-cpp
  GIT_REPOSITORY https://github.com/tdv/redis-cpp.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(redis-cpp)

# http://mariobadr.com/creating-a-header-only-library-with-cmake.html
set(COMPONENT_NAME database)

add_library(${COMPONENT_NAME} INTERFACE)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_include_directories(
    ${COMPONENT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${COMPONENT_NAME} INTERFACE 
  redis-cpp
  pthread
)