#include "gtest/gtest.h"
#include "libfoo/foo.h"

class FooTest : public ::testing::Test
{
protected:
    FooTest()
    {}

    virtual ~FooTest()
    {}

    virtual void SetUp()
    {}

    virtual void TearDown()
    {}
};

TEST_F(FooTest, Hello)
{
    foo::Hello();
}
