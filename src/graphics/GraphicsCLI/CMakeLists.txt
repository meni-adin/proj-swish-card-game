set(TARGET_NAME mdn_GraphicsCLI)

set(TARGET_SOURCES
    "GraphicsCLI.cpp"
)

add_library(${TARGET_NAME} STATIC
    ${TARGET_SOURCES}
)

target_include_directories(${TARGET_NAME}
    PRIVATE "include"
    PUBLIC "../include"
)

target_link_libraries(${TARGET_NAME}
    PRIVATE mdn_Card
    PRIVATE mdn_Board
    PRIVATE ncurses
)
