#include <gtest/gtest.h>
#include "mt.hpp"

TEST(SimdMtTest, IRNG_can_be_created)
{
    IRNG rng;
}


TEST(SimdMtTest, FRNG_can_be_created)
{
    FRNG rng;
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
