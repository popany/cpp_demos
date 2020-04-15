set(DYNAMIC_LOAD_WIN32_SRCS
    main.cpp
)

add_executable(dynamic_load_win32 ${DYNAMIC_LOAD_WIN32_SRCS})

target_include_directories(dynamic_load_win32
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../foo_api/include
)
