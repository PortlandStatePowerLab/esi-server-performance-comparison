set(COMPONENT_NAME ecs_test)

add_executable (${COMPONENT_NAME}
    ecs_tests.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    ecs
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    ${ecs_INCLUDE_DIRS}
    ${database_INCLUDE_DIRS}
)