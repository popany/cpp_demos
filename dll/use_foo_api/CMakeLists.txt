set(USE_FOO_API_SRCS
    main.cpp
)

add_executable(use_foo_api ${USE_FOO_API_SRCS})

target_link_libraries(use_foo_api
    foo_api
)

if(WIN32)
target_compile_definitions(foo_api
    PRIVATE
        WIN32
)
endif()