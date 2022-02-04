#pragma once

#include "Core/Core.h"

/**
 * \brief Class that defines the platform.
 *
 * It initializes the system so that it mimics as much as possible the final target, e.g. creates
 * the memory regions that represent the EEPROM and RAM.
 */
class Platform {
public:
    // Size of the RAM area.
    static const int RAM_SIZE = 0x10000;
    // Size of the NVM area.
    static const int NVM_SIZE = 0x52000;

    // Initialize the system so that it mimics the real device as closely as possible.
    Platform();
    // It cannot be cloneable.
    Platform(const Platform &other) = delete;
    // Free resources and cleanup.
    virtual ~Platform();

    // It cannot be assignable.
    void operator=(const Platform &other) = delete;

    /**
     * \brief Return an immutable pointer to the start of the RAM.
     *
     * \return Constant pointer to the start of the RAM.
     */
    inline const u8 *GetRamStart() const {
        return (const u8 *) m_RamStart;
    }

    /**
     * \brief Return a mutable pointer to the start of the RAM.
     *
     * \return Mutable pointer to the start of the RAM.
     */
    inline u8 *GetRamStartAsMut() {
        return m_RamStart;
    }

    /**
     * \brief Return an immutable pointer to the start of the NVM.
     *
     * \return Constant pointer to the start of the NVM.
     */
    inline const u8 *GetNvmStart() const {
        return (const u8 *) m_NvmStart;
    }

    /**
     * \brief Return a mutable pointer to the start of the NVM.
     *
     * \return Mutable pointer to the start of the NVM.
     */
    inline u8 *GetNvmStartAsMut() {
        return m_NvmStart;
    }

private:
    // Pointer to the start of the RAM area.
    u8 *m_RamStart;
    // Pointer to the start of the NVM area.
    u8 *m_NvmStart;
};
