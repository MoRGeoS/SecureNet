#include <SecureNet/Common/BufferedStream.hpp>

#include <cstring>

namespace SecureNet
{
#pragma region BufferedStreamWriter
    [[nodiscard]]
    bool BufferedStreamWriter::write(const ubyte* data, usize length)
    {
        if (m_Length - m_Position < length)
        {
            return false;
        }

        memcpy(m_Buffer + m_Position, data, length);
        m_Position += length;

        return true;
    }
#pragma endregion

#pragma region BufferedStreamReader
    [[nodiscard]]
    bool BufferedStreamReader::read(ubyte* dest, usize length)
    {
        if (m_Length - m_Position < length)
        {
            return false;
        }

        memcpy(dest, m_Buffer + m_Position, length);
        m_Position += length;

        return true;
    }
#pragma endregion
}