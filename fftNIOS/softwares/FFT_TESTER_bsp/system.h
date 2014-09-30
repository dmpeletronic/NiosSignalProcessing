/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpuNios' in SOPC Builder design 'processador'
 * SOPC Builder design path: C:/altera/Projetos/fftNIOS/processador.sopcinfo
 *
 * Generated: Sun Feb 26 21:25:22 BRT 2012
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x4003820
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x0
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1b
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x20
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1b
#define ALT_CPU_NAME "cpuNios"
#define ALT_CPU_RESET_ADDR 0x0


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x4003820
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x0
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1b
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x20
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1b
#define NIOS2_RESET_ADDR 0x0


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PERFORMANCE_COUNTER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SGDMA
#define __ALTERA_AVALON_SYSID
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2
#define __ALTMEMDDR
#define __FFT_PIPELINE
#define __TRIPLE_SPEED_ETHERNET


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "CYCLONEIII"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x4004880
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x4004880
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x4004880
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "processador"


/*
 * descriptor_memory configuration
 *
 */

#define ALT_MODULE_CLASS_descriptor_memory altera_avalon_onchip_memory2
#define DESCRIPTOR_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define DESCRIPTOR_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define DESCRIPTOR_MEMORY_BASE 0x4002000
#define DESCRIPTOR_MEMORY_CONTENTS_INFO ""
#define DESCRIPTOR_MEMORY_DUAL_PORT 0
#define DESCRIPTOR_MEMORY_GUI_RAM_BLOCK_TYPE "Automatic"
#define DESCRIPTOR_MEMORY_INIT_CONTENTS_FILE "descriptor_memory"
#define DESCRIPTOR_MEMORY_INIT_MEM_CONTENT 1
#define DESCRIPTOR_MEMORY_INSTANCE_ID "NONE"
#define DESCRIPTOR_MEMORY_IRQ -1
#define DESCRIPTOR_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DESCRIPTOR_MEMORY_NAME "/dev/descriptor_memory"
#define DESCRIPTOR_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define DESCRIPTOR_MEMORY_RAM_BLOCK_TYPE "Auto"
#define DESCRIPTOR_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define DESCRIPTOR_MEMORY_SIZE_MULTIPLE 1
#define DESCRIPTOR_MEMORY_SIZE_VALUE 4096u
#define DESCRIPTOR_MEMORY_SPAN 4096
#define DESCRIPTOR_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define DESCRIPTOR_MEMORY_WRITABLE 1


/*
 * fft_pipeline_0 configuration
 *
 */

#define ALT_MODULE_CLASS_fft_pipeline_0 fft_pipeline
#define FFT_PIPELINE_0_BASE 0x4000000
#define FFT_PIPELINE_0_IRQ -1
#define FFT_PIPELINE_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FFT_PIPELINE_0_NAME "/dev/fft_pipeline_0"
#define FFT_PIPELINE_0_SPAN 8192
#define FFT_PIPELINE_0_TYPE "fft_pipeline"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK SYS_CLK_TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x4004880
#define JTAG_UART_IRQ 0
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 64
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * lcd_i2c_en configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_i2c_en altera_avalon_pio
#define LCD_I2C_EN_BASE 0x4004780
#define LCD_I2C_EN_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_I2C_EN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_I2C_EN_CAPTURE 0
#define LCD_I2C_EN_DATA_WIDTH 1
#define LCD_I2C_EN_DO_TEST_BENCH_WIRING 0
#define LCD_I2C_EN_DRIVEN_SIM_VALUE 0x0
#define LCD_I2C_EN_EDGE_TYPE "NONE"
#define LCD_I2C_EN_FREQ 100000000u
#define LCD_I2C_EN_HAS_IN 0
#define LCD_I2C_EN_HAS_OUT 1
#define LCD_I2C_EN_HAS_TRI 0
#define LCD_I2C_EN_IRQ -1
#define LCD_I2C_EN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_I2C_EN_IRQ_TYPE "NONE"
#define LCD_I2C_EN_NAME "/dev/lcd_i2c_en"
#define LCD_I2C_EN_RESET_VALUE 0x0
#define LCD_I2C_EN_SPAN 128
#define LCD_I2C_EN_TYPE "altera_avalon_pio"


