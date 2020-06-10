ADD_EXECUTABLE(scan_port scan_port.cpp)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON) # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.70.0 REQUIRED thread regex)

if(UNIX)
find_library(RT_LIB rt) # 'Boost_USE_STATIC_LIBS ON' need this
target_link_libraries(scan_port
    PRIVATE
        Boost::thread
        ${RT_LIB}
)
endif()

if(WIN32)
target_link_libraries(scan_port
    PRIVATE
        Boost::thread
        Boost::regex
)
endif()

target_include_directories(scan_port
    PRIVATE
        ${Boost_INCLUDE_DIRS}
)