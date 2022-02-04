#include "Core/Core.h"
#include "Core/Product.h"

/**
 * \brief Entry point of the simulator.
 *
 * \return Unused.
 */
int main() {
    Log::Init();

    Product product;
    product.Run();

    return 0;
}
