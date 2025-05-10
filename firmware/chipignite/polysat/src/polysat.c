#include <defs.h>
#include <stub.h>
#include <csr.h>
#include "../include/slip.h"
#include "../include/uart.h"
#include "../include/gpio.h"

// --------------------------------------------------------
// Firmware routines
// --------------------------------------------------------

/** @brief Configure the IO pins
 */
void configure_io() {
  //  ======= Useful GPIO mode values =============

  //  GPIO_MODE_MGMT_STD_INPUT_NOPULL
  //  GPIO_MODE_MGMT_STD_INPUT_PULLDOWN
  //  GPIO_MODE_MGMT_STD_INPUT_PULLUP
  //  GPIO_MODE_MGMT_STD_OUTPUT
  //  GPIO_MODE_MGMT_STD_BIDIRECTIONAL
  //  GPIO_MODE_MGMT_STD_ANALOG

  //  GPIO_MODE_USER_STD_INPUT_NOPULL
  //  GPIO_MODE_USER_STD_INPUT_PULLDOWN
  //  GPIO_MODE_USER_STD_INPUT_PULLUP
  //  GPIO_MODE_USER_STD_OUTPUT
  //  GPIO_MODE_USER_STD_BIDIRECTIONAL
  //  GPIO_MODE_USER_STD_ANALOG

  //  ======= set each IO to the desired configuration =============

  //  GPIO 0 is turned off to prevent toggling the debug pin; For debug, make this an output and
  //  drive it externally to ground.

  reg_mprj_io_0 = GPIO_MODE_MGMT_STD_ANALOG;

  // Changing configuration for IO[1-4] will interfere with programming flash. if you change them,
  // You may need to hold reset while powering up the board and initiating flash to keep the process
  // configuring these IO from their default values.

  // SPI
  reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_2 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_3 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_4 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

  // -------------------------------------------

  reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL; // UART Rx
  reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT; // UART Tx
  reg_mprj_io_7 = GPIO_MODE_MGMT_STD_INPUT_NOPULL; // Used for reset
  reg_mprj_io_8 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_9 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_10 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_11 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_12 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_13 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_14 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_15 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_16 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_17 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_18 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

  reg_mprj_io_19 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_20 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_21 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_22 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_23 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_24 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_25 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_26 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_27 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_28 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_29 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_30 = GPIO_MODE_MGMT_STD_INPUT_PULLUP; // High
  reg_mprj_io_31 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN; // Low
  reg_mprj_io_32 = GPIO_MODE_MGMT_STD_INPUT_PULLUP; // High
  reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT; // Controlled by the code
  reg_mprj_io_34 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_35 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_36 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
  reg_mprj_io_37 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

  // Initialize UART
  uart_init();

  // Initiate the serial transfer to configure IO
  reg_mprj_xfer = 1;
  while (reg_mprj_xfer == 1);
}

/** @brief Delay in microseconds
 *
 * @param d Delay in microseconds.
 */
void delay(const int d) {
  /* Configure timer for a single-shot countdown */
  reg_timer0_config = 0;
  reg_timer0_data = d;
  reg_timer0_config = 1;

  // Loop, waiting for value to reach zero
  reg_timer0_update = 1; // latch current value
  while (reg_timer0_value > 0) { reg_timer0_update = 1; }
}

/** @brief Turn off the LED
 */
void led_off() { reg_gpio_out = 1; }

/** @brief Turn on the LED
 */
void led_on() { reg_gpio_out = 0; }

/** @brief Entry point
 */
void main() {
  // Initialize GPIO
  reg_gpio_mode1 = 1;
  reg_gpio_mode0 = 0;
  reg_gpio_ien = 1;
  reg_gpio_oe = 1;

  // Configure IO pins including UART pins
  configure_io();

  // Configure All LA probes as inputs to the cpu
  reg_la0_oenb = reg_la0_iena = 0x00000000; // [31:0]
  reg_la1_oenb = reg_la1_iena = 0x00000000; // [63:32]
  reg_la2_oenb = reg_la2_iena = 0x00000000; // [95:64]
  reg_la3_oenb = reg_la3_iena = 0x00000000; // [127:96]

  // write data to la output
  //	reg_la0_data = 0x00;
  //	reg_la1_data = 0x00;
  //	reg_la2_data = 0x00;
  //	reg_la3_data = 0x00;

  // read data from la input
  //	data0 = reg_la0_data;
  //	data1 = reg_la1_data;
  //	data2 = reg_la2_data;
  //	data3 = reg_la3_data;

  bool pulse = false;

  // Turn off all GPIO outputs
  reg_mprj_datah = 0x00000000; // Set all high pins (32-37) low
  reg_mprj_datal = 0x00000000; // Set all low pins (0-31) low

  // Main loop - echo received characters and blink LED and
  while (1) {
    // // Check if data is available to read
    // if (uart_read_available()) {
    //   // Read and echo back the character
    //   uint8_t ch = uart_read();
    //   uart_write(ch);
    //   slip_send_packet(c, 1, SLIP_CMD_DATA, uart_write);
    // }

    if (!pulse) {
      led_off();
      // Set GPIO 33 low (bit 1)
      gpio_clear(33);
    } else {
      led_on();
      // Set GPIO 33 high (bit 1)
      gpio_set(33, true);
    }
    pulse = !pulse;
    const char message_to_send[] = "Hello, World!";
    slip_send_packet(message_to_send, sizeof(message_to_send) - 1, SLIP_CMD_DATA, uart_write);

    // Wait for 1 second
    delay(10000000);
  }
}
