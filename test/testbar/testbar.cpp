#include "gtest/gtest.h"
#include "libbar/bar.h"
#include "mockcpp/mokc.h"

class BarTest : public ::testing::Test
{
protected:
    BarTest()
    {}

    virtual ~BarTest()
    {}

    virtual void SetUp()
    {}

    virtual void TearDown()
    {}
};

TEST_F(BarTest, Hello)
{
    bar::Hello();
}

TEST_F(BarTest, FuncB)
{
    MOCKER(bar::FuncA)
        .expects(once())
        .will(returnValue(2));

    ASSERT_EQ(20, bar::FuncB());
}
