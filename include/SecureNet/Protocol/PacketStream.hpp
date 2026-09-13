#pragma once

#include <SecureNet/Common/IBufferedStream.hpp>
#include <SecureNet/Common/ByteSwap.hpp>

namespace SecureNet
{
    class PacketStreamWriter
    {
    public:
        using stream_type = IBufferedStreamWriter;

        PacketStreamWriter() = default;

        PacketStreamWriter(stream_type& stream) : m_Stream(&stream)
        {
        }

        [[nodiscard]]
        stream_type* getStream() const
        {
            return m_Stream;
        }

        void setStream(stream_type& stream)
        {
            m_Stream = &stream;
        }

        template <std::integral T>
        [[nodiscard]]
        bool write(T value)
        {
            T net = littleswap(value);
            return m_Stream->writeRaw(net);
        }

        template <typename T>
        requires (!std::integral<T>)
        [[nodiscard]]
        bool write(const T& value)
        {
            return value.serialize(*this);
        }

    private:
        stream_type* m_Stream = nullptr;
    };

    class PacketStreamReader
    {
    public:
        using stream_type = IBufferedStreamReader;

        PacketStreamReader() = default;

        PacketStreamReader(stream_type& stream) : m_Stream(&stream)
        {
        }

        [[nodiscard]]
        stream_type* getStream() const
        {
            return m_Stream;
        }

        void setStream(stream_type& stream)
        {
            m_Stream = &stream;
        }

        template <std::integral T>
        [[nodiscard]]
        bool read(T value)
        {
            T net;
            if (!m_Stream->readRaw(net))
            {
                return false;
            }

            return littleswap(net);
        }

        template <typename T>
        requires (!std::integral<T>)
        [[nodiscard]]
        bool read(T& value)
        {
            return value.deserialize(*this);
        }

    private:
        stream_type* m_Stream = nullptr;
    };
}