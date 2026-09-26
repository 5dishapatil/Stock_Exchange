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

    enum class Side : std::uint8_t{
        BUY,
        SELL
    };

    enum class OrderType : std::uint8_t{
        LIMIT,
        MARKET,
        IOC,
        FOK,
        GTC,
        STOP,
        STOP_LIMIT,
        ICEBERG,
        POST_ONLY,
    };

    enum class OrderStatus : std::uint8_t{
        NEW,
        ACCEPTED,
        PARTIALLY_FILLED,
        FILLED,
        CANCELED,
    };

    using Symbol = std::array<char, 8>; // we are using std::array instead of std::string to avoid dynamic memory allocation. we will be using a fixed size array of 8 characters to store the symbol. if the symbol is less than 8 characters, we will pad it with null characters.

    constexpr Symbol make_symbol(std::string_view text) noexcept{
        Symbol symbol{};
        const auto length = std::min(symbol.size(), text.size());
        for(std::size_t index = 0; index < length; ++index){
            symbol[index] = text[index];
        }
        return symbol;
    }

    constexpr std::string_view symbol_view(const Symbol &symbol) noexcept{
        std::size_t length = 0;
        while(length < symbol.size() && symbol[length] != '\0'){
            ++length;
        }
        return std::string_view{symbol.data(), length};
    }

    struct SymbolLess{
        constexpr bool operator()(const Symbol &lhs, const Symbol &rhs) const noexcept{
            return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }
    };

    static_assert(std::is_trivially_copyable_v<Price>);
    static_assert(std::is_trivially_copyable_v<Quantity>);
    static_assert(std::is_trivially_copyable_v<OrderId>);
    static_assert(std::is_trivially_copyable_v<SequenceNumber>);
    static_assert(std::is_trivially_copyable_v<Timestamp>);
    static_assert(std::is_trivially_copyable_v<ParticipantId>);
    static_assert(std::is_trivially_copyable_v<MatchID>);
    static_assert(std::is_trivially_copyable_v<Side>);
    static_assert(std::is_trivially_copyable_v<OrderType>);
    static_assert(std::is_trivially_copyable_v<OrderStatus>);
    static_assert(std::is_trivially_copyable_v<Symbol>);

}