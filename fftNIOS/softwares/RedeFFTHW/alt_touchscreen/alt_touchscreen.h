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
#ifndef __ALT_TOUCHSCREEN_H_DEFINED
#define __ALT_TOUCHSCREEN_H_DEFINED
/*****************************************************************
 *
 * alt_touchscreen 
 * 
 * 
 * OVERVIEW
 *
 * This is an API for managing the touch-screen on the Embedded
 * Evaluation Kit LCD daughtercard.
 * 
 * You call a few simple routines to initialize the subsystem, and
 * then get the current pen-state and location. 
 * 
 * You can register a call-back function for pen-up and pen-down
 * events.
 *
 * API SUMMARY
 *
 * There are five ultra-simple functions you call to interact with
 * your touchscreen
 *
 *       alt_touchscreen_init()
 *       alt_touchscreen_stop()
 *       alt_touchscreen_get_pen()
 *       alt_touchscreen_event_loop_update()
 *       alt_touchscreen_register_callback_func()
 *
 *
 * "init" & "stop" are simple enough that you can just look at the
 * comment next to their declarations.  "get_pen" is pretty
 * straightforward, too. 
 * 
 * The interesting things to say about "get_pen" are:
 *        1) It returns a full, coherent sample: X, Y, and pen-state,
 *           by reference.
 * 
 *        2) It's "hardened" against ISR-synchronization issues.
 * 
 *        3) It's absurdly CPU-efficient, because it doesn't really do
 *           any work.  It just pulls three numbers out of the 
 *           alt_touch_screen struct and hands them back to you.
 *
 *  The "register_callback_func" interface allow you to
 *  drive your application from pen-actions--a very common thing to
 *  do.  Passing-in the magic value "NULL" for your func-pointer 
 *  un-registers your callback.
 *  
 *  The "event_loop_update" is actually a little bit interesting.
 *  If you are a civilized human being with an actual operating
 *  system, you should set this function to run in a thread which is
 *  woken by a 60Hz timer.  If you are some sort of barbaric cave-man,
 *  you can call this function in your application's primitive "while (1)" 
 *  "main" loop.  Ook.  If you don't call this function in your
 *  application's event-loop, then your pen-up and/or pen-down
 *  callbacks will never get triggered.  Happily: this funciton, too,
 *  does almost no work.  All it does is call your application's
 *  pen-up/down callback-function, if you registered one, and if the
 *  pen happened to go up-or-down.  If you registered no function, or
 *  if the pen is going neither up nor down, then it does nothing.
 *  
 *  The reason we need an "event_loop_update" function is so that your
 *  pen-up/down callback is not called in an ISR-context because
 *  (typically) a pen-up or pen-down causes your application to go off
 *  and run a large body of "mainline" non-real-time application code.
 * 
 * 
 *  CALLBACKS and APPLICATION CONTEXT
 * 
 *      <watch this space for a large comment>
 *  
 *  SCALING and CALIBRATION
 * 
 *      <watch this space for a large comment>
 * 
 *
 * PHYSICAL HARDWARE
 * 
 * The physical hardware is composed of three parts: 
 * 
 *    1) The actual resistive touch-screen overlayed on the LCD
 *       display.  This is part of the Topploy XXX module.  The
 *       interface to the actual sensor-element is four analog signals
 *       which appear on the display-module's connector.  The FPGA
 *       does not connect directly to these signals.
 * 
 *    2) An Analog Devices 7843 Touch Screen Digitizer chip, which
 *       connects directly to the analog signals on the sensor and
 *       presents a digital interface (SPI protocol) to the FPGA. 
 *       the AD7843 resides on the daughtercard. Its SPI-port connects
 *       to FPGA I/O pins via the daughtercard connector.
 * 
 *    3) An ordinary SPI peripheral IP component in the FPGA, which is
 *       seen by the Nios as an Avalon slave.  Software (this
 *       software) running on Nios sends commands to, and gets data
 *       from, the AD7843 (and, thus, the sensor) via this SPI
 *       interface.
 *
 *  Hardware limitations:
 *
 *     There is one particular limitation of the LCD daughtercard
 *     which has a strong influence on the form of this software: Some
 *     fool soldered a giant capacitor on the analog sensor wires.
 *     This creates a loooong time-constant on the sensor-circuit, and
 *     necessitates a sloooow sampling-cycle.   The sampling-cycle
 *     happens to be controlled by the SPI clock-rate--which means we
 *     must run the SPI interface at a very-slow speed.    
 * 
 *     Experiments indicate you can run the SPI clock up to about
 *     32KHz, but you might get better data if you run it slower.
 *     Running it at 8KHz gave frighteningly-good data.
 * 
 *     Ideally, the SPI interface would run at a couple of megaherz.
 *     The AD7843 (sans capacitor) can run its SPI-port (and
 *     sampling-circuit) at 2MHz.  
 *
 *     Unfortunately, this means sending commands (and getting data)
 *     from the SPI peripheral will be SLOW.  This software is built
 *     to take this into account, and not waste CPU-cycles
 *     waiting-around for slow SPI-transactions and analog settling-times.
 *
 * PRINCIPLES of OPERATION
 * 
 *   Basic Idea
 *
 *     The basic concept is simplicity itself: We register a 60Hz
 *     timer-callback.   The timer-callback sends a sample-command to
 *     the AD7843 over the SPI port.  The timer-callback just launches
 *     the command and doesn't wait-around for the SPI transaction to
 *     complete.  It just writes the command to the SPI-controller and
 *     exits.  The timer-callback should execute in a handful of CPU
 *     clock-cycles. 
 *
 *     The SPI peripheral is set-up in interrupt mode.  When the SPI
 *     transaction (launched by the 60Hz timer-callback) completes,
 *     the CPU will get an interrupt from the SPI, meaning: "The
 *     transaction is complete, and you can come and pick up your
 *     data."
 * 
 *     The SPI interrupt-service routine then grabs the data from the
 *     SPI peripheral.  This data represents the most-recent sample,
 *     gathered ever-so-slowly and ever-so-carefully whist the CPU was
 *     off doing useful things.  The ISR uses this data to update
 *     location and pen-up/down information in a little
 *     datastructure...and that's it.  The SPI ISR should execute in a
 *     handful of CPU clocks and update a global datastructure.
 * 
 *     The 60Hz timer-callback and SPI ISR run in the background all
 *     the time, and the data in the structure is
 *     continuously-refreshed.
 *
 *     That's the scheme.  Ideally, the CPU is only using two handfuls
 *     of clocks to sample the screen 60 times per second--a
 *     truly-negligible load. 
 *
 *   Nettlesome Complications
 * 
 *     As always, the real world makes our simple scheme more complex
 *     than we might really prefer.  Here are the complications that
 *     make this harder than it ought to be:
 * 
 *        A) A command *sequence* is required to get a complete X-Y
 *            data point.
 *
 *        B) There's some supersitious hoo-ha that you have to "throw
 *            away the first sample" before you get a good one.
 *  
 *            Careful experiment shows this notion to be abject
 *            bunkum.  All the samples are very, very good...including
 *            the first one.  Those guys at Analog Devices do this for
 *            a living, you know.
 * 
 *        C) There's some additional superstitious hoo-ha that you have
 *            to average your samples to get clean data
 * 
 *             That's just so much ore abject bunkum.  The *range*
 *             (nevermind the standard deviation) of the touch-data is
 *             a good bit less than one screen pixel.  The sensor is
 *             capable measuring down to ~1/4 pixel.  Impressive.
 *
 *        D) Software-sync and reentrancy issues with an ISR-updated
 *            structure is always something to be very, very careful
 *            about.
 *
 *    Really: A, just make our SPI ISR-routine more
 *    complicated.  This needs to be a little state-machine that
 *    remembers things like: "Am I currently sampling X or Y?" and 
 *    "What phase of sample-aquisition am I currently in?"
 *
 *    Issues B and C can safely be ignored.
 * 
 *    Issue D (reentrancy and synchronization) makes the public "get
 *    me a sample" access routine more complex..we have to be careful
 *    not to grab an incoherent sample.  But programmers have ways of
 *    guarding against this kind of thing, as you will see.
 * 
 ****************************************************************/
