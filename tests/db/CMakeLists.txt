set(COMPONENT_NAME db_test)

add_executable (${COMPONENT_NAME}
    database_tests.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    database
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    ${database_INCLUDE_DIRS}
)