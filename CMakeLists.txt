cmake_minimum_required(VERSION 3.5)

project(cpp_demos VERSION 1.0.0 LANGUAGES CXX C)

set (CMAKE_CXX_STANDARD 11)

# set(CMAKE_VERBOSE_MAKEFILE on)

include(CMakePrintHelpers)
if(WIN32)
    cmake_print_variables(MSVC_VERSION MSVC_TOOLSET_VERSION CMAKE_CXX_COMPILER_VERSION CMAKE_GENERATOR)
endif()

enable_testing()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(libfoo)
add_subdirectory(libbar)

get_property(ROOT_DIR_INCLUDE_DIRECTORIES DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
cmake_print_variables(ROOT_DIR_INCLUDE_DIRECTORIES)

get_property(ROOT_DIR_INTERFACE_INCLUDE_DIRECTORIES DIRECTORY PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(ROOT_DIR_INTERFACE_INCLUDE_DIRECTORIES)