/*
 * lcd_i2c_scl configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_i2c_scl altera_avalon_pio
#define LCD_I2C_SCL_BASE 0x4004700
#define LCD_I2C_SCL_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_I2C_SCL_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_I2C_SCL_CAPTURE 0
#define LCD_I2C_SCL_DATA_WIDTH 1
#define LCD_I2C_SCL_DO_TEST_BENCH_WIRING 0
#define LCD_I2C_SCL_DRIVEN_SIM_VALUE 0x0
#define LCD_I2C_SCL_EDGE_TYPE "NONE"
#define LCD_I2C_SCL_FREQ 100000000u
#define LCD_I2C_SCL_HAS_IN 0
#define LCD_I2C_SCL_HAS_OUT 1
#define LCD_I2C_SCL_HAS_TRI 0
#define LCD_I2C_SCL_IRQ -1
#define LCD_I2C_SCL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_I2C_SCL_IRQ_TYPE "NONE"
#define LCD_I2C_SCL_NAME "/dev/lcd_i2c_scl"
#define LCD_I2C_SCL_RESET_VALUE 0x0
#define LCD_I2C_SCL_SPAN 128
#define LCD_I2C_SCL_TYPE "altera_avalon_pio"


/*
 * lcd_i2c_sdat configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_i2c_sdat altera_avalon_pio
#define LCD_I2C_SDAT_BASE 0x4004800
#define LCD_I2C_SDAT_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_I2C_SDAT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_I2C_SDAT_CAPTURE 0
#define LCD_I2C_SDAT_DATA_WIDTH 1
#define LCD_I2C_SDAT_DO_TEST_BENCH_WIRING 0
#define LCD_I2C_SDAT_DRIVEN_SIM_VALUE 0x0
#define LCD_I2C_SDAT_EDGE_TYPE "NONE"
#define LCD_I2C_SDAT_FREQ 100000000u
#define LCD_I2C_SDAT_HAS_IN 0
#define LCD_I2C_SDAT_HAS_OUT 0
#define LCD_I2C_SDAT_HAS_TRI 1
#define LCD_I2C_SDAT_IRQ -1
#define LCD_I2C_SDAT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_I2C_SDAT_IRQ_TYPE "NONE"
#define LCD_I2C_SDAT_NAME "/dev/lcd_i2c_sdat"
#define LCD_I2C_SDAT_RESET_VALUE 0x0
#define LCD_I2C_SDAT_SPAN 128
#define LCD_I2C_SDAT_TYPE "altera_avalon_pio"


/*
 * lcd_sgdma configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_sgdma altera_avalon_sgdma
#define LCD_SGDMA_ADDRESS_WIDTH 32
#define LCD_SGDMA_ALWAYS_DO_MAX_BURST 1
#define LCD_SGDMA_ATLANTIC_CHANNEL_DATA_WIDTH 4
#define LCD_SGDMA_BASE 0x2000000
#define LCD_SGDMA_BURST_DATA_WIDTH 8
#define LCD_SGDMA_BURST_TRANSFER 0
#define LCD_SGDMA_BYTES_TO_TRANSFER_DATA_WIDTH 16
#define LCD_SGDMA_CHAIN_WRITEBACK_DATA_WIDTH 32
#define LCD_SGDMA_COMMAND_FIFO_DATA_WIDTH 104
#define LCD_SGDMA_CONTROL_DATA_WIDTH 8
#define LCD_SGDMA_CONTROL_SLAVE_ADDRESS_WIDTH 0x4
#define LCD_SGDMA_CONTROL_SLAVE_DATA_WIDTH 32
#define LCD_SGDMA_DESCRIPTOR_READ_BURST 0
#define LCD_SGDMA_DESC_DATA_WIDTH 32
#define LCD_SGDMA_HAS_READ_BLOCK 1
#define LCD_SGDMA_HAS_WRITE_BLOCK 0
#define LCD_SGDMA_IN_ERROR_WIDTH 0
#define LCD_SGDMA_IRQ 2
#define LCD_SGDMA_IRQ_INTERRUPT_CONTROLLER_ID 0
#define LCD_SGDMA_NAME "/dev/lcd_sgdma"
#define LCD_SGDMA_OUT_ERROR_WIDTH 0
#define LCD_SGDMA_READ_BLOCK_DATA_WIDTH 64
#define LCD_SGDMA_READ_BURSTCOUNT_WIDTH 4
#define LCD_SGDMA_SPAN 64
#define LCD_SGDMA_STATUS_TOKEN_DATA_WIDTH 24
#define LCD_SGDMA_STREAM_DATA_WIDTH 64
#define LCD_SGDMA_SYMBOLS_PER_BEAT 8
#define LCD_SGDMA_TYPE "altera_avalon_sgdma"
#define LCD_SGDMA_UNALIGNED_TRANSFER 0
#define LCD_SGDMA_WRITE_BLOCK_DATA_WIDTH 64
#define LCD_SGDMA_WRITE_BURSTCOUNT_WIDTH 4


/*
 * performance_counter configuration
 *
 */

#define ALT_MODULE_CLASS_performance_counter altera_avalon_performance_counter
#define PERFORMANCE_COUNTER_BASE 0x4004400
#define PERFORMANCE_COUNTER_HOW_MANY_SECTIONS 3
#define PERFORMANCE_COUNTER_IRQ -1
#define PERFORMANCE_COUNTER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PERFORMANCE_COUNTER_NAME "/dev/performance_counter"
#define PERFORMANCE_COUNTER_SPAN 512
#define PERFORMANCE_COUNTER_TYPE "altera_avalon_performance_counter"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altmemddr
#define SDRAM_BASE 0x0
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_SPAN 33554432
#define SDRAM_TYPE "altmemddr"


