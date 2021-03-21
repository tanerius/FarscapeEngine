#include "Farscape.h"
#include <entt/entt.hpp>

#include <gtest/gtest.h>




TEST(ComponentTest, TagComponent)
{
    Farscape::TagComponent comp;
    comp.Tag = "Test";

    ASSERT_STREQ("Test", ((std::string)comp).c_str());
}

TEST(EcsTest, Entt)
{
    struct position {
        float x;
        float y;
    };

    struct velocity {
        float dx;
        float dy;
    };

    entt::registry reg;

    for (auto i = 0u; i < 10u; ++i) {
        const auto entity = reg.create();
        reg.emplace<position>(entity, i * 1.f, i * 1.f);
        if (i % 2 == 0) { reg.emplace<velocity>(entity, i * .1f, i * .1f); }
    }
}