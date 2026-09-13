#pragma once

#include <SecureNet/Common/Types.hpp>
#include <SecureNet/Protocol/PacketStream.hpp>

namespace SecureNet
{
    struct ConnectRequest
    {
        u32 magic;      /* Magic number to identify protocol */
        u32 version;    /* Procol version */
        u32 sequence;   /* Initial sequence id */
        u64 timestamp;  /* Timestamp for ping */

        [[nodiscard]]
        bool serialize(PacketStreamWriter& writer) const
        {
            return
                writer.write(magic) &&
                writer.write(version) &&
                writer.write(sequence) &&
                writer.getStream()->writeRaw(timestamp);
        }

        [[nodiscard]]
        bool deserialize(PacketStreamReader& reader) const
        {
            return
                reader.read(magic) &&
                reader.read(version) &&
                reader.read(sequence) &&
                reader.getStream()->readRaw(timestamp);
        }
    };

    struct ConnectResponse
    {
        u32 version;    /* Protocol version */
        u32 sequence;   /* Initial sequence id */
        u64 timestamp;  /* Timestamp response */

        [[nodiscard]]
        bool serialize(PacketStreamWriter& writer) const
        {
            return
                writer.write(version) &&
                writer.write(sequence) &&
                writer.getStream()->writeRaw(timestamp);
        }

        [[nodiscard]]
        bool deserialize(PacketStreamReader& reader) const
        {
            return
                reader.read(version) &&
                reader.read(sequence) &&
                reader.getStream()->readRaw(timestamp);
        }
    };

    struct Disconnect
    {
        enum class Reason : u16
        {
            Unknown = 0,
            Timeout
        };

        Reason reason;

        [[nodiscard]]
        bool serialize(PacketStreamWriter& writer) const
        {
            return writer.write(reason);
        }

        [[nodiscard]]
        bool deserialize(PacketStreamReader& reader)
        {
            return reader.read(reason);
        }
    };

    struct Ping
    {
        u64 timestamp;

        [[nodiscard]]
        bool serialize(PacketStreamWriter& writer) const
        {
            return writer.getStream()->writeRaw(timestamp);
        }

        [[nodiscard]]
        bool deserialize(PacketStreamReader& reader)
        {
            return reader.getStream()->readRaw(timestamp);
        }
    };

    struct Pong
    {
        u64 timestamp;

        [[nodiscard]]
        bool serialize(PacketStreamWriter& writer) const
        {
            return writer.getStream()->writeRaw(timestamp);
        }

        [[nodiscard]]
        bool deserialize(PacketStreamReader& reader)
        {
            return reader.getStream()->readRaw(timestamp);
        }
    };

    struct Message
    {
        u32 messageID;      /* New message id */
        u16 fragmentCount;  /* Fragment count of new message */

        [[nodiscard]]
        bool serialize(PacketStreamWriter& writer) const
        {
            return
                writer.write(messageID) &&
                writer.write(fragmentCount);
        }

        [[nodiscard]]
        bool deserialize(PacketStreamReader& reader)
        {
            return
                reader.read(messageID) &&
                reader.read(fragmentCount);
        }
    };

    struct MessageFragment
    {
        u32 messageID;      /* Existing message id */
        u16 fragmentIndex;  /* Fragment's index */

        [[nodiscard]]
        bool serialize(PacketStreamWriter& writer) const
        {
            return
                writer.write(messageID) &&
                writer.write(fragmentIndex);
        }

        [[nodiscard]]
        bool deserialize(PacketStreamReader& reader)
        {
            return
                reader.read(messageID) &&
                reader.read(fragmentIndex);
        }
    };
}