/*
 * sdram configuration as viewed by lcd_sgdma_m_read
 *
 */

#define LCD_SGDMA_M_READ_SDRAM_BASE 0x0
#define LCD_SGDMA_M_READ_SDRAM_IRQ -1
#define LCD_SGDMA_M_READ_SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_SGDMA_M_READ_SDRAM_NAME "/dev/sdram"
#define LCD_SGDMA_M_READ_SDRAM_SPAN 33554432
#define LCD_SGDMA_M_READ_SDRAM_TYPE "altmemddr"


/*
 * sdram configuration as viewed by sgdma_rx_m_write
 *
 */

#define SGDMA_RX_M_WRITE_SDRAM_BASE 0x0
#define SGDMA_RX_M_WRITE_SDRAM_IRQ -1
#define SGDMA_RX_M_WRITE_SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SGDMA_RX_M_WRITE_SDRAM_NAME "/dev/sdram"
#define SGDMA_RX_M_WRITE_SDRAM_SPAN 33554432
#define SGDMA_RX_M_WRITE_SDRAM_TYPE "altmemddr"


/*
 * sdram configuration as viewed by sgdma_tx_m_read
 *
 */

#define SGDMA_TX_M_READ_SDRAM_BASE 0x0
#define SGDMA_TX_M_READ_SDRAM_IRQ -1
#define SGDMA_TX_M_READ_SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SGDMA_TX_M_READ_SDRAM_NAME "/dev/sdram"
#define SGDMA_TX_M_READ_SDRAM_SPAN 33554432
#define SGDMA_TX_M_READ_SDRAM_TYPE "altmemddr"


/*
 * sgdma_rx configuration
 *
 */

#define ALT_MODULE_CLASS_sgdma_rx altera_avalon_sgdma
#define SGDMA_RX_ADDRESS_WIDTH 32
#define SGDMA_RX_ALWAYS_DO_MAX_BURST 1
#define SGDMA_RX_ATLANTIC_CHANNEL_DATA_WIDTH 4
#define SGDMA_RX_BASE 0x4004900
#define SGDMA_RX_BURST_DATA_WIDTH 8
#define SGDMA_RX_BURST_TRANSFER 0
#define SGDMA_RX_BYTES_TO_TRANSFER_DATA_WIDTH 16
#define SGDMA_RX_CHAIN_WRITEBACK_DATA_WIDTH 32
#define SGDMA_RX_COMMAND_FIFO_DATA_WIDTH 104
#define SGDMA_RX_CONTROL_DATA_WIDTH 8
#define SGDMA_RX_CONTROL_SLAVE_ADDRESS_WIDTH 0x4
#define SGDMA_RX_CONTROL_SLAVE_DATA_WIDTH 32
#define SGDMA_RX_DESCRIPTOR_READ_BURST 0
#define SGDMA_RX_DESC_DATA_WIDTH 32
#define SGDMA_RX_HAS_READ_BLOCK 0
#define SGDMA_RX_HAS_WRITE_BLOCK 1
#define SGDMA_RX_IN_ERROR_WIDTH 6
#define SGDMA_RX_IRQ 1
#define SGDMA_RX_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SGDMA_RX_NAME "/dev/sgdma_rx"
#define SGDMA_RX_OUT_ERROR_WIDTH 0
#define SGDMA_RX_READ_BLOCK_DATA_WIDTH 32
#define SGDMA_RX_READ_BURSTCOUNT_WIDTH 4
#define SGDMA_RX_SPAN 64
#define SGDMA_RX_STATUS_TOKEN_DATA_WIDTH 24
#define SGDMA_RX_STREAM_DATA_WIDTH 32
#define SGDMA_RX_SYMBOLS_PER_BEAT 4
#define SGDMA_RX_TYPE "altera_avalon_sgdma"
#define SGDMA_RX_UNALIGNED_TRANSFER 0
#define SGDMA_RX_WRITE_BLOCK_DATA_WIDTH 32
#define SGDMA_RX_WRITE_BURSTCOUNT_WIDTH 4


/*
 * sgdma_tx configuration
 *
 */

