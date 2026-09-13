#pragma once

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

    struct PacketHeader
    {
        PacketFlags flags;
        u32 sequenceID;
        u32 ackSequence;
        u32 ackBitfield;
        u8  channelID;
        u16 length;

        constexpr bool isUnreliable() const
        {
            return flags == 0;
        }

        constexpr bool isSequenced() const
        {
            return flags & PacketFlag::Sequenced;
        }

        constexpr bool isReliable() const
        {
            return (flags & PacketFlag::Reliable) == PacketFlag::Reliable;
        }

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

            if (!writer.write(channelID) || !writer.write(length))
            {
                return false;
            }

            return true;
        }

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

            if (!reader.read(channelID) || !reader.read(length))
            {
                return false;
            }

            return true;
        }
    };
}