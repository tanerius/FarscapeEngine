#include "Farscape.h"

#include <gtest/gtest.h>

class ApplicationTest : public ::testing::Test
{

    virtual void SetUp() override
    {

    }

    virtual void TearDown() override {}
};


TEST_F(ApplicationTest, AppCreation)
{
    auto app = new Farscape::Application();
    EXPECT_NE(app, nullptr);
    delete app;
}

