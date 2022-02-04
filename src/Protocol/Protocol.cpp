#include "Protocol/Protocol.h"

#include <stdlib.h>
#include <string.h>

#define CONTROL_COLD_RESET 0
#define CONTROL_TRANSMIT   1
#define CONTROL_EXIT       2

#define HEADER_SIZE 5

Apdu::Apdu()
    : cla(0)
    , ins(0)
    , p1(0)
    , p2(0)
    , p3(0)
    , data(std::vector<u8>())
    , nc(0)
    , ne(0)
    , nr(0)
    , sw1(0)
    , sw2(0) {
}

Apdu::Apdu(const u8 *bytes, usize length)
    : cla(bytes[0])
    , ins(bytes[1])
    , p1(bytes[2])
    , p2(bytes[3])
    , p3(bytes[4]) {
    // TODO fill data vector.
}

Apdu::Apdu(const Apdu &other) {
    this->cla = other.cla;
    this->ins = other.ins;
    this->p1 = other.p1;
    this->p2 = other.p2;
    this->p3 = other.p3;
    this->nc = other.nc;
    this->ne = other.ne;
    this->nr = other.nr;
    this->sw1 = other.sw1;
    this->sw2 = other.sw2;
    this->data = other.data;
}

Apdu::Apdu(u8 cla, u8 ins, u8 p1, u8 p2, u8 p3, std::optional<const std::vector<u8>> data)
    : cla(cla)
    , ins(ins)
    , p1(p1)
    , p2(p2)
    , p3(p3)
    , nc(0)
    , ne(0)
    , nr(0)
    , sw1(0)
    , sw2(0) {
}

Apdu::~Apdu() {
}

/**
 * \brief Helper function to set the status word given a u16.
 *
 * \param sw status word to be set.
 */
void Apdu::SetSw(u16 sw) {
    this->sw1 = (u8) (sw >> 8);
    this->sw2 = (u8) (sw & 0xFF);
}

Protocol::Protocol() {
    m_Server = TcpIpServer::GetInstance();
    m_Atr = std::make_unique<Atr>();
}

Protocol::~Protocol() {
    m_Server->Close();
}

/**
 * \brief Initialize the protocol and send the ATR.
 */
void Protocol::Init() {
    SC_INFO("initializing protocol...");

    m_Server->Init();
    m_Server->Accept();

    const u8 *atr = m_Atr->AsPtr();
    m_Atr->Print();

    // Set the packet to be sent.
    Packet packet;
    memcpy(packet.data, atr, m_Atr->Size());
    packet.length = m_Atr->Size();

    m_Server->Send((const u8 *) &packet.length, sizeof(packet.length));
    m_Server->Send(packet.data, packet.length);
}

/**
 * \brief Receive a message. This function will not retry. If an error occurs the connection is
 * closed.
 *
 * \note This function is blocking.
 *
 * \return Message object.
 */
Result<Message> Protocol::Receive() {
    SC_INFO("waiting for a new command...");

    u8 bytes[5 + 256] = { 0 };
    Packet packet;

    // Receive the control byte.
    if (m_Server->Receive((u8 *) &packet.control, sizeof(packet.control)) != ReceiveResult::Ok) {
        return Result<Message>::Error("error receiving control byte");
    }

    switch (packet.control) {
    case CONTROL_COLD_RESET:
        return Result<Message>(Message(Message::Type::COLD_RESET));

    case CONTROL_EXIT:
        return Result<Message>(Message(Message::Type::EXIT));
    }

    // Receive the length.
    if (m_Server->Receive((u8 *) &packet.length, sizeof(packet.length)) != ReceiveResult::Ok) {
        return Result<Message>::Error("error receiving length");
    }

    if (packet.length) {
        if (m_Server->Receive(bytes, packet.length) != ReceiveResult::Ok) {
            return Result<Message>::Error("error receiving payload");
        }
    }

    Apdu apdu(bytes, packet.length);
    SC_INFO(
        "apdu received: %02X %02X %02X %02X %02X", apdu.cla, apdu.ins, apdu.p1, apdu.p2, apdu.p3);

    // If it's a 4-byte case 1 command.
    if (packet.length == 4) {
        packet.length++;
    }

    if ((apdu.p3 + HEADER_SIZE) == packet.length) {
        // Case 1
        // Case 2
        // Case 3 with p3 == 0
        // Case 4 with no Le
        apdu.ne = apdu.p3;
        apdu.nc = 0;

    } else if (((apdu.p3 + HEADER_SIZE) > packet.length) && (packet.length == HEADER_SIZE)) {
        // Case 3 with p3 <> 0
        apdu.ne = apdu.p3;
        apdu.nc = 0;

    } else if ((apdu.p3 + HEADER_SIZE + 1) == packet.length) {
        // Case 4 command and Le is present.
        apdu.ne = apdu.data[apdu.p3];
        apdu.nc = apdu.p3;
    }

    return Result<Message>(Message(apdu));
}

/**
 * \brief Send the data and/or the SW. This function expects that at least apdu_t.nr, apdu_t.sw1 and
 * apdu_t.sw2 are set.
 *
 * \param apdu Apdu to be sent.
 */
void Protocol::Send(const Message &message) {
    SC_INFO("sending response...");

    Packet packet;
    const Apdu &r_apdu = message.GetApdu();
    if (r_apdu.nr > 0) {
        memcpy(packet.data, &r_apdu.data[0], r_apdu.nr);

        packet.length = r_apdu.nr + 2;
        packet.data[r_apdu.nr] = r_apdu.sw1;
        packet.data[r_apdu.nr + 1] = r_apdu.sw2;
    } else {
        packet.length = 2;
        packet.data[0] = r_apdu.sw1;
        packet.data[1] = r_apdu.sw2;
    }

    m_Server->Send((const u8 *) &packet.length, sizeof(packet.length));
    m_Server->Send(packet.data, packet.length);
}
