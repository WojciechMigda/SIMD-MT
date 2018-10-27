/*******************************************************************************
 * Copyright (c) 2018 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: likely.h
 *
 * Description:
 *      SIMD-friendly Mersenne Twister PRNG
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2018-10-13   wm              Initial version
 *
 ******************************************************************************/

#pragma once

#include "likely.h"

#include <type_traits>

struct IRNG
{
    static constexpr unsigned int MTSZ = 624;
    static constexpr unsigned int NS = 8;

    int index;

    alignas(64) unsigned int RES[MTSZ * NS];
    alignas(64) unsigned int MT[MTSZ * NS];

    inline
    IRNG(int seed=1)
    {
        init(seed);
    }

    inline
    void init(int seed=1)
    {
        for (auto it = 0u; it < NS; ++it)
        {
            MT[it] = it + seed;
        }

        for (unsigned int i = 1 * NS; i < MTSZ * NS; ++i)
        {
            MT[i] = (1812433253UL * (MT[i - NS] ^ (MT[i - NS] >> 30)) + i / NS);
        }
        index = 0;
    }

    void generate()
    {
        auto MULT1 = 2567483615UL;

        for (unsigned int i = 0; i < 227 * NS; ++i)
        {
            auto y = (MT[i] & 0x8000000UL) + (MT[i + NS] & 0x7FFFFFFFUL);

            MT[i] = MT[i + 397 * NS] ^ (y >> 1) ^ (y & 1 ? MULT1 : 0);
        }
        for (unsigned int i = 227 * NS; i < (MTSZ - 1) * NS; ++i)
        {
            auto y = (MT[i] & 0x8000000UL) + (MT[i + NS] & 0x7FFFFFFFUL);

            MT[i] = MT[i - 227 * NS] ^ (y >> 1) ^ (y & 1 ? MULT1 : 0);
        }

        for (auto it = 0u; it < NS; ++it)
        {
            auto y = (MT[(MTSZ - 1) * NS + it] & 0x8000000UL) + (MT[0 + it] & 0x7FFFFFFFUL);
            MT[(MTSZ - 1) * NS + it] = MT[(MTSZ - 1 - 227) * NS + it] ^ (y >> 1) ^ (y & 1 ? MULT1 : 0);
        }

        for (auto it = 0u; it < MTSZ * NS; ++it)
        {
            auto y = MT[it];
            y ^= y >> 11;
            y ^= y << 7  & 2636928640UL;
            y ^= y << 15 & 4022730752UL;
            y ^= y >> 18;
            RES[it] = y;
        }
    }

    inline
    unsigned int rand()
    {
        if (UNLIKELY(index == 0))
        {
            generate();
        }

        unsigned int y = RES[index];

        if (UNLIKELY(index == MTSZ * NS - 1))
        {
            index = 0;
        }
        else
        {
            ++index;
        }

        return y;
    }

    inline
    int next()
    {
        return rand();
    }

    inline
    int next(int x)
    {
        return rand() % x;
    }

    inline
    int next(int a, int b)
    {
        return a + (rand() % (b + 1 - a));
    }
};

struct FRNG
{
    static constexpr unsigned int MTSZ = 624;
    static constexpr unsigned int NS = 8;

    int index;

    alignas(64) float RES[MTSZ * NS];
    alignas(64) unsigned int MT[MTSZ * NS];

    inline
    FRNG(int seed=1)
    {
        init(seed);
    }

    inline
    void init(int seed=1)
    {
        for (auto it = 0u; it < NS; ++it)
        {
            MT[it] = it + seed;
        }

        for (unsigned int i = 1 * NS; i < MTSZ * NS; ++i)
        {
            MT[i] = (1812433253UL * (MT[i - NS] ^ (MT[i - NS] >> 30)) + i / NS);
        }
        index = 0;
    }

    void generate()
    {
        auto MULT1 = 2567483615UL;

        for (unsigned int i = 0; i < 227 * NS; ++i)
        {
            auto y = (MT[i] & 0x8000000UL) + (MT[i + NS] & 0x7FFFFFFFUL);

            MT[i] = MT[i + 397 * NS] ^ (y >> 1) ^ (y & 1 ? MULT1 : 0);
        }
        for (unsigned int i = 227 * NS; i < (MTSZ - 1) * NS; ++i)
        {
            auto y = (MT[i] & 0x8000000UL) + (MT[i + NS] & 0x7FFFFFFFUL);

            MT[i] = MT[i - 227 * NS] ^ (y >> 1) ^ (y & 1 ? MULT1 : 0);
        }

        for (auto it = 0u; it < NS; ++it)
        {
            auto y = (MT[(MTSZ - 1) * NS + it] & 0x8000000UL) + (MT[0 + it] & 0x7FFFFFFFUL);
            MT[(MTSZ - 1) * NS + it] = MT[(MTSZ - 1 - 227) * NS + it] ^ (y >> 1) ^ (y & 1 ? MULT1 : 0);
        }

        for (auto it = 0u; it < MTSZ * NS; ++it)
        {
            auto y = MT[it];
            y ^= y >> 11;
            y ^= y << 7  & 2636928640UL;
            y ^= y << 15 & 4022730752UL;
            y ^= y >> 18;
            RES[it] = (y + 0.5f) * (1.0f / 4294967296.0f);
        }
    }

    inline
    float rand()
    {
        if (UNLIKELY(index == 0))
        {
            generate();
        }

        float y = RES[index];

        if (UNLIKELY(index == MTSZ * NS - 1))
        {
            index = 0;
        }
        else
        {
            ++index;
        }

        return y;
    }

    inline
    float next()
    {
        return rand();
    }
};
