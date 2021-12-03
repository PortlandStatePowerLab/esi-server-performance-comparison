FetchContent_Declare(
  mysql-conn
  GIT_REPOSITORY https://github.com/mysql/mysql-connector-cpp.git
  GIT_TAG        8.0.27
)

FetchContent_MakeAvailable(mysql-conn)

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
  xapi
  devapi
  connector
  pthread
)