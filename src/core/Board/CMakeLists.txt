set(TARGET_NAME mdn_Board)

set(TARGET_SOURCES
    "Board.cpp"
)

add_library(${TARGET_NAME} STATIC
    ${TARGET_SOURCES}
)

target_include_directories(${TARGET_NAME}
    PUBLIC "include"
)

target_link_libraries(${TARGET_NAME}
    PUBLIC mdn_Card
)
