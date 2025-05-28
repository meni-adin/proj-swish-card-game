include(fetch_content_wrapper)
cmake_language(CALL ${PROJECT_NAME}_fetch_content_wrapper
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        origin/main
)

cmake_language(CALL ${PROJECT_NAME}_fetch_content_wrapper
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        origin/master
)

enable_testing()

add_subdirectory(card_test)
add_subdirectory(test_utils)
