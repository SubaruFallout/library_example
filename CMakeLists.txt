cmake_minimum_required(VERSION 3.14)

project(LibraryEmulation)

add_subdirectory(book)
add_subdirectory(client)

add_library(
    library
    library.cpp
)

target_include_directories(
    library
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(library book client)
