#include "Core/Product.h"
#include "Memory/MMU.h"

Product::Product() {
    m_Platform = std::make_unique<Platform>();
    m_Protocol = std::make_unique<Protocol>();

    m_State = CardState::UNINITIALIZED;
}

Product::~Product() {
}

void Product::Reset() {
    // TODO move this to Device.
    // Set the RAM to 0x00
    MMU::Fill(&m_Platform->GetRamStartAsMut()[0], 0x00, m_Platform->RAM_SIZE);

    m_Protocol->SendAtr();
}

void Product::Run() {
    SC_INFO(
        "starting sc-emulator ({0}.{1}.{2})...", SC_VERSION_MAJOR, SC_VERSION_MINOR,
        SC_VERSION_PATCH);

    // Initialize the protocol.
    m_Protocol->Init();

    while (true) {
        // Set the RAM to 0x00
        MMU::Fill(&m_Platform->GetRamStartAsMut()[0], 0x00, m_Platform->RAM_SIZE);

        while (true) {
            Result<Message> res = m_Protocol->Receive();
            if (res.IsOk()) {
                switch (res.Value().GetType()) {
                case Message::Type::NEW_CONNECTION:
                    SC_PANIC("not implemented yet");
                    break;

                case Message::Type::COLD_RESET:
                    Reset();
                    break;

                case Message::Type::EXIT:
                    break;

                case Message::Type::APDU:
                    Apdu apdu = res.Value().GetApdu();

                    apdu.SetSw(0x9000);
                    m_Protocol->Send(apdu);
                    break;
                }

            } else {
                /// \todo Return error code.
            }
        }
    }
}