#include "sys/alt_alarm.h"
#include "alt_types.h"

typedef struct alt_touchscreen_axis_scaler_struct 
{
  int input_A;
  int input_B;
  int output_A;
  int output_B;
} alt_touchscreen_axis_scaler;

typedef struct alt_touchscreen_surface_scaler_struct
{
  alt_touchscreen_axis_scaler x;
  alt_touchscreen_axis_scaler y;
} alt_touchscreen_surface_scaler;

typedef enum alt_touchscreen_axis_swap_choice_enum
  { 
    ALT_TOUCHSCREEN_NO_SWAP_XY,
    ALT_TOUCHSCREEN_SWAP_XY
  } alt_touchscreen_axis_swap_choice;


typedef enum alt_touchscreen_callback_trigger_enum
  {
    ALT_TOUCHSCREEN_CALLBACK_NEVER,
    ALT_TOUCHSCREEN_CALLBACK_ON_PEN_UP,
    ALT_TOUCHSCREEN_CALLBACK_ON_PEN_DOWN,
    ALT_TOUCHSCREEN_CALLBACK_ON_PEN_MOVE
  } alt_touchscreen_callback_trigger;

typedef struct alt_touchscreen_scaled_pen_data_struct 
{
  int pen_down;
  int x;
  int y;
} alt_touchscreen_scaled_pen_data;

typedef struct alt_touchscreen_pen_adc_data_struct 
{
  volatile int x;
  volatile int y;
} alt_touchscreen_pen_adc_data;

typedef void (*alt_touchscreen_event_callback_func)
     (int pen_down, int x, int y, void*);

