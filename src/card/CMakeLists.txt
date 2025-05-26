set(TARGET_NAME mdn_card)

set(TARGET_SOURCES
    "card.cpp"
)

add_library(${TARGET_NAME} STATIC
    ${TARGET_SOURCES}
)

target_include_directories(${TARGET_NAME}
    PUBLIC "include"
)
