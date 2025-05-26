set(TARGET_NAME mdn_card_test)

include(GoogleTest)

set(TARGET_SOURCES
    "card_test.cpp"
)

add_executable(${TARGET_NAME}
    ${TARGET_SOURCES}
)

target_link_libraries(${TARGET_NAME}
    PRIVATE GTest::gmock
    PRIVATE mdn_card
    PRIVATE mdn_test_utils
    PRIVATE nlohmann_json
)

target_include_directories(${TARGET_NAME}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

cmake_language(CALL ${PROJECT_NAME}_setup_tests_data ${TARGET_NAME})

gtest_discover_tests(${TARGET_NAME})
