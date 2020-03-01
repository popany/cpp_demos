set(TESTBAR_SRCS
    testbar.cpp
    main.cpp
)

ADD_EXECUTABLE(testbar ${TESTBAR_SRCS})

TARGET_LINK_LIBRARIES(testbar
    bar
    gtest
    gmock
    mockcpp
)

add_test(NAME testbar
    COMMAND testbar
)