# fetch remote packages for development
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

set(COMPONENT_NAME performance)

add_executable (${COMPONENT_NAME}
    main.cpp
    ecs_tests.cpp
    database_tests.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    gtest 
    gtest_main
    ecs
    database
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    ${googletest_INCLUDE_DIRS}
    ${ecs_INCLUDE_DIRS}
    ${database_INCLUDE_DIRS}
)