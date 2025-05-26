set(TARGET_NAME mdn_main)

set(TARGET_SOURCES
    "main.cpp"
)

add_executable(${TARGET_NAME}
    ${TARGET_SOURCES}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC mdn_card
)

add_subdirectory(card)
