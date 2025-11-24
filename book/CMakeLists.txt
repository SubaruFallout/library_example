add_library(
    book
    book.cpp
)

target_include_directories(
    book
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
