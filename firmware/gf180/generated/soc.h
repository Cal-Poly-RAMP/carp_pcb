//--------------------------------------------------------------------------------
// Auto-generated by Migen (9a0be7a) & LiteX (dc4c190) on 2022-11-27 23:51:55
//--------------------------------------------------------------------------------
#ifndef __GENERATED_SOC_H
#define __GENERATED_SOC_H
#define CONFIG_CLOCK_FREQUENCY 10000000
#define CONFIG_CPU_HAS_INTERRUPT
#define CONFIG_CPU_RESET_ADDR 268435456
#define CONFIG_CPU_TYPE_VEXRISCV
#define CONFIG_CPU_VARIANT_MINIMAL
#define CONFIG_CPU_HUMAN_NAME "VexRiscv_MinDebug"
#define CONFIG_CPU_NOP "nop"
#define SPIFLASH_PHY_FREQUENCY 10000000
#define SPIFLASH_MODULE_NAME "W25Q128JV"
#define SPIFLASH_MODULE_TOTAL_SIZE 16777216
#define SPIFLASH_MODULE_PAGE_SIZE 256
#define SPIFLASH_MODULE_QUAD_CAPABLE
#define CONFIG_CSR_DATA_WIDTH 32
#define CONFIG_CSR_ALIGNMENT 32
#define CONFIG_BUS_STANDARD "WISHBONE"
#define CONFIG_BUS_DATA_WIDTH 32
#define CONFIG_BUS_ADDRESS_WIDTH 32
#define TIMER0_INTERRUPT 0
#define UART_INTERRUPT 1
#define USER_IRQ_0_INTERRUPT 2
#define USER_IRQ_1_INTERRUPT 3
#define USER_IRQ_2_INTERRUPT 4
#define USER_IRQ_3_INTERRUPT 5
#define USER_IRQ_4_INTERRUPT 6
#define USER_IRQ_5_INTERRUPT 7

#ifndef __ASSEMBLER__
static inline int config_clock_frequency_read(void) { return 10000000; }

static inline int config_cpu_reset_addr_read(void) { return 268435456; }

static inline const char* config_cpu_human_name_read(void) { return "VexRiscv_MinDebug"; }

static inline const char* config_cpu_nop_read(void) { return "nop"; }

static inline int spiflash_phy_frequency_read(void) { return 10000000; }

static inline const char* spiflash_module_name_read(void) { return "W25Q128JV"; }

static inline int spiflash_module_total_size_read(void) { return 16777216; }

static inline int spiflash_module_page_size_read(void) { return 256; }

static inline int config_csr_data_width_read(void) { return 32; }

static inline int config_csr_alignment_read(void) { return 32; }

static inline const char* config_bus_standard_read(void) { return "WISHBONE"; }

static inline int config_bus_data_width_read(void) { return 32; }

static inline int config_bus_address_width_read(void) { return 32; }

static inline int timer0_interrupt_read(void) { return 0; }

static inline int uart_interrupt_read(void) { return 1; }

static inline int user_irq_0_interrupt_read(void) { return 2; }

static inline int user_irq_1_interrupt_read(void) { return 3; }

static inline int user_irq_2_interrupt_read(void) { return 4; }

static inline int user_irq_3_interrupt_read(void) { return 5; }

static inline int user_irq_4_interrupt_read(void) { return 6; }

static inline int user_irq_5_interrupt_read(void) { return 7; }
#endif // !__ASSEMBLER__

#endif
