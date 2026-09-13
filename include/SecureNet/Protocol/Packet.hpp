#pragma once

#include <cstring>

#include <SecureNet/Common/Types.hpp>
#include <SecureNet/Protocol/PacketStream.hpp>

namespace SecureNet
{
    using PacketFlags = u8;
    namespace PacketFlag
    {
        enum : PacketFlags
        {
            Sequenced = 1 << 0,
            Reliable  = 1 << 1 | Sequenced,
        };
    }

    enum class PacketType : u8
    {
        ConnectRequest,
        ConnectResponse,
        Disconnect,
        Ping,
        Pong,
        Message,
        MessageFragment
    };

    struct Packet
    {
        PacketFlags flags;
        u32 sequenceID;     /* Exists only when isSequenced() */
        u32 ackSequence;    /* Exists only when isReliable() */
        u32 ackBitfield;    /* Exists only when isReliable() */
        PacketType type;

        [[nodiscard]]
        constexpr bool isUnreliable() const
        {
            return flags == 0;
        }

        [[nodiscard]]
        constexpr bool isSequenced() const
        {
            return flags & PacketFlag::Sequenced;
        }

        [[nodiscard]]
        constexpr bool isReliable() const
        {
            return (flags & PacketFlag::Reliable) == PacketFlag::Reliable;
        }

        [[nodiscard]]
        bool serialize(PacketStreamWriter& writer) const
        {
            if (!writer.write(flags))
            {
                return false;
            }

            if (isSequenced() && !writer.write(sequenceID))
            {
                return false;
            }

            if (isReliable() && (!writer.write(ackSequence) || !writer.write(ackBitfield)))
            {
                return false;
            }

            return writer.write(type);
        }

        [[nodiscard]]
        bool deserialize(PacketStreamReader& reader)
        {
            if (!reader.read(flags))
            {
                return false;
            }

            if (isSequenced() && !reader.read(sequenceID))
            {
                return false;
            }

            if (isReliable() && (!reader.read(ackSequence) || !reader.read(ackBitfield)))
            {
                return false;
            }
            
            return reader.read(type);
        }
    };
}