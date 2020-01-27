# Note: "We do not recommend using GLOB to collect a list of source files from your source tree.
# If no CMakeLists.txt file changes when a source is added or removed then the generated build
# system cannot know when to ask CMake to regenerate."
# -- https://cmake.org/cmake/help/v3.16/command/file.html
set(MAIN_SRCS
    main.cpp
)

add_executable(cpp_demos
    ${MAIN_SRCS}
)

target_link_libraries(cpp_demos
    INTERFACE
        foo
    PUBLIC
        bar
)

get_property(SRC_DIR_INCLUDE_DIRECTORIES DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
cmake_print_variables(SRC_DIR_INCLUDE_DIRECTORIES)

get_property(SRC_DIR_INTERFACE_INCLUDE_DIRECTORIES DIRECTORY PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(SRC_DIR_INTERFACE_INCLUDE_DIRECTORIES)

get_property(SRC_EXE_INCLUDE_DIRECTORIES TARGET cpp_demos PROPERTY INCLUDE_DIRECTORIES)
cmake_print_variables(SRC_EXE_INCLUDE_DIRECTORIES)

get_property(SRC_EXE_INTERFACE_INCLUDE_DIRECTORIES TARGET cpp_demos PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(SRC_EXE_INTERFACE_INCLUDE_DIRECTORIES)

get_property(SRC_EXE_LINK_LIBRARIES TARGET cpp_demos PROPERTY LINK_LIBRARIES)
cmake_print_variables(SRC_EXE_LINK_LIBRARIES)

get_property(SRC_EXE_INTERFACE_LINK_LIBRARIES TARGET cpp_demos PROPERTY INTERFACE_LINK_LIBRARIES)
cmake_print_variables(SRC_EXE_INTERFACE_LINK_LIBRARIES)

target_compile_definitions(cpp_demos PRIVATE
    BAR_PROPERTY=$<TARGET_PROPERTY:BAR_PROPERTY>
    BAR_PROPERTY2=$<TARGET_PROPERTY:BAR_PROPERTY2>
)

target_compile_definitions(cpp_demos PRIVATE
    $<$<CONFIG:Debug>:SRC_EXE_DEBUG_BUILD>
)
