/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2007 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
******************************************************************************/

/*
 * Configuration register read/write API for the Toppoly TPG 110 TFT LCD 
 * included in the Altera Embedded Evaluation Kit.
 * 
 * This software emulates a two wire (three with clock) serial interface
 * to read and write configuration registers in the TFT display to set
 * resolution, gamma curve, contrast, and other items. For register 
 * descriptions and the meaning of the values read or written, please
 * refer to the TFT manufacturer's datasheet.
 * 
 * FAQ:
 *   Q: Do I have to use this in my application that uses the TFT on the 
 *      Embedded Evaluation Kit (EEK) hardware?
 * 
 *   A: Not necessarily. If you are using the display in its default (800x480)
 *      resolution and are displaying simple colors or graphics, along with
 *      hardware in the "video pipeline" of the EEK example designs featuring
 *      the TFT, then the default register contents in the display are often
 *      adequate for use.
 * 
 *   Q: Then when should I use this?
 * 
 *   A: If you wish to display images such as Bitmap or JPEG photos
 *      on the display, the register writes performed by this software's 
 *      "init" routine will write a gamma curve to the LCD that corrects 
 *      contrast quite nicely. 
 * 
 *      Additionaly, the init() routine accepts screen resolution 
 *      specifications if your design uses a (supported) resolution other 
 *      than 800x480. You can fine-tune these by either modifying these 
 *      defaults, or performing additioal register reads and writes directly 
 *      to the display by refering to the TFT datasheet.
 * 
 *    Q: Does this mean that I can just change to a lower resolution to
 *       in my call to the init routine to save video frame buffer memory?
 *  
 *    A: No, the hardware design must also be changed. It is configured to
 *       deliver 800x480 frames to the TFT. Once the approrpriate components
 *       in SOPC Builder are changed, the design re-compiled, and a new 
 *       programming file downloaded to the FPGA, you can specify the new
 *       resolution to the init() routine to configure the LCD. You must
 *       also initialize the "alt_video_display" software with the new 
 *       resolution, so that its memory and DMA management software is
 *       properly configured.
 * 
 *    Q: What sorts of hardware do I need in my design to use this software?
 *  
 *    A: You'll need three one-bit PIO interfaces. Two one-bit output-only
 *       PIOs and one bi-directional. These tie to the "SCEN" (chip enable), 
 *       "SCL" (clock), and "SDA" (bi-directional data), respectively. In
 *       the following example code, these PIOs were given names like 
 *       "lcd_2wire_scen". The base address for each PIO is defined in your 
 *       BSP's "system.h" file, and must be placed into an "alt_tpo_lcd"
 *       struct that you create and allocate in your application code.
 * 
 *    Q: Okay, how do I use this in my program?
 * 
 *    A: Here is an example:
 *       #include "alt_tpo_lcd.h"
 *       #include "system.h"
 *       #include "alt_types.h"
 * 
 *       #define LCD_WIDTH 800
 *       #define LCD_HEIGHT 480
 * 
 *       int main(void)
 *       {
 *         alt_tpo_lcd s_lcd;         // lcd configurator struct
 *         alt_tpo_lcd *lcd = &s_lcd; // struct pointer
 *         int result;
 *         alt_u8 data;
 * 
 *         // Specify base addresses of the each communication bus PIO,
 *         // as defined in system.h
 *         lcd->scen_pio = LCD_2WIRE_SCEN_BASE;
 *         lcd->scl_pio  = LCD_2WIRE_SCL_BASE;
 *         lcd->sda_pio  = LCD_2WIRE_SDA_BASE;
 * 
 *         // Write the default gamma curve, use 800x480 resolution (default),
 *         // and verify that the LCD is alive by reading back its Chip/ID 
 *         // register. Most users will only need to call this routine, and
 *         // verify that it completed successfully.
 *         result = alt_tpo_lcd_init(lcd, LCD_WIDTH, LCD_HEIGHT);
 *         if(result) {
 *            ... ; // failure
 *         } else {
 *            ...   // success
 *         }   
 * 
 *         // Example reads and writes:
 * 
 *         // Write "0x20" into register address "0xD"
 *         alt_tpo_lcd_write_config_register(lcd, 0xD, 0x20);
 * 
 *         // Read contents of register address "0xD"
 *         data = alt_tpo_lcd_read_config_register(lcd, 0xD);
 */

#include <unistd.h>
#include <stdio.h>

#include "sys/alt_irq.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_tpo_lcd.h"

