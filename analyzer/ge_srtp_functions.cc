// Copyright (c) 2024 Battelle Energy Alliance, LLC. 

#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <hilti/rt/libhilti.h>
#include <spicy/rt/libspicy.h>

namespace GE_SRTP_FUNCTIONS
{
    #define ID_LEN 9

    // Spicy exports its version in `PROJECT_VERSION_NUMBER`.
    // hilti::rt::String was introduced in HILTI 1.16 (Zeek 8.2.1); on
    // earlier versions (e.g. Zeek 8.0.9 / HILTI 1.14.2) it doesn't exist,
    // so fall back to std::string there.
#if PROJECT_VERSION_NUMBER >= 11600
    using SpicyString = hilti::rt::String;
#else
    using SpicyString = std::string;
#endif

    SpicyString generateId() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 255);

        std::stringstream ss;
        for (auto i = 0; i < ID_LEN; i++) {
            // Generate a random char
            const auto rc = dis(gen);
            // Hex representaton of random char
            std::stringstream hexstream;
            hexstream << std::hex << rc;
            auto hex = hexstream.str();
            ss << (hex.length() < 2 ? '0' + hex : hex);
        }
        return {ss.str()};
    }
}