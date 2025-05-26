set(TARGET_NAME mdn_test_utils)

set(TARGET_SOURCES
    "test_utils.cpp"
)

add_library(${TARGET_NAME} STATIC
    ${TARGET_SOURCES}
)

target_include_directories(${TARGET_NAME}
    PUBLIC "include"
)

target_link_libraries(${TARGET_NAME}
    PRIVATE nlohmann_json
)