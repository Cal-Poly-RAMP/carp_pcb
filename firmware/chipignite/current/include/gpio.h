/**
 * @file slip.h
 * @brief GPIO implementation header
 *
 * Provides functions to interface with the GPIO pins.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

/* Begin typedef declarations */

/* Begin function prototype declarations */

bool valid_pin(uint32_t pin);
void gpio_set(uint32_t pin, bool value);
void gpio_clear(uint32_t pin);
void gpio_toggle(uint32_t pin);
bool gpio_get(uint32_t pin);

/* Begin inline function declarations */
