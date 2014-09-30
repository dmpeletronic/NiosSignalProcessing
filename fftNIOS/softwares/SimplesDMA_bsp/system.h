/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpuNios' in SOPC Builder design 'processador'
 * SOPC Builder design path: C:/altera/Projetos/fftNIOS/processador.sopcinfo
 *
 * Generated: Fri Nov 04 23:14:25 BRST 2011
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
#define ALT_CPU_BREAK_ADDR 0x4000820
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x0
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1b
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x20
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 1
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x1b
#define ALT_CPU_NAME "cpuNios"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x0


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x4000820
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x0
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1b
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x20
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 1
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x1b
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x0


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SGDMA
#define __ALTERA_AVALON_SYSID
#define __ALTERA_AVALON_TIMER
#define __ALTERA_AVALON_UART
#define __ALTERA_NIOS2
#define __ALTMEMDDR


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
#define ALT_STDERR_BASE 0x4001200
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x4001200
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x4001200
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "processador"


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
#define JTAG_UART_BASE 0x4001200
#define JTAG_UART_IRQ 0
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 16
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * lcd_i2c_en configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_i2c_en altera_avalon_pio
#define LCD_I2C_EN_BASE 0x4001160
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
#define LCD_I2C_EN_SPAN 32
#define LCD_I2C_EN_TYPE "altera_avalon_pio"


/*
 * lcd_i2c_scl configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_i2c_scl altera_avalon_pio
#define LCD_I2C_SCL_BASE 0x4001140
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
#define LCD_I2C_SCL_SPAN 32
#define LCD_I2C_SCL_TYPE "altera_avalon_pio"


/*
 * lcd_i2c_sdat configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_i2c_sdat altera_avalon_pio
#define LCD_I2C_SDAT_BASE 0x4001180
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
#define LCD_I2C_SDAT_SPAN 32
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
 * pixel_data configuration
 *
 */

#define ALT_MODULE_CLASS_pixel_data altera_avalon_pio
#define PIXEL_DATA_BASE 0x40011c0
#define PIXEL_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define PIXEL_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIXEL_DATA_CAPTURE 0
#define PIXEL_DATA_DATA_WIDTH 8
#define PIXEL_DATA_DO_TEST_BENCH_WIRING 0
#define PIXEL_DATA_DRIVEN_SIM_VALUE 0x0
#define PIXEL_DATA_EDGE_TYPE "NONE"
#define PIXEL_DATA_FREQ 100000000u
#define PIXEL_DATA_HAS_IN 0
#define PIXEL_DATA_HAS_OUT 1
#define PIXEL_DATA_HAS_TRI 0
#define PIXEL_DATA_IRQ -1
#define PIXEL_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIXEL_DATA_IRQ_TYPE "NONE"
#define PIXEL_DATA_NAME "/dev/pixel_data"
#define PIXEL_DATA_RESET_VALUE 0x0
#define PIXEL_DATA_SPAN 32
#define PIXEL_DATA_TYPE "altera_avalon_pio"


/*
 * pixel_in configuration
 *
 */

#define ALT_MODULE_CLASS_pixel_in altera_avalon_pio
#define PIXEL_IN_BASE 0x40011e0
#define PIXEL_IN_BIT_CLEARING_EDGE_REGISTER 0
#define PIXEL_IN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIXEL_IN_CAPTURE 0
#define PIXEL_IN_DATA_WIDTH 32
#define PIXEL_IN_DO_TEST_BENCH_WIRING 0
#define PIXEL_IN_DRIVEN_SIM_VALUE 0x0
#define PIXEL_IN_EDGE_TYPE "NONE"
#define PIXEL_IN_FREQ 100000000u
#define PIXEL_IN_HAS_IN 1
#define PIXEL_IN_HAS_OUT 0
#define PIXEL_IN_HAS_TRI 0
#define PIXEL_IN_IRQ -1
#define PIXEL_IN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIXEL_IN_IRQ_TYPE "NONE"
#define PIXEL_IN_NAME "/dev/pixel_in"
#define PIXEL_IN_RESET_VALUE 0x0
#define PIXEL_IN_SPAN 32
#define PIXEL_IN_TYPE "altera_avalon_pio"


/*
 * pixel_pos configuration
 *
 */

#define ALT_MODULE_CLASS_pixel_pos altera_avalon_pio
#define PIXEL_POS_BASE 0x40011a0
#define PIXEL_POS_BIT_CLEARING_EDGE_REGISTER 0
#define PIXEL_POS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIXEL_POS_CAPTURE 0
#define PIXEL_POS_DATA_WIDTH 8
#define PIXEL_POS_DO_TEST_BENCH_WIRING 0
#define PIXEL_POS_DRIVEN_SIM_VALUE 0x0
#define PIXEL_POS_EDGE_TYPE "NONE"
#define PIXEL_POS_FREQ 100000000u
#define PIXEL_POS_HAS_IN 0
#define PIXEL_POS_HAS_OUT 1
#define PIXEL_POS_HAS_TRI 0
#define PIXEL_POS_IRQ -1
#define PIXEL_POS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIXEL_POS_IRQ_TYPE "NONE"
#define PIXEL_POS_NAME "/dev/pixel_pos"
#define PIXEL_POS_RESET_VALUE 0x0
#define PIXEL_POS_SPAN 32
#define PIXEL_POS_TYPE "altera_avalon_pio"


