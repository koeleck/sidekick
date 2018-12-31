include_guard(DIRECTORY)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

#
# Warnings
#
set(SIDEKICK_WARNING_FLAGS "")
function(sidekick_check_warning FLAG)
    string(REGEX REPLACE "^[/-]" "" VARNAME "${FLAG}")
    string(REGEX REPLACE "[- =]" "_" VARNAME "${VARNAME}")
    set(VARNAME "HAS_${VARNAME}")
    check_cxx_compiler_flag(${FLAG} ${VARNAME})
    if(${${VARNAME}})
        list(APPEND SIDEKICK_WARNING_FLAGS ${FLAG})
        set(SIDEKICK_WARNING_FLAGS "${SIDEKICK_WARNING_FLAGS}" PARENT_SCOPE)
    endif()
endfunction()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    sidekick_check_warning("-Wextra")
    sidekick_check_warning("-Wduplicated-cond")
    sidekick_check_warning("-Wduplicated-branches")
    sidekick_check_warning("-Wlogical-op")
    sidekick_check_warning("-Wrestrict")
    sidekick_check_warning("-Wnull-dereference")
    sidekick_check_warning("-Wold-style-cast")
    sidekick_check_warning("-Wuseless-cast")
    sidekick_check_warning("-Wjump-misses-init")
    sidekick_check_warning("-Wdouble-promotion")
    sidekick_check_warning("-Wshadow=compatible-local")
    sidekick_check_warning("-Wformat=2")
    sidekick_check_warning("-Wpedantic")
    sidekick_check_warning("-pedantic-errors")
    sidekick_check_warning("-Wparentheses")
    sidekick_check_warning("-Wcast-align=strict")
    sidekick_check_warning("-Wconversion")
    sidekick_check_warning("-Wsign-conversion")
    sidekick_check_warning("-Wzero-as-null-pointer-constant")
    sidekick_check_warning("-Wnoexcept")
    sidekick_check_warning("-Wnon-virtual-dtor")
    sidekick_check_warning("-Woverloaded-virtual")
    sidekick_check_warning("-Wlifetime")
endif()

function(sidekick_apply_flags TARGET)
    set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        CXX_VISIBILITY_PRESET "hidden"
        VISIBILITY_INLINES_HIDDEN ON
        POSITION_INDEPENDENT_CODE ON
    )
    target_compile_options(${TARGET}
        PRIVATE
            ${SIDEKICK_WARNING_FLAGS}
    )
endfunction()

