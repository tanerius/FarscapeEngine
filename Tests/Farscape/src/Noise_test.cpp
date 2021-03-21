#include "Farscape.h"

#include <gtest/gtest.h>

#include "Core/Math/Noise.h"

static float noiseResult[2];

TEST(NoiseTest, GetNoiseForOrigin)
{
    noiseResult[0] = Farscape::Noise::PerlinNoise(0.0f, 0.0f);
    EXPECT_LT(noiseResult[0], 1.0000f);
}

TEST(NoiseTest, RandomPointsDiffer)
{
    noiseResult[0] = Farscape::Noise::PerlinNoise(1.0f, 1.0f);
    noiseResult[1] = Farscape::Noise::PerlinNoise(2.3f, 5.1f);
    EXPECT_NE(noiseResult[0], noiseResult[1]);
}