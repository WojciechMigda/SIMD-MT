#include <gtest/gtest.h>
#include "mt.hpp"
#include "reference.hpp"

TEST(SimdMtTest, IRNG_can_be_created)
{
    IRNG rng;
}


TEST(SimdMtTest, FRNG_can_be_created)
{
    FRNG rng;
}


TEST(SimdMtTest, IRNG_generates_same_numbers_as_the_reference)
{
    constexpr auto NS = 8u;
    IRNG rng(1); // 8 streams
    ref::RNG base[NS];

    for (auto it = 0u; it < NS; ++it)
    {
        base[it].init(it + 1);
    }

    for (auto it = 0u; it < 20000; ++it)
    {
        for (auto jt = 0u; jt < NS; ++jt)
        {
            auto ref = base[jt].next();
            auto val = rng.next();

            ASSERT_EQ(ref, val);
        }
    }

}


TEST(SimdMtTest, FRNG_generates_same_numbers_as_the_reference)
{
    constexpr auto NS = 8u;
    FRNG rng(1); // 8 streams
    ref::RNG base[NS];

    for (auto it = 0u; it < NS; ++it)
    {
        base[it].init(it + 1);
    }

    for (auto it = 0u; it < 20000; ++it)
    {
        for (auto jt = 0u; jt < NS; ++jt)
        {
            auto ref = base[jt].nextFloat();
            auto val = rng.next();

            ASSERT_FLOAT_EQ(ref, val);
        }
    }

}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
