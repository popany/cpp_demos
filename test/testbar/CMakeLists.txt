set(TESTBAR_SRCS
    testbar.cpp
    main.cpp
)

ADD_EXECUTABLE(testbar ${TESTBAR_SRCS})

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON) # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.65.0 REQUIRED thread)

target_include_directories(testbar
    PRIVATE
        ${Boost_INCLUDE_DIRS}
)

TARGET_LINK_LIBRARIES(testbar
    bar
    gtest
    gmock
    mockcpp
)

add_test(NAME testbar
    COMMAND testbar
)