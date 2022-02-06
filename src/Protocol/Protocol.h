#pragma once

#include "Core/Core.h"
#include "Protocol/Atr.h"
#include "Protocol/TcpIpServer.h"

#include <optional>
#include <vector>

/**
 * \brief Class that represents a c_apdu and r_apdu as defined in the ISO_7816-3/4.
 */
class Apdu {
public:
    Apdu();
    Apdu(const u8 *bytes, usize length);
    Apdu(u8 cla, u8 ins, u8 p1, u8 p2, u8 p3, std::optional<const std::vector<u8>> data);
    Apdu(const Apdu &other);
    virtual ~Apdu();

    // Helper function to set the status word given a u16.
    void SetSw(u16 sw);

    void operator=(const Apdu &other);

public:
    u8 cla;               ///< Class byte.
    u8 ins;               ///< Instruction byte.
    u8 p1;                ///< P1 byte.
    u8 p2;                ///< P2 byte.
    u8 p3;                ///< P3 byte.
    std::vector<u8> data; ///< Data buffer.
    u16 nc;               ///< Number of bytes received.
    u16 ne;               ///< Expected data.
    u16 nr;               ///< Number of bytes to be sent.
    u8 sw1;               ///< First byte of the status word.
    u8 sw2;               ///< Second byte of the status word.
};

/**
 * \brief Struct that contains a message received by the other end. This message contains a Type
 * and, optionally, an Apdu.
 */
struct Message {
public:
    enum Type { NEW_CONNECTION, COLD_RESET, APDU, EXIT };

    Message()
        : m_Type(Message::Type::NEW_CONNECTION)
        , m_Apdu(std::nullopt) {
    }

    Message(Type type)
        : m_Type(type)
        , m_Apdu(std::nullopt) {
    }

    Message(const Apdu &apdu)
        : m_Type(Type::APDU) {
        m_Apdu = std::make_unique<Apdu>(apdu);
    }

    Message(const Message &other)
        : m_Type(other.GetType()) {
        m_Apdu = std::make_unique<Apdu>(other.GetApdu());
    }

    Type GetType() const {
        return m_Type;
    }

    const Apdu &GetApdu() const {
        return *m_Apdu.value().get();
    }

private:
    Type m_Type;
    std::optional<std::unique_ptr<Apdu>> m_Apdu;
};

/**
 * \brief Class that represents the protocol component. This file provides a platform-agnostic API
 * to receive APDUs and send the response.
 */
class Protocol {
public:
    Protocol();
    virtual ~Protocol();

    // Initialize the protocol and send the ATR.
    void Init();
    // Receive a message.
    Result<Message> Receive();
    // Send the data and/or the SW.
    void Send(const Message &message);
    // Send the Atr.
    void SendAtr() const;

private:
    /**
     * \brief Struct that represents a packet received from the outside.
     *
     * The `control` byte is mandatory. The rest are optional.
     */
    struct Packet {
        u8 control;   ///< Control byte. Used to determine the type of information that follows (if
                      ///< any).
        u16 length;   ///< Length of the data (zero if no data).
        u8 data[258]; ///< Data buffer (256 bytes + SW).
    };

    // TODO decouple this object from the protocol.
    TcpIpServer *m_Server;
    std::unique_ptr<Atr> m_Atr;
};