/*
 * alt_tpo_lcd_prepare_serial_bus
 * 
 * Prepare 3-wire bus. This routine:
 * - Generates low-to-high transition on SCEN, 
 *   and then asserts it.
 * - Sets clock (SCL) low
 * - Sets SDA to drive output (from high-Z)
 */
void alt_tpo_lcd_prepare_serial_bus(alt_tpo_lcd *lcd)
{
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scen_pio, 0x1);
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x0);
  usleep(1);
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scen_pio, 0x0);
  IOWR_ALTERA_AVALON_PIO_DIRECTION(lcd->sda_pio, 
    ALTERA_AVALON_PIO_DIRECTION_OUTPUT);
  usleep(1); 
}

/* 
 * alt_tpo_lcd_cleanup_serial_bus
 * 
 * Restore 3-wire bus to safe state. This routine:
 * - Sets clock low & waits to conclude transmission
 * - Sets SDA from FPGA to high-Z
 * - Negates SCL/SCEN
 * - Does a final wait to allow-back-to-back register 
 *   operations via public API
 */
void alt_tpo_lcd_cleanup_serial_bus(alt_tpo_lcd *lcd)
{
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x0);
  usleep(1);
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scen_pio, 0x1);
  IOWR_ALTERA_AVALON_PIO_DIRECTION(lcd->sda_pio,
    ALTERA_AVALON_PIO_DIRECTION_INPUT);
  usleep(1);
}


/*
 * alt_tpo_lcd_write_serial_bits
 * 
 * This routine writes the specified number of bits to the LCD
 * configuration interface. This routine is private and should not
 * be called outside of the general purpose register read/write
 * routines in this file.
 *
 * This routine assumes that chip select has been asserted,
 * approrpriate delay has passed, that interrupts are
 * disabled to guarantee a steady clock duty-cycle, and that
 * the SDA line is set for output.
 * 
 * This routine leaves the serial clock signal high, and the 
 * SDA line set for output.
 */
void alt_tpo_lcd_write_serial_bits(alt_tpo_lcd *lcd, int num_bits, alt_u8 data)
{
  alt_u8 to_transmit;
  
  while(num_bits--) {
    to_transmit = ((data >> num_bits) & 0x1);

    /* Set clock low; Write TX bit & wait */
    IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x0);
    IOWR_ALTERA_AVALON_PIO_DATA(lcd->sda_pio, to_transmit);
    usleep(1);
    
    /* Set clock high & wait */
    IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x1);
    usleep(1);
  }
}

/*
 * alt_tpo_lcd_read_serial_byte
 * 
 * This routine reads a data byte from the LCD serial configuration
 * interface. This routine is private and should not
 * be called outside of the general purpose register read/write
 * routines in this file.
 *
 * This routine assumes that chip select has been asserted,
 * approrpriate delay has passed, that interrupts are
 * disabled to guarantee a steady clock duty-cycle, and that
 * a 6-bit register address has already been clocked in.
 * 
 * This routine leaves the serial clock signal high, and
 * SDA data pin tri-stated.
 */
alt_u8 alt_tpo_lcd_read_serial_byte(alt_tpo_lcd *lcd)
{
  int i;
  alt_u8 read_data = 0x0;
  
  /* Write "1" to indicate that this is a read command & toggle clock */
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x0);
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->sda_pio, 0x1);
  usleep(1);
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x1);
  usleep(1);
   
  /* Set SDA PIO to High-Z state & toggle clock */
  IOWR_ALTERA_AVALON_PIO_DIRECTION(lcd->sda_pio, 
    ALTERA_AVALON_PIO_DIRECTION_INPUT);
  
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x0);
  usleep(1);
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x1);
  usleep(1);
  
  IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x0);
  usleep(1);

  
  /* Read in data byte */
  for(i=0; i<8; i++) {
    /* Read & shift data */
    read_data = read_data << 1;
    read_data |= (IORD_ALTERA_AVALON_PIO_DATA(lcd->sda_pio) & 0x01);
    
    /* Toggle clock & wait */
    IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x1);
    usleep(1);
    IOWR_ALTERA_AVALON_PIO_DATA(lcd->scl_pio, 0x0);
    usleep(1);
  }
  
  return read_data;
}