/*
 * portA configuration
 *
 */

#define ALT_MODULE_CLASS_portA altera_avalon_pio
#define PORTA_BASE 0x4001040
#define PORTA_BIT_CLEARING_EDGE_REGISTER 0
#define PORTA_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PORTA_CAPTURE 0
#define PORTA_DATA_WIDTH 32
#define PORTA_DO_TEST_BENCH_WIRING 0
#define PORTA_DRIVEN_SIM_VALUE 0x0
#define PORTA_EDGE_TYPE "NONE"
#define PORTA_FREQ 100000000u
#define PORTA_HAS_IN 0
#define PORTA_HAS_OUT 1
#define PORTA_HAS_TRI 0
#define PORTA_IRQ -1
#define PORTA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PORTA_IRQ_TYPE "NONE"
#define PORTA_NAME "/dev/portA"
#define PORTA_RESET_VALUE 0x0
#define PORTA_SPAN 64
#define PORTA_TYPE "altera_avalon_pio"


/*
 * porta_serial configuration
 *
 */

#define ALT_MODULE_CLASS_porta_serial altera_avalon_uart
#define PORTA_SERIAL_BASE 0x4001080
#define PORTA_SERIAL_BAUD 115200
#define PORTA_SERIAL_DATA_BITS 8
#define PORTA_SERIAL_FIXED_BAUD 1
#define PORTA_SERIAL_FREQ 100000000u
#define PORTA_SERIAL_IRQ 9
#define PORTA_SERIAL_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PORTA_SERIAL_NAME "/dev/porta_serial"
#define PORTA_SERIAL_PARITY 'N'
#define PORTA_SERIAL_SIM_CHAR_STREAM ""
#define PORTA_SERIAL_SIM_TRUE_BAUD 0
#define PORTA_SERIAL_SPAN 64
#define PORTA_SERIAL_STOP_BITS 1
#define PORTA_SERIAL_SYNC_REG_DEPTH 2
#define PORTA_SERIAL_TYPE "altera_avalon_uart"
#define PORTA_SERIAL_USE_CTS_RTS 0
#define PORTA_SERIAL_USE_EOP_REGISTER 0


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
 * sdram configuration as viewed by sgdma_mm_to_st_m_read
 *
 */

#define SGDMA_MM_TO_ST_M_READ_SDRAM_BASE 0x0
#define SGDMA_MM_TO_ST_M_READ_SDRAM_IRQ -1
#define SGDMA_MM_TO_ST_M_READ_SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SGDMA_MM_TO_ST_M_READ_SDRAM_NAME "/dev/sdram"
#define SGDMA_MM_TO_ST_M_READ_SDRAM_SPAN 33554432
#define SGDMA_MM_TO_ST_M_READ_SDRAM_TYPE "altmemddr"


/*
 * sdram configuration as viewed by sgdma_st_to_mm_m_write
 *
 */

#define SGDMA_ST_TO_MM_M_WRITE_SDRAM_BASE 0x0
#define SGDMA_ST_TO_MM_M_WRITE_SDRAM_IRQ -1
#define SGDMA_ST_TO_MM_M_WRITE_SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SGDMA_ST_TO_MM_M_WRITE_SDRAM_NAME "/dev/sdram"
#define SGDMA_ST_TO_MM_M_WRITE_SDRAM_SPAN 33554432
#define SGDMA_ST_TO_MM_M_WRITE_SDRAM_TYPE "altmemddr"


/*
 * sgdma_mm_to_st configuration
 *
 */

