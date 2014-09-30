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
#ifndef __ALT_TPO_LCD_H__
#define __ALT_TPO_LCD_H__

#include "alt_types.h"

#define ALT_TPO_LCD_ADDR_CHIP_ID 0x1
#define ALT_TPO_LCD_ADDR_RESOLUTION 0x2
#define ALT_TPO_LCD_ADDR_RES_SEL_STBY 0x03

#define ALT_TPO_LCD_CHIP_ID 0xC0
#define ALT_TPO_LCD_CHIP_ID_MASK 0xF0

typedef struct alt_tpo_lcd
{
  alt_u32 scen_pio;
  alt_u32 scl_pio;
  alt_u32 sda_pio;
} alt_tpo_lcd;

/*
 * Prototypes for public API 
 */
void alt_tpo_lcd_write_config_register(
   alt_tpo_lcd *lcd, alt_u8 addr, alt_u8 data);
                                       
alt_u8 alt_tpo_lcd_read_config_register(
  alt_tpo_lcd *lcd, alt_u8 addr);

int alt_tpo_lcd_init(alt_tpo_lcd *lcd, alt_u32 width, alt_u32 height);

#endif /* __ALT_TPO_LCD_H__*/
