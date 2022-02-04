#include "Core/Platform.h"

#include <sys/mman.h>

/**
 * \brief
 */
Platform::Platform() {
    m_RamStart = (u8 *) mmap(NULL, RAM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
    m_NvmStart = (u8 *) mmap(NULL, NVM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
}

/**
 * \brief
 */
Platform::~Platform() {
    /// \todo Free RAM and NVM areas.
}
