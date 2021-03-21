#include "Farscape.h"

#include <gtest/gtest.h>


class Sandbox : public Farscape::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

class ApplicationTest : public ::testing::Test
{

    virtual void SetUp() override
    {
        Farscape::InitializeEngine();

    }

    virtual void TearDown() override {}
};


TEST_F(ApplicationTest, AppCreation)
{
    auto app = new Sandbox();
    EXPECT_NE(app, nullptr);
    delete app;
}

