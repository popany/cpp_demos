set(TESTFOO_SRCS
    testfoo.cpp
    main.cpp
)

ADD_EXECUTABLE(testfoo ${TESTFOO_SRCS})

TARGET_LINK_LIBRARIES(testfoo
    foo
    gtest
    gmock
)

add_test(NAME testfoo
    COMMAND testfoo
)
