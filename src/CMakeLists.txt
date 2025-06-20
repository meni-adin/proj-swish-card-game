set(TARGET_NAME mdn_game)

set(TARGET_SOURCES
    "main.cpp"
)

add_executable(${TARGET_NAME}
    ${TARGET_SOURCES}
)

target_link_libraries(${TARGET_NAME}
    PRIVATE mdn_card
    PRIVATE nlohmann_json
    PRIVATE ncurses
)

add_subdirectory(board)
add_subdirectory(card)
