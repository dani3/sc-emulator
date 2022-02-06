#include "Core/Platform.h"

/**
 * \brief
 */
Platform::Platform() {
    m_RamStart = std::vector<u8>(RAM_SIZE, 0x00);
    m_NvmStart = std::vector<u8>(NVM_SIZE, 0xFF);
}

/**
 * \brief
 */
Platform::~Platform() {
    /// \todo Free RAM and NVM areas.
}
