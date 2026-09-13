#pragma once

#include <SecureNet/Common/Types.hpp>

namespace SecureNet
{
    class IBufferedStreamWriter
    {
    public:
        virtual ~IBufferedStreamWriter() = default;

        [[nodiscard]]
        virtual bool isStreamGood() const = 0;

        [[nodiscard]]
        virtual usize getStreamLength() const = 0;
        
        [[nodiscard]]
        virtual usize getStreamPosition() const = 0;

        virtual void setStreamPosition(usize position) = 0;

        [[nodiscard]]
        virtual bool write(const ubyte* data, usize length) = 0;

        template <typename T>
        [[nodiscard]]
        bool writeRaw(const T& object)
        {
            return write(
                reinterpret_cast<const ubyte*>(&object), 
                sizeof(T)
            );
        }
    };

    class IBufferedStreamReader
    {
    public:
        virtual ~IBufferedStreamReader() = default;

        [[nodiscard]]
        virtual bool isStreamGood() const = 0;

        [[nodiscard]]
        virtual usize getStreamLength() const = 0;
        
        [[nodiscard]]
        virtual usize getStreamPosition() const = 0;

        virtual void setStreamPosition(usize position) = 0;

        [[nodiscard]]
        virtual bool read(ubyte* dest, usize length) = 0;

        template <typename T>
        [[nodiscard]]
        bool readRaw(T& object)
        {
            return read(
                reinterpret_cast<ubyte*>(&object), 
                sizeof(T)
            );
        }

        [[nodiscard]]
        explicit operator bool() const
        {
            return isStreamGood();
        }
    };
}