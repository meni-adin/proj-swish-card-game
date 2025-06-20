set(TARGET_NAME mdn_board)

set(TARGET_SOURCES
    "board.cpp"
)

add_library(${TARGET_NAME} STATIC
    ${TARGET_SOURCES}
)

target_include_directories(${TARGET_NAME}
    PUBLIC "include"
)

target_link_libraries(${TARGET_NAME}
    PUBLIC mdn_card
)
