find_package(Catch2 REQUIRED)

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main
    PUBLIC
        Catch2::Catch2
)