/*
 *  Function: alt_tpo_lcd_read_config_register
 *
 *  Purpose: This routine reads a configuration word from the LCD
 *           panel's serial interface port.
 *
 * The serial interface for LCD configuration is implemented with
 * three PIO peripherals, the base address of each is presumed to
 * be defined in the lcd configuration struct pointed to by *lcd.
 * 
 * Timing information:
 * A 160-ns pulse width is required for scl; 150ns setup and hold 
 * times for data transitions before/after the clock edge. Additionally,
 * a 1us-delay is required between successive commands (successive
 * calls to this routine). 
 * 
 * Because this routine is intended to be used only during initial setup, 
 * latency isn't critical; the usleep() routine is used to generate a 
 * predicable (if large) delay between each transition. This routine
 * may be immediatly called after it returns to write another register
 * in the LCD.
 * 
 * Arguments:
 *   *lcd: LCD configuration struct. This must be pre-populated with valid
 *         base addresses of the LCD communication PIOs.
 *   addr: byte containing 6-bit LCD configuration register address in LSBs
 * 
 * Return value:
 *   byte read from specified register address
 */
alt_u8 alt_tpo_lcd_read_config_register(alt_tpo_lcd *lcd, alt_u8 addr)
{
  alt_irq_context irq_state;
  alt_u8 read_data;
  
  alt_tpo_lcd_prepare_serial_bus(lcd);
    
  /* 
   * Disable interrupts. The LCD requires a 40-60% duty cycle on the
   * serial clock signal, which we can only guarantee if this routine
   * runs uninterrupted.
   */
  irq_state = alt_irq_disable_all();

  /* Transmit 6-bit address */
  alt_tpo_lcd_write_serial_bits(lcd, 6, addr);
  
  /* Do read */ 
  read_data = alt_tpo_lcd_read_serial_byte(lcd);
   
  /* Done. Restore previously enabled interrupts & clean-up bus */
  alt_irq_enable_all(irq_state);
  alt_tpo_lcd_cleanup_serial_bus(lcd);
  
  return read_data;
}

/*
 *  Function: alt_tpo_lcd_write_config_register
 *
 *  Purpose: This routine writes a configuration word to the LCD
 *           panel's serial interface port.
 *
 * The serial interface for LCD configuration is implemented with
 * three PIO peripherals, the base address of each is presumed to
 * be defined in the lcd configuration struct pointed to by *lcd.
 * 
 * Timing information:
 * A 160-ns pulse width is required for scl; 150ns setup and hold 
 * times for data transitions before/after the clock edge. Additionally,
 * a 1us-delay is required between successive commands (successive
 * calls to this routine). 
 * 
 * Because this routine is intended to be used only during initial setup, 
 * latency isn't critical; the usleep() routine is used to generate a 
 * predicable (if large) delay between each transition. This routine
 * may be immediatly called after it returns to write another register
 * in the LCD.
 * 
 * Arguments:
 *   *lcd: LCD configuration struct. This must be pre-populated with valid
 *         base addresses of the LCD communication PIOs 
 *   addr: byte containing 6-bit LCD configuration register address in LSBs
 *   data: byte to write
 */
void alt_tpo_lcd_write_config_register(alt_tpo_lcd *lcd, alt_u8 addr, alt_u8 data)
{
  alt_irq_context irq_state;
 
  alt_tpo_lcd_prepare_serial_bus(lcd);  
  
  /* 
   * Disable interrupts. The LCD requires a 40-60% duty cycle on the
   * serial clock signal, which we can only guarantee if this routine
   * runs uninterrupted.
   */
  irq_state = alt_irq_disable_all();
   
  /* Transmit:
   *  - 6-bit address
   *  - "00" to indicate write, (this would be "1" then high-Z turnaround 
   *    cycle for a read) 
   *  - 8-bit data
   */
  alt_tpo_lcd_write_serial_bits(lcd, 6, addr);
  alt_tpo_lcd_write_serial_bits(lcd, 2, (alt_u8) 0x0);
  alt_tpo_lcd_write_serial_bits(lcd, 8, data);
    
  /* Done. Restore previously enabled interrupts & clean-up bus */
  alt_irq_enable_all(irq_state);
  alt_tpo_lcd_cleanup_serial_bus(lcd);
}