#define ALT_MODULE_CLASS_sgdma_tx altera_avalon_sgdma
#define SGDMA_TX_ADDRESS_WIDTH 32
#define SGDMA_TX_ALWAYS_DO_MAX_BURST 1
#define SGDMA_TX_ATLANTIC_CHANNEL_DATA_WIDTH 4
#define SGDMA_TX_BASE 0x4004940
#define SGDMA_TX_BURST_DATA_WIDTH 8
#define SGDMA_TX_BURST_TRANSFER 0
#define SGDMA_TX_BYTES_TO_TRANSFER_DATA_WIDTH 16
#define SGDMA_TX_CHAIN_WRITEBACK_DATA_WIDTH 32
#define SGDMA_TX_COMMAND_FIFO_DATA_WIDTH 104
#define SGDMA_TX_CONTROL_DATA_WIDTH 8
#define SGDMA_TX_CONTROL_SLAVE_ADDRESS_WIDTH 0x4
#define SGDMA_TX_CONTROL_SLAVE_DATA_WIDTH 32
#define SGDMA_TX_DESCRIPTOR_READ_BURST 0
#define SGDMA_TX_DESC_DATA_WIDTH 32
#define SGDMA_TX_HAS_READ_BLOCK 1
#define SGDMA_TX_HAS_WRITE_BLOCK 0
#define SGDMA_TX_IN_ERROR_WIDTH 0
#define SGDMA_TX_IRQ 3
#define SGDMA_TX_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SGDMA_TX_NAME "/dev/sgdma_tx"
#define SGDMA_TX_OUT_ERROR_WIDTH 1
#define SGDMA_TX_READ_BLOCK_DATA_WIDTH 32
#define SGDMA_TX_READ_BURSTCOUNT_WIDTH 4
#define SGDMA_TX_SPAN 64
#define SGDMA_TX_STATUS_TOKEN_DATA_WIDTH 24
#define SGDMA_TX_STREAM_DATA_WIDTH 32
#define SGDMA_TX_SYMBOLS_PER_BEAT 4
#define SGDMA_TX_TYPE "altera_avalon_sgdma"
#define SGDMA_TX_UNALIGNED_TRANSFER 0
#define SGDMA_TX_WRITE_BLOCK_DATA_WIDTH 32
#define SGDMA_TX_WRITE_BURSTCOUNT_WIDTH 4


/*
 * sys_clk_timer configuration
 *
 */

#define ALT_MODULE_CLASS_sys_clk_timer altera_avalon_timer
#define SYS_CLK_TIMER_ALWAYS_RUN 0
#define SYS_CLK_TIMER_BASE 0x4004600
#define SYS_CLK_TIMER_COUNTER_SIZE 32
#define SYS_CLK_TIMER_FIXED_PERIOD 0
#define SYS_CLK_TIMER_FREQ 100000000u
#define SYS_CLK_TIMER_IRQ 8
#define SYS_CLK_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYS_CLK_TIMER_LOAD_VALUE 99999ull
#define SYS_CLK_TIMER_MULT 0.0010
#define SYS_CLK_TIMER_NAME "/dev/sys_clk_timer"
#define SYS_CLK_TIMER_PERIOD 1
#define SYS_CLK_TIMER_PERIOD_UNITS "ms"
#define SYS_CLK_TIMER_RESET_OUTPUT 0
#define SYS_CLK_TIMER_SNAPSHOT 1
#define SYS_CLK_TIMER_SPAN 256
#define SYS_CLK_TIMER_TICKS_PER_SEC 1000u
#define SYS_CLK_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYS_CLK_TIMER_TYPE "altera_avalon_timer"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid
#define SYSID_BASE 0x40048c0
#define SYSID_ID 0u
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 64
#define SYSID_TIMESTAMP 1330299125u
#define SYSID_TYPE "altera_avalon_sysid"


/*
 * tse_mac configuration
 *
 */

#define ALT_MODULE_CLASS_tse_mac triple_speed_ethernet
#define TSE_MAC_BASE 0x4004000
#define TSE_MAC_ENABLE_MACLITE 0
#define TSE_MAC_FIFO_WIDTH 32
#define TSE_MAC_IRQ -1
#define TSE_MAC_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TSE_MAC_IS_MULTICHANNEL_MAC 0
#define TSE_MAC_MACLITE_GIGE 0
#define TSE_MAC_MDIO_SHARED 0
#define TSE_MAC_NAME "/dev/tse_mac"
#define TSE_MAC_NUMBER_OF_CHANNEL 1
#define TSE_MAC_NUMBER_OF_MAC_MDIO_SHARED 1
#define TSE_MAC_PCS 0
#define TSE_MAC_PCS_ID 0u
#define TSE_MAC_PCS_SGMII 0
#define TSE_MAC_RECEIVE_FIFO_DEPTH 1024
#define TSE_MAC_REGISTER_SHARED 0
#define TSE_MAC_SPAN 1024
#define TSE_MAC_TRANSMIT_FIFO_DEPTH 1024
#define TSE_MAC_TYPE "triple_speed_ethernet"
#define TSE_MAC_UNASSIGNED "unassigned"
#define TSE_MAC_USE_MDIO 1

#endif /* __SYSTEM_H_ */
