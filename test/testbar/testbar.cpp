#include "gtest/gtest.h"
#include "libbar/bar.h"

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
