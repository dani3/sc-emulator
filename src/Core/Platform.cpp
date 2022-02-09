#include "Core/Platform.h"

/**
 * \brief
 */
Platform::Platform() {
    m_NvmStart = std::vector<u8>(NVM_SIZE, 0xFF);
}

/**
 * \brief
 */
Platform::~Platform() {
    /// \todo Free NVM areas.
}