typedef struct alt_touchscreen_even_flag_group_struct
{
  volatile int pen_up_event_flag;
  volatile int pen_down_event_flag;
  volatile int pen_move_event_flag;
} alt_touchscreen_event_flag_group;

typedef struct alt_touchscreen_callback_registry_entry_struct
{
  alt_touchscreen_callback_trigger     trigger;
  alt_touchscreen_event_callback_func  callback_func;
  void*                                context;
} alt_touchscreen_callback_registry_entry;

#define ALT_TOUCHSCREEN_CALLBACK_REGISTRY_NUM_ENTRIES 10

typedef struct alt_touchscreen_callback_registry_struct
{
  alt_touchscreen_callback_registry_entry registry 
    [ALT_TOUCHSCREEN_CALLBACK_REGISTRY_NUM_ENTRIES];
} alt_touchscreen_callback_registry;


typedef struct alt_touchscreen_pen_state_struct
{
  volatile int          pen_down;
  volatile int          previous_pen_down;
  volatile int          pen_detect_counter;
  volatile int          sample_number;
} alt_touchscreen_pen_state;

typedef struct alt_touchscreen_hardware_struct
{
  alt_u32 spi_controller_base;
  alt_u32 pen_detect_pio_base;
  alt_u32 spi_controller_irq_number;
} alt_touchscreen_hardware;


#define NUM_SAMPLE_MACHINE_PHASES 5

typedef struct alt_touchscreen_sample_machine_struct
{
  int sample_phase;
  alt_u8 scheduled_commands     [NUM_SAMPLE_MACHINE_PHASES]; 
  alt_u8 link_with_next_command [NUM_SAMPLE_MACHINE_PHASES]; 
  alt_u8 rxdata_values 	        [NUM_SAMPLE_MACHINE_PHASES]; 
} alt_touchscreen_sample_machine;

typedef struct alt_touchscreen_spi_isr_context_struct
{
  alt_touchscreen_hardware*         hw;
  alt_touchscreen_sample_machine*   sample_machine;
  alt_touchscreen_pen_adc_data*     adc_data;
  alt_touchscreen_pen_state*        pen_state;
  alt_touchscreen_event_flag_group* event_flags;
} alt_touchscreen_spi_isr_context;

typedef struct alt_touchscreen_alarm_context_struct 
{
  int nticks;
  alt_touchscreen_hardware*         hw;
  alt_touchscreen_sample_machine*   sample_machine;
  alt_touchscreen_pen_state*        pen_state;
  alt_touchscreen_event_flag_group* event_flags;
} alt_touchscreen_alarm_context;
  
typedef struct alt_touchscreen_struct
{
  ////////////////
  // NOTE: THIS ENTIRE STRUCTURE IS PRIVATE.
  //
  //   It may be tempting for application-programmers to
  // rummage-around inside this structure and get things like x-y
  // coordinates or pen up/down status directly.  DON'T.   You are not
  // guaranteed to get a coherent (or even valid) sample unless you
  // use the provided public access routines.
  

  // Data Aquisition
  alt_alarm                         alarm;
  alt_touchscreen_hardware          hardware;
  alt_touchscreen_sample_machine    sample_machine;
  alt_touchscreen_pen_adc_data      pen_adc_data;
  alt_touchscreen_pen_state         pen_state;
  alt_touchscreen_event_flag_group  event_flags;

  // Interrupt-interface
  alt_touchscreen_spi_isr_context   spi_isr_context;
  alt_touchscreen_alarm_context     alarm_context;

  // Application interface
  alt_touchscreen_callback_registry callback_registry;

  // Coordinate mapping 
  alt_touchscreen_surface_scaler    surface_scaler;
  alt_touchscreen_axis_swap_choice  swap_xy;

} alt_touchscreen;

int alt_touchscreen_init (alt_touchscreen* screen,
			  alt_u32 spi_controller_base,
			  alt_u32 spi_controller_irq_number, 
			  alt_u32 pen_detect_pio_base,
			  int     samples_per_second,
			  alt_touchscreen_axis_swap_choice swap_xy );

void alt_touchscreen_stop (alt_touchscreen* screen);

unsigned int alt_touchscreen_get_pen (alt_touchscreen* screen,
				      int* pen_down,
				      int* x,
				      int* y);

int alt_touchscreen_register_callback_func (
    alt_touchscreen*                         screen,    
    alt_touchscreen_callback_trigger         callback_type,
    alt_touchscreen_event_callback_func      callback_func,
    void*                                    context	   );

void alt_touchscreen_event_loop_update (alt_touchscreen* screen);

void alt_touchscreen_calibrate_upper_right 
(
 alt_touchscreen* screen,
 unsigned int x_adc_value,
 unsigned int y_adc_value,
 int x_screen_coordinate,
 int y_screen_coordinate
 );

void alt_touchscreen_calibrate_lower_left
(
 alt_touchscreen* screen,
 unsigned int x_adc_value,
 unsigned int y_adc_value,
 int x_screen_coordinate,
 int y_screen_coordinate
 );

#endif // __ALT_TOUCHSCREEN_H_DEFINED
