#include "Core/Product.h"

Product::Product() {
    m_Platform = std::make_unique<Platform>();
    m_Protocol = std::make_unique<Protocol>();

    m_State = CardState::UNINITIALIZED;
}

Product::~Product() {
}

void Product::Reset() {
    m_Protocol->SendAtr();
}

void Product::Run() {
    SC_INFO(
        "starting sc-emulator ({0}.{1}.{2})...", SC_VERSION_MAJOR, SC_VERSION_MINOR,
        SC_VERSION_PATCH);

    // Initialize the protocol.
    m_Protocol->Init();

    bool exit = false;
    while (!exit) {
        Result<Message> res = m_Protocol->Receive();
        if (res.IsOk()) {
            switch (res.Value().GetType()) {
            case Message::Type::NEW_CONNECTION:
                SC_PANIC("not implemented yet");
                break;

            case Message::Type::COLD_RESET:
                SC_INFO("cold reset received...");
                Reset();
                break;

            case Message::Type::EXIT:
                SC_INFO("exit request received...");
                exit = true;
                break;

            case Message::Type::APDU:
                SC_INFO("new APDU received...");
                Apdu apdu = res.Value().GetApdu();

                apdu.SetSw(0x9000);
                m_Protocol->Send(apdu);
                break;
            }

        } else {
            exit = true;
        }
    }

    SC_INFO("shutting down sc-emulator...");
}