/******************************************************************
*  Function: alt_tpo_lcd_init
*
*  Purpose: This routine configures the LCD panel through its
*           serial interface port.
*
******************************************************************/
int alt_tpo_lcd_init(alt_tpo_lcd *lcd, alt_u32 width, alt_u32 height)
{
  alt_u8 data;

  /* Gamma curve */
  unsigned short gamma[12] = 
    { 106, 200, 289, 375, 460, 543, 625, 705, 785, 864, 942, 1020 };  

  /* Sanity check: Read Chip ID/Version */
  data = alt_tpo_lcd_read_config_register(lcd, ALT_TPO_LCD_ADDR_CHIP_ID);

  /* Mask off "version" bits to only examine chip ID. Chip ID is high nibble */
  data &= ALT_TPO_LCD_CHIP_ID_MASK;

  if(data != ALT_TPO_LCD_CHIP_ID) {
    printf("[alt_tpo_lcd_init] Warning: Read incorrect chip ID.\n");
    printf("--> Expected 0x%x, read 0x%x\n", ALT_TPO_LCD_CHIP_ID, data);
    printf("--> The gamma curve or other LCD register writes may not succeed.\n");
  }
 
  /* Enable software-writable resolution. */
  data = alt_tpo_lcd_read_config_register(lcd, ALT_TPO_LCD_ADDR_RES_SEL_STBY);
  data |= 0x80; /* Bit 7 = Enable SW control for resolution */
  alt_tpo_lcd_write_config_register(lcd, ALT_TPO_LCD_ADDR_RES_SEL_STBY, data);
 
  /* Set resolution */
  if(width == 800 && height == 480) {
    alt_tpo_lcd_write_config_register(
      lcd, ALT_TPO_LCD_ADDR_RESOLUTION, (alt_u8) 0x7);
  }
  else if(width == 640 && height == 480) {
    alt_tpo_lcd_write_config_register(
      lcd, ALT_TPO_LCD_ADDR_RESOLUTION, (alt_u8) 0x6);
  }
  else if(width == 480 && height == 272) {
    alt_tpo_lcd_write_config_register(
      lcd, ALT_TPO_LCD_ADDR_RESOLUTION, (alt_u8) 0x5);
  } 
  else {
    printf("[alt_tpo_lcd_init] Error: Width & height not supported.\n");
    printf("--> This software supports 800x480, 640x480, or 480x272\n");
    return -1;
  }
 
  /* 
   * Write gamma curve 
   * 
   * Registers in the address range 0x11..0x13 contain the two MSBs of each
   * 10-bit gamma value. This is derived from manufacturer's datasheet.
   */
  alt_tpo_lcd_write_config_register(lcd , 0x11, (alt_u8)
            ( ((gamma[0] & 0x300) >> 2) | 
              ((gamma[1] & 0x300) >> 4) | 
              ((gamma[2] & 0x300) >> 6) | 
              ((gamma[3] & 0x300) >> 8 )  ) );
             
  alt_tpo_lcd_write_config_register(lcd, 0x12, (alt_u8)
            ( ((gamma[4] & 0x300) >> 2) | 
              ((gamma[5] & 0x300) >> 4) | 
              ((gamma[6] & 0x300) >> 6) | 
              ((gamma[7] & 0x300) >> 8 )  ) );
             
  alt_tpo_lcd_write_config_register(lcd, 0x13, (alt_u8)
            ( ((gamma[8]  & 0x300) >> 2) | 
              ((gamma[9]  & 0x300) >> 4) | 
              ((gamma[10] & 0x300) >> 6) | 
              ((gamma[11] & 0x300) >> 8 )  ) );
  
  /* 
   * Register addresses 0x14..0x1f contain 8-bit gamma values.
   */
  alt_tpo_lcd_write_config_register(lcd, 0x14, (alt_u8)( gamma[0] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x15, (alt_u8)( gamma[1] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x16, (alt_u8)( gamma[2] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x17, (alt_u8)( gamma[3] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x18, (alt_u8)( gamma[4] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x19, (alt_u8)( gamma[5] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x1a, (alt_u8)( gamma[6] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x1b, (alt_u8)( gamma[7] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x1c, (alt_u8)( gamma[8] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x1d, (alt_u8)( gamma[9] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x1e, (alt_u8)( gamma[10] & 0xFF ) );
  alt_tpo_lcd_write_config_register(lcd, 0x1f, (alt_u8)( gamma[11] & 0xFF ) );
  
  /*
   * Register address 0x20 controls the "voltage range for
   * positive polarity" (and negative polarity, for 0x21).
   *   High nibble defines DAC reference voltage for "code 0xFF"
   *   Low nibble defines DAC reference voltage for "code 0x00"
   */
  alt_tpo_lcd_write_config_register(lcd, 0x20, (alt_u8) 0xF0);
  alt_tpo_lcd_write_config_register(lcd, 0x21, (alt_u8) 0xF0);
  
  return 0;
}
