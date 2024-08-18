#include <defs.h>
#include <stub.h>

#include "print.h"


void led_off()
{
    reg_gpio_out = 1; // OFF
    reg_mprj_datal = 0x00000000;
    reg_mprj_datah = 0x00000000;
}

void led_on()
{
    reg_gpio_out = 0;  // ON
    reg_mprj_datah = 0x0000003f;
    reg_mprj_datal = 0xffffffff;
}

void led_blink()
{
    led_on();
    delay(800000);
    led_off();
    delay(800000);
}

void config_logic()
{
    reg_la0_iena = 0x00007FFF;    // [31:0]
	reg_la1_iena = 0x00000000;    // [63:32]
	reg_la2_iena = 0x00000000;    // [95:64]
	reg_la3_iena = 0x00000000;    // [127:96]

    reg_la0_oenb = 0x00007FFF;    // [31:0]
	reg_la1_oenb = 0x00000000;    // [63:32]
	reg_la2_oenb = 0x00000000;    // [95:64]
	reg_la3_oenb = 0x00000000;    // [127:96]
}

void print_logic()
{
    // print("Logic Analyzer Out Bits: \n");
    // printk("%u\n", reg_la0_data);
    print_hex(reg_la3_data, 8);
    print(" ");
    print_hex(reg_la2_data, 8);
    print(" ");
    print_hex(reg_la1_data, 8);
    print(" ");
    print_hex(reg_la0_data, 8);
    print("\n");
    for (int channel = 0; channel < 8; channel += 1)
    {

        print("Logic Analyzer Channel ");
        print_dec(channel);
        print(": \n");
        reg_la0_data &= ~(0x7000);
        reg_la0_data |= channel << 12;

        
        print_hex(reg_la3_data, 8);
        print(" ");
        print_hex(reg_la2_data, 8);
        print(" ");
        print_hex(reg_la1_data, 8);
        print(" ");
        print_hex(reg_la0_data, 8);
        print("\n");

        reg_la_sample = 0;
        reg_la_sample = 1;

        print_hex(reg_la3_data_in, 8);
        print(" ");
        print_hex(reg_la2_data_in, 8);
        print(" ");
        print_hex(reg_la1_data_in, 8);
        print(" ");
        print_hex(reg_la0_data_in, 8);
        print("\n");
    }
}
// --------------------------------------------------------
// Firmware routines
// --------------------------------------------------------

void configure_io()
{

//  ======= Useful GPIO mode values =============

//      GPIO_MODE_MGMT_STD_INPUT_NOPULL
//      GPIO_MODE_MGMT_STD_INPUT_PULLDOWN
//      GPIO_MODE_MGMT_STD_INPUT_PULLUP
//      GPIO_MODE_MGMT_STD_OUTPUT
//      GPIO_MODE_MGMT_STD_BIDIRECTIONAL
//      GPIO_MODE_MGMT_STD_ANALOG

//      GPIO_MODE_USER_STD_INPUT_NOPULL
//      GPIO_MODE_USER_STD_INPUT_PULLDOWN
//      GPIO_MODE_USER_STD_INPUT_PULLUP
//      GPIO_MODE_USER_STD_OUTPUT
//      GPIO_MODE_USER_STD_BIDIRECTIONAL
//      GPIO_MODE_USER_STD_ANALOG


//  ======= set each IO to the desired configuration =============

    //  GPIO 0 is turned off to prevent toggling the debug pin; For debug, make this an output and
    //  drive it externally to ground.

    reg_mprj_io_0 = GPIO_MODE_MGMT_STD_ANALOG;

    // Changing configuration for IO[1-4] will interfere with programming flash. if you change them,
    // You may need to hold reset while powering up the board and initiating flash to keep the process
    // configuring these IO from their default values.

    reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_2 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_3 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_4 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

    // -------------------------------------------

    reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;     // UART Rx
    reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;           // UART Tx
    reg_mprj_io_7 = GPIO_MODE_USER_STD_INPUT_PULLUP;
    reg_mprj_io_8 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_9 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_USER_STD_BIDIRECTIONAL;
    reg_mprj_io_11 = GPIO_MODE_USER_STD_BIDIRECTIONAL;
    reg_mprj_io_12 = GPIO_MODE_USER_STD_BIDIRECTIONAL;
    reg_mprj_io_13 = GPIO_MODE_USER_STD_BIDIRECTIONAL;
    reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;

    reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;

    // Initiate the serial transfer to configure IO
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
}

void delay(const int d)
{

    /* Configure timer for a single-shot countdown */
	reg_timer0_config = 0;
	reg_timer0_data = d;
    reg_timer0_config = 1;

    // Loop, waiting for value to reach zero
   reg_timer0_update = 1;  // latch current value
   while (reg_timer0_value > 0) {
           reg_timer0_update = 1;
   }

}

void main()
{
	int i, j, k;

    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;

    configure_io();

    reg_uart_enable = 1;

    config_logic();

    reg_la0_data = 0x000000A0;

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
    print("Hello World - mgmt");
    led_off();
    volatile uint32_t * carp_mem = ( uint32_t *)0x30000000;
	while (1) {
        uint32_t carp_mem_data;
        print_logic();
        led_blink();
        
        reg_wb_enable = 1;
        *carp_mem = 0xAC;
        carp_mem_data = *carp_mem;
        reg_wb_enable = 0;

        print("Wishbone Read:\n");
        print_hex(carp_mem_data, 8);
        print("\n");

        // led_blink();
        // print("Hello World - mgmt\n\r");
        // print("abcdefg\n");
        if ( carp_mem_data != 0xAC)
        {
            // print("Fail !!\n");
            led_off();
            delay(8000000);
        } else {
            // print("Pass !!\n");
            // led_on();

            led_on();
            delay(8000000);
        }


    }


}

