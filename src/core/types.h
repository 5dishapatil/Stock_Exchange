#pragma once

#include<algorithm>
#include<array>
#include<cstdint>
#include<string_view>
#include<type_traits>

namespace stock_exchange::core{

    using Price = std::int64_t;  // we are purposely choosing integer to avoid floating point precision issues. we will be multiply each original number by 10000 to store it as integer. for example, 1.2345 will be stored as 12345

    using Quantity = std::uint32_t;

    using OrderId = std::uint64_t;

    using SequenceNumber = std::uint64_t;

    using Timestamp = std::uint64_t; // we will be using two clocks - one is the wall clock (which measures upto nanoseconds)and the other is the logical clock (which is a simple counter that increments with each event). we will be using the logical clock for ordering events and the wall clock for measuring time intervals.

    using ParticipantId = std::uint32_t;

    using MatchID = std::uint64_t;

    inline constexpr Price PRICE_SCALE = 10'000;
}