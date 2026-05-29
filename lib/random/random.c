/**
 * @author Matej Franek
 * @brief Knihovna s funkcí pro generování náhodných čísel pomocí algoritmu Xorshift32
 * @date 29.5.2026
 * @version 1
*/
#include <stdint.h>
#include "random.h"
uint32_t xorshift32(uint32_t *state) {
    /** @brief Implementace algoritmu Xorshift32
     *  @param state: ukazatel na stav generátoru
     *  @return: náhodné číslo
     */
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return *state = x;
}