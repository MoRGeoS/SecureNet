#pragma once

#include <bit>
#include <concepts>

namespace SecureNet
{
    template <std::integral T>
    [[nodiscard]]
    constexpr T byteswap(T value) noexcept
    {
        if constexpr (sizeof(T) == 1)
        {
            return value;
        }
        else if constexpr (sizeof(T) == 2)
        {
            return static_cast<T>(
                ((value & 0x00FF) << 8) |
                ((value & 0xFF00) >> 8)
            );
        }
        else if constexpr (sizeof(T) == 4)
        {
            return static_cast<T>(
                ((value & 0x000000FF) << 24) |
                ((value & 0x0000FF00) << 8)  |
                ((value & 0x00FF0000) >> 8)  |
                ((value & 0xFF000000) >> 24)
            );
        }
        else if constexpr (sizeof(T) == 8)
        {
            return static_cast<T>(
                ((value & 0x00000000000000FFULL) << 56) |
                ((value & 0x000000000000FF00ULL) << 40) |
                ((value & 0x0000000000FF0000ULL) << 24) |
                ((value & 0x00000000FF000000ULL) << 8)  |
                ((value & 0x000000FF00000000ULL) >> 8)  |
                ((value & 0x0000FF0000000000ULL) >> 24) |
                ((value & 0x00FF000000000000ULL) >> 40) |
                ((value & 0xFF00000000000000ULL) >> 56)
            );
        }
        else
        {
            static_assert(false, "byteswap only supports integral types between 1 to 8 bytes.");
        }
    }

    template <std::integral T>
    T bigswap(T value)
    {
        if constexpr (std::endian::native != std::endian::big)
        {
            return byteswap(value);
        }
        else
        {
            return value;
        }
    }

    template <std::integral T>
    T littleswap(T value)
    {
        if constexpr (std::endian::native != std::endian::little)
        {
            return byteswap(value);
        }
        else
        {
            return value;
        }
    }
}