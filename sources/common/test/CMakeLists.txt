add_executable(common_tests
    flags_test.cpp
)
target_link_libraries(common_tests
    PRIVATE
        catch_main
        common
)

add_test(NAME common_tests
    COMMAND "$<TARGET_FILE:common_tests>"
)
