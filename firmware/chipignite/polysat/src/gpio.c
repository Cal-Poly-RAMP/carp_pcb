#include "../include/gpio.h"

#include <defs.h>

/** @brief Set the value of a GPIO pin (high)
 *
 * @param pin The pin to set.
 * @param value The value to set the pin to.
 */
void gpio_set(uint32_t pin, bool value) {
  if (pin < 32) {
    // Register for low pins (0-31)
    reg_mprj_datal |= (1 << (pin % 32));
  } else if (pin <= 37) {
    // Register for high pins (32-37)
    reg_mprj_datah |= (1 << (pin % 32));
  }
}

/** @brief Clear the value of a GPIO pin (low)
 *
 * @param pin The pin to clear.
 */
void gpio_clear(uint32_t pin) {
  if (pin < 32) {
    // Register for low pins (0-31)
    reg_mprj_datal &= ~(1 << (pin % 32));
  } else if (pin <= 37) {
    // Register for high pins (32-37)
    reg_mprj_datah &= ~(1 << (pin % 32));
  }
}

/** @brief Toggle the value of a GPIO pin
 *
 * @param pin The pin to toggle.
 */
void gpio_toggle(uint32_t pin) {
  if (pin < 32) {
    // Register for low pins (0-31)
    reg_mprj_datal ^= (1 << (pin % 32));
  } else if (pin <= 37) {
    // Register for high pins (32-37)
    reg_mprj_datah ^= (1 << (pin % 32));
  }
}

/** @brief Get the value of a GPIO pin
 *
 * @param pin The pin to get.
 * @return The value of the pin.
 */
bool gpio_get(uint32_t pin) {
  if (pin < 32) {
    // Register for low pins (0-31)
    return (reg_mprj_datal & (1 << (pin % 32))) != 0;
  } else if (pin <= 37) {
    // Register for high pins (32-37)
    return (reg_mprj_datah & (1 << (pin % 32))) != 0;
  }
  return false;
}
