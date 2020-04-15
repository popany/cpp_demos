if (WIN32)
set(FOO_API_SRCS
    foo_api.cpp
    dll_main.cpp
)
else()
set(FOO_API_SRCS
    foo_api.cpp
)
endif()

add_library(foo_api SHARED 
	${FOO_API_SRCS}
)

target_include_directories(foo_api
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
target_compile_definitions(foo_api
    PRIVATE
        WIN32
        FOOLIBRARY_EXPORTS
)
endif()
