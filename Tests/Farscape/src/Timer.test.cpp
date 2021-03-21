#include "Farscape.h"

#include <gtest/gtest.h>

#if defined(FS_WIN64)
#include<windows.h>

void FSSleep(int milliseconds)
{
    Sleep(milliseconds);
}

#elif defined(FS_LINUX)
#include<unistd.h>

void FSSleep(int milliseconds)
{
    unsigned int microsecond = 1000;
    usleep(milliseconds * microsecond);
}
#else

#endif


class TimerTest : public ::testing::Test
{
private:
    Farscape::Timer m_timer;
public:
    virtual void SetUp() override
    {
        
    }

    virtual void TearDown() override {}

    TimerTest()
    {
        // sleep for 3 sec in construction
        FSSleep(3000);
    }

    Farscape::Timer& GetTimer() { return m_timer; }
};


TEST_F(TimerTest, TimerPointerCheck)
{
    auto timer = GetTimer();
    // more than three socends must hav elapsed
    EXPECT_GT(timer.Elapsed(), 3.0f);
}