#define ALT_MODULE_CLASS_sgdma_mm_to_st altera_avalon_sgdma
#define SGDMA_MM_TO_ST_ADDRESS_WIDTH 32
#define SGDMA_MM_TO_ST_ALWAYS_DO_MAX_BURST 1
#define SGDMA_MM_TO_ST_ATLANTIC_CHANNEL_DATA_WIDTH 4
#define SGDMA_MM_TO_ST_BASE 0x40010c0
#define SGDMA_MM_TO_ST_BURST_DATA_WIDTH 8
#define SGDMA_MM_TO_ST_BURST_TRANSFER 0
#define SGDMA_MM_TO_ST_BYTES_TO_TRANSFER_DATA_WIDTH 16
#define SGDMA_MM_TO_ST_CHAIN_WRITEBACK_DATA_WIDTH 32
#define SGDMA_MM_TO_ST_COMMAND_FIFO_DATA_WIDTH 104
#define SGDMA_MM_TO_ST_CONTROL_DATA_WIDTH 8
#define SGDMA_MM_TO_ST_CONTROL_SLAVE_ADDRESS_WIDTH 0x4
#define SGDMA_MM_TO_ST_CONTROL_SLAVE_DATA_WIDTH 32
#define SGDMA_MM_TO_ST_DESCRIPTOR_READ_BURST 0
#define SGDMA_MM_TO_ST_DESC_DATA_WIDTH 32
#define SGDMA_MM_TO_ST_HAS_READ_BLOCK 1
#define SGDMA_MM_TO_ST_HAS_WRITE_BLOCK 0
#define SGDMA_MM_TO_ST_IN_ERROR_WIDTH 0
#define SGDMA_MM_TO_ST_IRQ 1
#define SGDMA_MM_TO_ST_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SGDMA_MM_TO_ST_NAME "/dev/sgdma_mm_to_st"
#define SGDMA_MM_TO_ST_OUT_ERROR_WIDTH 0
#define SGDMA_MM_TO_ST_READ_BLOCK_DATA_WIDTH 32
#define SGDMA_MM_TO_ST_READ_BURSTCOUNT_WIDTH 4
#define SGDMA_MM_TO_ST_SPAN 64
#define SGDMA_MM_TO_ST_STATUS_TOKEN_DATA_WIDTH 24
#define SGDMA_MM_TO_ST_STREAM_DATA_WIDTH 32
#define SGDMA_MM_TO_ST_SYMBOLS_PER_BEAT 4
#define SGDMA_MM_TO_ST_TYPE "altera_avalon_sgdma"
#define SGDMA_MM_TO_ST_UNALIGNED_TRANSFER 0
#define SGDMA_MM_TO_ST_WRITE_BLOCK_DATA_WIDTH 32
#define SGDMA_MM_TO_ST_WRITE_BURSTCOUNT_WIDTH 4


/*
 * sgdma_st_to_mm configuration
 *
 */

#define ALT_MODULE_CLASS_sgdma_st_to_mm altera_avalon_sgdma
#define SGDMA_ST_TO_MM_ADDRESS_WIDTH 32
#define SGDMA_ST_TO_MM_ALWAYS_DO_MAX_BURST 1
#define SGDMA_ST_TO_MM_ATLANTIC_CHANNEL_DATA_WIDTH 4
#define SGDMA_ST_TO_MM_BASE 0x4001100
#define SGDMA_ST_TO_MM_BURST_DATA_WIDTH 8
#define SGDMA_ST_TO_MM_BURST_TRANSFER 0
#define SGDMA_ST_TO_MM_BYTES_TO_TRANSFER_DATA_WIDTH 16
#define SGDMA_ST_TO_MM_CHAIN_WRITEBACK_DATA_WIDTH 32
#define SGDMA_ST_TO_MM_COMMAND_FIFO_DATA_WIDTH 104
#define SGDMA_ST_TO_MM_CONTROL_DATA_WIDTH 8
#define SGDMA_ST_TO_MM_CONTROL_SLAVE_ADDRESS_WIDTH 0x4
#define SGDMA_ST_TO_MM_CONTROL_SLAVE_DATA_WIDTH 32
#define SGDMA_ST_TO_MM_DESCRIPTOR_READ_BURST 0
#define SGDMA_ST_TO_MM_DESC_DATA_WIDTH 32
#define SGDMA_ST_TO_MM_HAS_READ_BLOCK 0
#define SGDMA_ST_TO_MM_HAS_WRITE_BLOCK 1
#define SGDMA_ST_TO_MM_IN_ERROR_WIDTH 0
#define SGDMA_ST_TO_MM_IRQ 5
#define SGDMA_ST_TO_MM_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SGDMA_ST_TO_MM_NAME "/dev/sgdma_st_to_mm"
#define SGDMA_ST_TO_MM_OUT_ERROR_WIDTH 0
#define SGDMA_ST_TO_MM_READ_BLOCK_DATA_WIDTH 32
#define SGDMA_ST_TO_MM_READ_BURSTCOUNT_WIDTH 4
#define SGDMA_ST_TO_MM_SPAN 64
#define SGDMA_ST_TO_MM_STATUS_TOKEN_DATA_WIDTH 24
#define SGDMA_ST_TO_MM_STREAM_DATA_WIDTH 32
#define SGDMA_ST_TO_MM_SYMBOLS_PER_BEAT 4
#define SGDMA_ST_TO_MM_TYPE "altera_avalon_sgdma"
#define SGDMA_ST_TO_MM_UNALIGNED_TRANSFER 0
#define SGDMA_ST_TO_MM_WRITE_BLOCK_DATA_WIDTH 32
#define SGDMA_ST_TO_MM_WRITE_BURSTCOUNT_WIDTH 4


/*
 * sys_clk_timer configuration
 *
 */

#define ALT_MODULE_CLASS_sys_clk_timer altera_avalon_timer
#define SYS_CLK_TIMER_ALWAYS_RUN 0
#define SYS_CLK_TIMER_BASE 0x4001000
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
#define SYS_CLK_TIMER_SPAN 64
#define SYS_CLK_TIMER_TICKS_PER_SEC 1000u
#define SYS_CLK_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYS_CLK_TIMER_TYPE "altera_avalon_timer"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid
#define SYSID_BASE 0x4001210
#define SYSID_ID 0u
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 16
#define SYSID_TIMESTAMP 1319681383u
#define SYSID_TYPE "altera_avalon_sysid"

#endif /* __SYSTEM_H_ */
