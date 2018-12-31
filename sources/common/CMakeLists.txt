add_library(common INTERFACE)
#sidekick_apply_flags(common)

target_include_directories(common
    INTERFACE
        include/
)

add_subdirectory(test)
