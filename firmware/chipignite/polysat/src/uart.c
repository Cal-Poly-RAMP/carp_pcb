/**
 * @file uart.c
 * @brief Universal Asynchronous Receiver/Transmitter (UART) implementation source
 *
 * Provides functions to configure and use the UART for serial communication.
 */

#include <defs.h>
#include <stub.h>
#include <csr.h>
#include "../include/uart.h"

/** @brief Initialize the UART
 */
void uart_init(void) {
  // Configure the UART
  reg_uart_clkdiv = 10;
  reg_uart_enable = 1;

  // Clear any pending interrupts
  uart_ev_pending_write(uart_ev_pending_read());

  // Enable RX/TX
  reg_uart_txfull = 0;
}

/** @brief Synchronize the UART
 */
void uart_sync(void) {
  // Wait for the UART to be ready
  while (reg_uart_txfull == 1);
}

/** @brief Write a character to the UART
 */
void uart_write(uint8_t c) {
  // Wait until TX buffer is not full
  while (uart_txfull_read());

  // Write the character
  uart_rxtx_write(c);
}

/** @brief Read a character from the UART
 */
uint8_t uart_read(void) {
  // Wait until data is available
  while (uart_rxempty_read());

  // Read and return the character
  return uart_rxtx_read();
}

int uart_read_available(void) { return !uart_rxempty_read(); }

int uart_write_available(void) { return !uart_txfull_read(); }
