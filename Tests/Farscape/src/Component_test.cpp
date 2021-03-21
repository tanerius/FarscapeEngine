#include "Farscape.h"

#include <gtest/gtest.h>



TEST(ComponentTest, TagComponent)
{
    Farscape::TagComponent comp;
    comp.Tag = "Test";

    ASSERT_STREQ("Test", ((std::string)comp).c_str());
}
