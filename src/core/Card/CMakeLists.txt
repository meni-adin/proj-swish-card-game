set(TARGET_NAME mdn_Card)

set(TARGET_SOURCES
    "Card.cpp"
)

add_library(${TARGET_NAME} STATIC
    ${TARGET_SOURCES}
)

target_include_directories(${TARGET_NAME}
    PUBLIC "include"
)
