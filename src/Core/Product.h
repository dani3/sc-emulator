#pragma once

#include "Core/Core.h"
#include "Core/Platform.h"
#include "Protocol/Protocol.h"

/**
 * \brief Enum that represents the different states a product can be in.
 */
enum class CardState { UNINITIALIZED = 0, INITIALIZED, READY, BLOCKED };

/**
 * \brief Class that represents a product.
 *
 * \note There can only be one product at a time.
 *
 * \todo The product needs to be configurable somehow. (Different platform, protocols, etc).
 */
class Product {
public:
    Product();
    // It cannot be cloneable.
    Product(const Product &other) = delete;
    virtual ~Product();

    // It cannot be assignable.
    void operator=(const Product &other) = delete;

    /**
     * \brief Entry point to run the current product.
     */
    void Run();

    /**
     * \brief Get the state of the card.
     *
     * \return State of the card.
     */
    inline CardState GetState() const {
        return m_State;
    }

private:
    /**
     * \brief Reset the card.
     */
    void Reset();

private:
    std::unique_ptr<Platform> m_Platform;
    std::unique_ptr<Protocol> m_Protocol;
    CardState m_State;
};
