set(FOO_SRCS
    foo.cpp
)

add_library(foo STATIC
    ${FOO_SRCS}
)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON) # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.65.0 REQUIRED thread)

if(UNIX)
    find_library(RT_LIB rt) # 'Boost_USE_STATIC_LIBS ON' need this
endif()

target_link_libraries(foo
    PRIVATE
        Boost::thread
        ${RT_LIB}
)

target_include_directories(foo
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/private
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/interface
    PRIVATE
        ${Boost_INCLUDE_DIRS}
)

get_property(FOO_DIR_INCLUDE_DIRECTORIES DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
cmake_print_variables(FOO_DIR_INCLUDE_DIRECTORIES)

get_property(FOO_DIR_INTERFACE_INCLUDE_DIRECTORIES DIRECTORY PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(FOO_DIR_INTERFACE_INCLUDE_DIRECTORIES)

get_property(FOO_LIB_INCLUDE_DIRECTORIES TARGET foo PROPERTY INCLUDE_DIRECTORIES)
cmake_print_variables(FOO_LIB_INCLUDE_DIRECTORIES)

get_property(FOO_LIB_INTERFACE_INCLUDE_DIRECTORIES TARGET foo PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(FOO_LIB_INTERFACE_INCLUDE_DIRECTORIES)

get_property(FOO_LINK_LIBRARIES TARGET foo PROPERTY LINK_LIBRARIES)
cmake_print_variables(FOO_LINK_LIBRARIES)

get_property(FOO_INTERFACE_LINK_LIBRARIES TARGET foo PROPERTY INTERFACE_LINK_LIBRARIES)
cmake_print_variables(FOO_INTERFACE_LINK_LIBRARIES)
