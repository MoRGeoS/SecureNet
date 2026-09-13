#pragma once

#include <SecureNet/Common/Types.hpp>
#include <SecureNet/Common/IBufferedStream.hpp>

namespace SecureNet
{
    class BufferedStreamWriter : public IBufferedStreamWriter
    {
    public:
        BufferedStreamWriter() = default;

        BufferedStreamWriter(ubyte* buffer, usize length)
            : m_Buffer(buffer)
            , m_Length(length)
        {
        }

        void reset(ubyte* buffer = nullptr, usize length = 0)
        {
            m_Buffer = buffer;
            m_Length = length;
            m_Position = 0;
        }

        [[nodiscard]]
        bool isStreamGood() const override
        {
            return m_Buffer != nullptr;
        }

        [[nodiscard]]
        usize getStreamLength() const override
        {
            return m_Length;
        }

        [[nodiscard]]
        usize getStreamPosition() const override
        {
            return m_Position;
        }

        void setStreamPosition(usize position) override
        {
            if (position > m_Length)
            {
                return;
            }

            m_Position = position;
        }

        [[nodiscard]]
        bool write(const ubyte* data, usize length) override;

    private:
        ubyte* m_Buffer = nullptr;
        usize m_Length = 0;
        usize m_Position = 0;
    };

    class BufferedStreamReader : public IBufferedStreamReader
    {
    public:
        BufferedStreamReader() = default;

        BufferedStreamReader(const ubyte* buffer, usize length)
            : m_Buffer(buffer)
            , m_Length(length)
        {
        }

        void reset(const ubyte* buffer = nullptr, usize length = 0)
        {
            m_Buffer = buffer;
            m_Length = length;
            m_Position = 0;
        }

        [[nodiscard]]
        bool isStreamGood() const override
        {
            return m_Buffer != nullptr;
        }

        [[nodiscard]]
        usize getStreamLength() const override
        {
            return m_Length;
        }

        [[nodiscard]]
        usize getStreamPosition() const override
        {
            return m_Position;
        }

        void setStreamPosition(usize position) override
        {
            if (position > m_Length)
            {
                return;
            }

            m_Position = position;
        }

        [[nodiscard]]
        bool read(ubyte* dest, usize length) override;

    private:
        const ubyte* m_Buffer = nullptr;
        usize m_Length = 0;
        usize m_Position = 0;
    };
}