#pragma once

#include "Core/Core.h"

#include <vector>

/**
 * \brief Class that defines the platform.
 *
 * It initializes the system so that it mimics as much as possible the final target, e.g. creates
 * the memory regions that represent the EEPROM.
 */
class Platform {
public:
    // Size of the NVM area.
    static const usize NVM_SIZE = 0x52000;

    // Initialize the system so that it mimics the real device as closely as possible.
    Platform();
    // It cannot be cloneable.
    Platform(const Platform &other) = delete;
    // Free resources and cleanup.
    virtual ~Platform();

    // It cannot be assignable.
    void operator=(const Platform &other) = delete;

    /**
     * \brief Return an immutable pointer to the start of the NVM.
     *
     * \return Constant pointer to the start of the NVM.
     */
    inline const std::vector<u8> &GetNvmStart() const {
        return m_NvmStart;
    }

    /**
     * \brief Return a mutable pointer to the start of the NVM.
     *
     * \return Mutable pointer to the start of the NVM.
     */
    inline std::vector<u8> &GetNvmStartAsMut() {
        return m_NvmStart;
    }

private:
    // Vector that represents the NVM area.
    std::vector<u8> m_NvmStart;
};
