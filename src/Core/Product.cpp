#include "Core/Product.h"
#include "Memory/MMU.h"

Product *Product::s_Instance = nullptr;

Product::Product() {
    SC_ASSERT(s_Instance == nullptr, "product already exists!");

    s_Instance = this;
    m_Platform = std::make_unique<Platform>();
    m_Protocol = std::make_unique<Protocol>();

    m_State = CardState::UNINITIALIZED;
}

Product::~Product() {
}

void Product::Run() {
    SC_INFO(
        "starting sc-emulator ({0}.{1}.{2})...", SC_VERSION_MAJOR, SC_VERSION_MINOR,
        SC_VERSION_PATCH);

    // Initialize the protocol.
    m_Protocol->Init();

    while (true) {
        // Set the NVM to 0xFF
        MMU::Fill(m_Platform->GetNvmStartAsMut(), 0xFF, m_Platform->NVM_SIZE);
        // Set the RAM to 0x00
        MMU::Fill(m_Platform->GetRamStartAsMut(), 0x00, m_Platform->RAM_SIZE);

        while (true) {
            Result<Message> res = m_Protocol->Receive();
            if (res.IsOk()) {
                // Apdu apdu = res.Value();
                //
                // apdu.SetSw(0x9000);
                // m_Protocol->Send(apdu);

            } else {
                /// \todo Return error code.
            }
        }
    }
}
