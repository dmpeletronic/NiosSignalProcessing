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

/*****************************************************************
 *
 * alt_touchscreen 
 * 
 *    A large comment atop the header-file describes this 
 *    module, its API, and its operation in gruesome detail.
 * 
 ****************************************************************/
/*
#include "alt_touchscreen.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include <stdio.h>
#include <unistd.h>

static
int axis_scaler_compute_output (alt_touchscreen_axis_scaler* as, int input)
{
  int output;

  int numerator   =    (input - as->input_A) * (as->output_B - as->output_A);
  //                   -----------------------------------------------------
  int denominator = 	           (as->input_B - as->input_A);          

  output  = (numerator / denominator) + as->output_A;

  return output;

}

static
void surface_scaler_compute_output (alt_touchscreen_surface_scaler*  ss,
				    int  input_x,  int  input_y,
				    int* output_x, int* output_y)
{
  *output_x = axis_scaler_compute_output (&(ss->x), input_x);
  *output_y = axis_scaler_compute_output (&(ss->y), input_y);
}				    

static
void surface_scaler_set_lower_left (alt_touchscreen_surface_scaler*  ss,
				    int input_x,   int input_y,
				    int output_x,  int output_y)
{
  ss->x.input_A  = input_x;
  ss->y.input_A  = input_y;
  ss->x.output_A = output_x;
  ss->y.output_A = output_y;
}

static
void surface_scaler_set_upper_right (alt_touchscreen_surface_scaler*  ss,
				     int input_x,   int input_y,
				     int output_x,  int output_y)
{
  ss->x.input_B  = input_x;
  ss->y.input_B  = input_y;
  ss->x.output_B = output_x;
  ss->y.output_B = output_y;
}

////////////////////////////////////////////////////////////////
// pen_state_init
//
////////////////////////////////////////////////////////////////
static
void  pen_state_init (alt_touchscreen_pen_state* ps)
{
  ps->pen_down           = 0;
  ps->previous_pen_down  = 0;
  ps->pen_detect_counter = 0;
  ps->sample_number      = 0;
}

////////////////////////////////////////////////////////////////
// pen_state_update_from_detect_sample
//
//  You pass-in the current reading from the pen-detect PIO, 
//  And this makes the pen up/down determination, plus keeps 
//  history necessary for detecting transitions.
//
//  You're supposed to call this whenever:
//
//    1) You've just gathered a new sample from the ADC and checked
//       the pen-state, or...
//
//    2) You've responded to a timer-callback and, before taking a
//       sample, you've noticed that the pen is up.  
//
// Case (1) is boring. Of course you want to update the pen-state
// after gathering a fresh X/Y sample.  Case (2) is more subtle.  You
// only want to update the pen-state in the timer-callback if the pen
// is UP.  If you detect the pen is down, you don't want to go
// promising anyone any sample-data (an implicit promise when you
// declare "The pen is down!") until you've actually read the ADCs to
// figure-out where the pen is.  In short: Don't call this if you've
// noticed the pen is down, but you haven't actually taken a sample yet.
//
//  Implementation note:
//     This actually waits for the second pen-detection event before
//  declaring that "The pen is down."  I honestly don't see why this
//  is ncessary--there must be some subtlety in the program-logic that
//  I've missed.  I do know this:  If you don't put in a one-count
//  delay, then the first pen-location your application sees is an OLD
//  x-y value every time the pen goes down.  Adding a one-count delay
//  in this routine fixes that problem.  Mysteriously.  I'm sure it
//  all makes sense, I just can't explain it.
//
//  NOTE: the caller must take care to grab a sample from the PIO at the
//  right time.  The PIO does not contain a valid value when any
//  SPI-commands are in-process to the ADC.  Read the ADC datasheet
//  for a complete description.
//
////////////////////////////////////////////////////////////////
static
void pen_state_update_from_detect_sample (alt_touchscreen_pen_state* ps,
					  int pen_detect_sample) 
{
  ps->sample_number++;
  if (pen_detect_sample) 
    ps->pen_detect_counter++;
  else
    ps->pen_detect_counter = 0;
    
  ps->previous_pen_down = ps->pen_down;
  ps->pen_down          = ps->pen_detect_counter > 1;
}


////////////////////////////////////////////////////////////////
// event_flag_group_init
//
//   Simple: initializes the event-flag structure.
//
////////////////////////////////////////////////////////////////
static
void  event_flag_group_init (alt_touchscreen_event_flag_group* efg)
{
  efg->pen_up_event_flag    = 0;
  efg->pen_move_event_flag  = 0;
  efg->pen_down_event_flag  = 0;
}

////////////////////////////////////////////////////////////////
// event_flag_group_update_from_pen_state
//
//  An "event" is a change from one state to another. This routine 
//  can only ever SET flags.  They are CLEARED when they're
//  acknowledged by the receiver in the application context.  This
//  routine is supposed to be called in the interrput context.  
//
//  Although it's worth considering:  Should this actually be called
//  in the application context?   I think not...but it's a subtle
//  point and, says me, worth considering carefully.
//
////////////////////////////////////////////////////////////////
static
void event_flag_group_update_from_pen_state 
    (alt_touchscreen_event_flag_group* efg,
     alt_touchscreen_pen_state* ps)
{
  efg->pen_up_event_flag   |=   (!ps->pen_down  &&  ps->previous_pen_down);
  efg->pen_down_event_flag |=   ( ps->pen_down  && !ps->previous_pen_down);
  efg->pen_move_event_flag |=     ps->pen_down;
}


////////////////////////////////////////////////////////////////
// callback_registry_entry_init
//
//   Simple: initializes the event-callback structure.
//
////////////////////////////////////////////////////////////////
static
void callback_registry_entry_init(alt_touchscreen_callback_registry_entry* cbre) 
{
  cbre->trigger       = ALT_TOUCHSCREEN_CALLBACK_NEVER;
  cbre->callback_func = NULL;
  cbre->context       = NULL;
}


////////////////////////////////////////////////////////////////
// callback_registry_entry_test_and_do 
//
// Check my trigger-condition against the provided trigger-condition
// If it's my trigger-type...then call my callback-function.
//
////////////////////////////////////////////////////////////////
static
void callback_registry_entry_do_on_trigger (
		  alt_touchscreen_callback_registry_entry* cbre,
		  alt_touchscreen_callback_trigger         trigger_kind,
		  alt_touchscreen_scaled_pen_data*         pen_data)
{
  if ((cbre->callback_func != NULL        ) && 
      (cbre->trigger       == trigger_kind)   )

    (cbre->callback_func)(pen_data->pen_down,
			  pen_data->x,
			  pen_data->y,
			  cbre->context);
}

////////////////////////////////////////////////////////////////
// callback_registry_entry_is_registered
//
// Query function: Returns true if this entry is properly-registered,
// false if it's empty (unregistered).
//
////////////////////////////////////////////////////////////////
static
int callback_registry_entry_is_registered (
		   alt_touchscreen_callback_registry_entry* cbre)
{
  return (cbre->trigger == ALT_TOUCHSCREEN_CALLBACK_NEVER);
}


////////////////////////////////////////////////////////////////
// callback_registry_init
//
//   Simple: initializes the event-callback registry (array).
//           Just stuffs it full of initialized registry-entries.
//
////////////////////////////////////////////////////////////////
static
void callback_registry_init (alt_touchscreen_callback_registry* cbr) 
{
  int i = 0;

  // Get a pointer to the first registry-entry:
  alt_touchscreen_callback_registry_entry* cbre = &((cbr->registry)[0]);
  
  for (i = 0; i < ALT_TOUCHSCREEN_CALLBACK_REGISTRY_NUM_ENTRIES; i++) 
    callback_registry_entry_init (cbre++);
}


////////////////////////////////////////////////////////////////
// callback_registry_dispatch_one_type
//
// Check all registered callbacks against the provided trigger-condition
// and event-flag.  
//
// If the event-flag is zero, obviously we don't want to call anybody.
//
// The event-flag is acknowledged (set to zero) after all callbacks.
//
////////////////////////////////////////////////////////////////
static
void callback_registry_dispatch_one_type (
		  alt_touchscreen_callback_registry* cbr,
		  alt_touchscreen_callback_trigger   trigger_kind,
		  volatile int*                      trigger_flag,
		  alt_touchscreen_scaled_pen_data*   pen_data)
{
  int i;
  alt_touchscreen_callback_registry_entry* cbre = &((cbr->registry)[0]);

  // If the condition isn't even asserted, don't bother with anything else.
  if (*trigger_flag == 0)
    return;

  // We've seen the flag, so acknowledge (clear) it.
  *trigger_flag = 0;

  for (i = 0; i < ALT_TOUCHSCREEN_CALLBACK_REGISTRY_NUM_ENTRIES; i++) 
    callback_registry_entry_do_on_trigger (cbre++,  trigger_kind, pen_data);
   
}

////////////////////////////////////////////////////////////////
// callback_dispatch_from_event_flags
//
// Dispatches all the callbacks in the registry based on all the 
// events in the event-flag group.
//
// The event-flags are cleared after the callbacks, even if none.
//
////////////////////////////////////////////////////////////////
static
void callback_registry_dispatch_from_event_flag_group (
		   alt_touchscreen_callback_registry* cbr,
		   alt_touchscreen_event_flag_group*  efg,
		   alt_touchscreen_scaled_pen_data*   pen_data)
{
  callback_registry_dispatch_one_type (cbr, 
				       ALT_TOUCHSCREEN_CALLBACK_ON_PEN_UP,   
				       &(efg->pen_up_event_flag  ),
				       pen_data);

  callback_registry_dispatch_one_type (cbr, 
				       ALT_TOUCHSCREEN_CALLBACK_ON_PEN_DOWN, 
				       &(efg->pen_down_event_flag),
				       pen_data);

  callback_registry_dispatch_one_type (cbr, 
				       ALT_TOUCHSCREEN_CALLBACK_ON_PEN_MOVE, 
				       &(efg->pen_move_event_flag),
				       pen_data);
}

////////////////////////////////////////////////////////////////
// callback_registry_get_empty_entry 
//
// Returns a pointer to the next empty entry in the callback-registry,
// or NULL if there are no empty entries.
//
////////////////////////////////////////////////////////////////
static
alt_touchscreen_callback_registry_entry* 
   callback_registry_get_empty_entry (alt_touchscreen_callback_registry* cbr)
{
  int i;
  alt_touchscreen_callback_registry_entry* cbre = &((cbr->registry)[0]);

  for (i = 0; i < ALT_TOUCHSCREEN_CALLBACK_REGISTRY_NUM_ENTRIES; i++) {
    if (callback_registry_entry_is_registered (cbre))
      return cbre;
    cbre++;
  }
  return NULL;   // No empty entries found.
}

////////////////////////////////////////////////////////////////
// callback_registry_register_callback
// 
// Registers the requested callback-type.
// 
// Returns zero if successful, nonzero on failure.
//
// Failure happens if you try to register too many callbacks.
//
////////////////////////////////////////////////////////////////
static
int callback_registry_register_callback (
		   alt_touchscreen_callback_registry*   cbr,
		   alt_touchscreen_callback_trigger     reason,
		   alt_touchscreen_event_callback_func  callback_func,
		   void*                                context)
{
  alt_touchscreen_callback_registry_entry* cbre = 
    callback_registry_get_empty_entry (cbr);    

  if (cbre == NULL)
    return -1;
  
  cbre->trigger       = reason;
  cbre->callback_func = callback_func;
  cbre->context       = context;

  return 0;
}


////////////////////////////////////////////////////////////////
// assemble_sample
//
//  You have to read the 8-bit SPI rx-data register twice to get a
//  full sample (because samples are 12 bits).  
//
//  The first 7 bits get stored in the screen's "partial_data_sample"
//  field.  This combines those with a (presumptive) successive value
//  from the rx-data register to form a full sample.
//
////////////////////////////////////////////////////////////////
static
inline int assemble_sample (alt_u8 first_rxdata_value, 
			    alt_u8 second_rxdata_value)
{
  // Top-7 bits come from previous sample, bottom 5 from this one.
  return   ((first_rxdata_value  << 5)       ) | 
           ((second_rxdata_value >> 3) & 0x1F) ;
}

static 
void sample_machine_assemble_x_y (alt_touchscreen_sample_machine* sm,
				  int* x,int* y)
{
  *x = assemble_sample ((sm->rxdata_values)[1], (sm->rxdata_values)[2]);
  *y = assemble_sample ((sm->rxdata_values)[3], (sm->rxdata_values)[4]);
}

static
void pen_adc_data_init (alt_touchscreen_pen_adc_data* dat)
{
  dat->x = 0;
  dat->y = 0;
}

static 
void pen_adc_data_update (alt_touchscreen_pen_adc_data* dat, int x, int y)
{
  dat->x = x;
  dat->y = y;
}


////////////////
// The SPI command-values.
//
//    The AD7843 has these command-bits:
//
//     #  Name   Meaning                         X-samp      Y-samp 
//   +-+------+------------------------------+----------+-----------+
//   |7| Start| Every cmd starts with 1      |    1     |     1     |
//   |6| A2   | 0 (x) or 1 (y) sample        |    0     |     1     |
//   |5| A1   | Use bonus-inputs (not screen)|    0     |     0     |
//   |4| A0   | For us:  Just ~A1            |    1     |     1     |
//   |3| SER  | Singe-Ended (1), or diff (0) |    0     |     0     |
//   |2| Mode | 0=12-bit 1=8-bit resolution  |    0     |     0     |
//   |1| PD1  | Chip always powered-up       |    1     |     1     |
//   |0| PD0  | Disable "penIRQ" feature     |    0     |     0     |
//   +-+------+------------------------------+----------+-----------+
//   
//     We want to use the chip in 12-bit mode and we don't want it to
//     power-down between samples (we want to leave the resistive
//     screen "driven" between samples to avoid settling-time issues).
//
//     Sampling the screen in differential-mode gives true-relative
//     data that's probably more noise-immune.  Sounds good.
//
//     The Pen IRQ issue
//        The "Pen IRQ" issue is a different can of worms.  An 
//        interrupt when the pen arrives *seems* like both a nice feature
//        and a good idea.  It's neither.  Since this entire system is
//        now an interrupt-driven sampling system;  and since you can
//        register a civilized application-context callback for
//        responding to pen up/down events, a hardware 
//        interrupt on pen-down is actually now actively-useless. Dealing
//        with it would make this software vastly more complicated, and
//        for absolutely no benefit.
//
//        HOWEVER....
//
//        We "hijack" the so-called "Pen IRQ" feature as just a polled
//        pen-detection feature.  We have to.  There's no other
//        reliable way to tell if the pen is down.  Looking at sensor
//        data and guessing is just no way to run a
//        railroad--especially not when there's a perfectly-good
//        digital bit sitting right there that tells you reliably
//        whether the pen is present.  So we leave the so-called "Pen
//        IRQ" feature enabled--and then don't take interrupts from it.
//
//     Of course: After every "real" command we have to send 8 bits of
//     pure-zero to reclaim the four "leftover" bits of our 12-bit sample
//
////////////////////////////////////////////////////////////////
#define ALT_TOUCHSCREEN_X_SAMPLE_CMD  0x92
#define ALT_TOUCHSCREEN_Y_SAMPLE_CMD  0xD2
#define ALT_TOUCHSCREEN_ZERO_FILL_CMD 0x00

////////////////////////////////////////////////////////////////
// hardware_retrieve_rxdata 
//
//   Get pending data from the rxdata register in the SPI peripheral.
//   You have to have some reason to believe that there IS pending
//   data.  If not, this routine will return garbage.  
//
//   One way to be sure there's pending data: Only call this routine
//   from an interrupt-handler that's triggered by the RRDY interrupt.
//
////////////////////////////////////////////////////////////////
static
alt_u8 hardware_retrieve_rxdata (alt_touchscreen_hardware* hw)
{
  return  (alt_u8) IORD_ALTERA_AVALON_SPI_RXDATA (hw->spi_controller_base);
}

////////////////////////////////////////////////////////////////
//  hardware_stop
//
// Disables interrupts from the peripheral and un-registers the ISR
// handler. 
//
////////////////////////////////////////////////////////////////
static
void hardware_stop (alt_touchscreen_hardware* hw)
{
  IOWR_ALTERA_AVALON_SPI_CONTROL  (hw->spi_controller_base,   0);

  // Un-register our ISR.
  alt_irq_register (hw->spi_controller_irq_number, NULL, NULL);
}

static
int hardware_pen_detect (alt_touchscreen_hardware* hw)
{
  // Pen-signal is active-low from AD7843 chip
  return  (IORD_ALTERA_AVALON_PIO_DATA(hw->pen_detect_pio_base) == 0); 
}

static
void hardware_send_spi_command (alt_touchscreen_hardware* hw,
				alt_u8 command,
				int link_with_next_command)
{

  // Assert continuous-select BEFORE we do the command.
  if (link_with_next_command)
    IOWR_ALTERA_AVALON_SPI_CONTROL (hw->spi_controller_base,
				    ALTERA_AVALON_SPI_CONTROL_IRRDY_MSK |
				    ALTERA_AVALON_SPI_CONTROL_SSO_MSK   );
    

  IOWR_ALTERA_AVALON_SPI_TXDATA (hw->spi_controller_base, command);

  // De-assert continuous-select AFTER we do the command.
  if (!link_with_next_command)
    IOWR_ALTERA_AVALON_SPI_CONTROL (hw->spi_controller_base,
				    ALTERA_AVALON_SPI_CONTROL_IRRDY_MSK );
}

static
void sample_machine_update_from_rxdata (alt_touchscreen_sample_machine* sm, 
					alt_u8 rx_data)
{
  (sm->rxdata_values) [(sm->sample_phase)++] = rx_data;
}

static
int sample_machine_done (alt_touchscreen_sample_machine* sm)
{
  return sm->sample_phase >= NUM_SAMPLE_MACHINE_PHASES;
}

static
int sample_machine_ready (alt_touchscreen_sample_machine* sm)
{
  return sm->sample_phase == 0;
}

static
alt_u8 sample_machine_next_command (alt_touchscreen_sample_machine* sm)
{
  return (sm->scheduled_commands) [sm->sample_phase];
}

static
int sample_machine_link_next_command (alt_touchscreen_sample_machine* sm)
{
  return (sm->link_with_next_command) [sm->sample_phase];
}

static
void sample_machine_reset (alt_touchscreen_sample_machine* sm)
{
  sm->sample_phase = 0;
}

static
void sample_machine_init (alt_touchscreen_sample_machine* sm)
{
  int i;

  sample_machine_reset (sm);

  for (i = 0; i < NUM_SAMPLE_MACHINE_PHASES; i++)
    (sm->rxdata_values) [i] = 0;

  (sm->scheduled_commands)     [0]  = ALT_TOUCHSCREEN_X_SAMPLE_CMD;
  (sm->scheduled_commands)     [1]  = ALT_TOUCHSCREEN_ZERO_FILL_CMD;
  (sm->scheduled_commands)     [2]  = ALT_TOUCHSCREEN_Y_SAMPLE_CMD;
  (sm->scheduled_commands)     [3]  = ALT_TOUCHSCREEN_ZERO_FILL_CMD;
  (sm->scheduled_commands)     [4]  = ALT_TOUCHSCREEN_ZERO_FILL_CMD;

  (sm->link_with_next_command) [0]  = 1;
  (sm->link_with_next_command) [1]  = 1;
  (sm->link_with_next_command) [2]  = 1;
  (sm->link_with_next_command) [3]  = 1;
  (sm->link_with_next_command) [4]  = 0;
}  

static
void spi_isr_context_init (alt_touchscreen_spi_isr_context*  context,
			   alt_touchscreen_hardware*         hw,
			   alt_touchscreen_sample_machine*   machine,
			   alt_touchscreen_pen_adc_data*     adc_data,
			   alt_touchscreen_pen_state*        pen_state,
			   alt_touchscreen_event_flag_group* event_flags)
{
  context->hw             = hw;
  context->sample_machine = machine;
  context->adc_data       = adc_data;
  context->pen_state      = pen_state;
  context->event_flags    = event_flags;
}

static
void alarm_context_init (alt_touchscreen_alarm_context*   context,
			 int                               samples_per_second,
			 alt_touchscreen_hardware*         hw,
			 alt_touchscreen_sample_machine*   machine,
			 alt_touchscreen_pen_state*        pen_state,
			 alt_touchscreen_event_flag_group* event_flags)
{
    // Compute this only once here, so we don't do a divide in the
    // timer ISR.
 context->nticks        = 
   alt_ticks_per_second() / samples_per_second;

  context->hw             = hw;
  context->sample_machine = machine;
  context->pen_state      = pen_state;
  context->event_flags    = event_flags;
}


////////////////////////////////////////////////////////////////
//
// SPI ISR callback
//
//  This is the heart of the touchscreen sampling system.
//
//  This routine deals with incoming data arriving on the touchscreen
//  SPI port--and chooses which command to send next.
//
//  This is the "mastermind" of the whole screen-sampling
//  process...and yet, it is event-driven.   This implies some sort 
//  of sequencing state-machine of a perfectly-conventional sort.
//
//  The ISR is actually two nested state-machines.
//
//  The "outer" state-machine (implemented right here in this
//  function) keeps track of which "sample phase" we're in.  
//  If we don't have a complete sample, then there isn't much to do.
//
//  When we've finally got a complete new sample, we call (as a
//  subroutine) the "inner" state-machine, which knows, basically,
//  what's the next thing to do with the sample.
// 
////////////////////////////////////////////////////////////////
static
void spi_isr (void* context, alt_u32 interrupt_number)
{
  alt_touchscreen_spi_isr_context* spi_isr_context =
    (alt_touchscreen_spi_isr_context*) context;

  int pen_detect;

  alt_touchscreen_hardware*         hardware  = spi_isr_context->hw;
  alt_touchscreen_sample_machine*   machine  = spi_isr_context->sample_machine; 
  alt_touchscreen_pen_adc_data*     pen_data  = spi_isr_context->adc_data;
  alt_touchscreen_pen_state*        pen_state = spi_isr_context->pen_state;
  alt_touchscreen_event_flag_group* flags     = spi_isr_context->event_flags;
  
  alt_u8 rx_data = hardware_retrieve_rxdata (hardware);

  sample_machine_update_from_rxdata (machine, rx_data);

  if (sample_machine_done (machine)) {

    pen_detect = hardware_pen_detect (hardware);
    pen_state_update_from_detect_sample (pen_state, pen_detect);
    event_flag_group_update_from_pen_state (flags, pen_state);
						      
    if (pen_detect) {
      int x;
      int y;
      sample_machine_assemble_x_y (machine, &x, &y);
      pen_adc_data_update(pen_data, x, y);
    }

    sample_machine_reset (machine);
  } else {
    hardware_send_spi_command  (hardware, 
				sample_machine_next_command      (machine),
				sample_machine_link_next_command (machine));
  }
}

////////////////////////////////////////////////////////////////
//
// init_hardware
//
//  This does a little more than just putting the SPI hardware into a
//  known state.  It:
//
//    * Initializes the SPI-peripheral, 
//    * Sends a command to configure the AD7843 the way we like it.
//       -- in particular, we NEED the "PEN_IRQ" feature enabled,
//          or else we'll never see the pen arrive!
//    * WAITS AROUND for the first "throw-away" data to come back.
//    * Registers the ISR routine.
//    * Enables interrupts on the hardware.
//   
//   Returns zero if successful.
//
////////////////////////////////////////////////////////////////
static
int hardware_init (alt_touchscreen_hardware* hw,
		   alt_u32 spi_controller_base,
		   alt_u32 spi_controller_irq_number,
		   alt_u32 pen_detect_pio_base,
		   alt_touchscreen_spi_isr_context* context)
{
  int    error_code;
  int    tx_done = 0;
  int    spi_retry_count = 0;


  // Trivial setup of just-my-variables:
  hw->spi_controller_base       = spi_controller_base; 
  hw->spi_controller_irq_number = spi_controller_irq_number;
  hw->pen_detect_pio_base       = pen_detect_pio_base; 

  // Take no chances.  Disable interrupts; put the peripheral in a 
  // safe state.
  IOWR_ALTERA_AVALON_SPI_CONTROL (spi_controller_base, 0);

  // Clear any lingering garbage from the RX-register.
  IORD_ALTERA_AVALON_SPI_RXDATA(spi_controller_base);

  // Writing to the status-register clears some of the error-condition
  // bits (if they happen to have gotten set somehow).
  IOWR_ALTERA_AVALON_SPI_STATUS(spi_controller_base, 0);

  // Select slave zero.
  // The "select" register is a bit-mask.  A "1" in any bit-position
  // means "please select the corresponding slave."  We only expect 
  // to have one slave, which is slave number zero.  So we write a "1" 
  // into bit zero to select it.
  // This is a little counter-intuitive, because we're writing a 1 to
  // select slave zero.  Still:  That's how it works. 
  // 
  IOWR_ALTERA_AVALON_SPI_SLAVE_SEL (spi_controller_base, 1);

  // Write a sampling-command to the AD7843 just to turn-on the
  // pen-detection feature.  We wait-around-for, and then throw away,
  // the returning data.  Note that the SPI is SLOOOW, so this might
  // add many, many microseconds to the callers (presumably
  // initialization) code.
  //
  // We place a timeout on this, because it would be unseemly to
  // lock-up the caller's code mysteriously at start-up if there's
  // some kind of catastrophic  problem with the SPI peripheral.
  //
  IOWR_ALTERA_AVALON_SPI_TXDATA (spi_controller_base, 
				 ALT_TOUCHSCREEN_X_SAMPLE_CMD  );

  do {
    tx_done = 
      (IORD_ALTERA_AVALON_SPI_STATUS (spi_controller_base)) & 
      (ALTERA_AVALON_SPI_STATUS_RRDY_MSK                          ) ;

    usleep (1000);   // 1ms of waiting-around.
    if (spi_retry_count++ > 20) 
      return -1;    
  }
  while (!tx_done); 

  // Read and discard the garbage-value in the RXDATA register
  IORD_ALTERA_AVALON_SPI_RXDATA(spi_controller_base);

  // Before we enable interrupts, it would be a good idea to install
  // our interrupt-handler.  Otherwise:  Who would handle them?
  //
  error_code = alt_irq_register (hw->spi_controller_irq_number,
				 (void*) context,
				 spi_isr);
  if (error_code) 
    return 1;

  // Now we've sent the first command and (only incidentally)
  // cleared-out the recieve-buffer.
  // 
  // Directly and belligerently write the SPI control-register to 
  //     * Continuously-select the slave.
  //     * Enable interrupts on RX-complete (RRDY)
  //
  IOWR_ALTERA_AVALON_SPI_CONTROL 
    (spi_controller_base,
     ALTERA_AVALON_SPI_CONTROL_IRRDY_MSK |
     ALTERA_AVALON_SPI_CONTROL_SSO_MSK );


  return 0; // Happy.

}


////////////////////////////////////////////////////////////////
//
// get_coherent_pen_data
//
// This is the only legal way to get sensor-data in the application
// context.  Otherwise, you might get interrupted in the middle and
// get something unexpected.  Did I say "might?"  This is an embedded
// system.  After millions of cycles, you certainly will.
//
// This returns the sample-count (so software can tell if it got 
// a new sample).
//
////////////////////////////////////////////////////////////////
static
unsigned int get_coherent_pen_data 
    (alt_touchscreen_pen_state*       pen_state,
     alt_touchscreen_pen_adc_data*    pen_adc_data,
     alt_touchscreen_axis_swap_choice swap_xy,
     int* pen_down,
     int* x_adc_sample,
     int* y_adc_sample)
{
  int x;
  int y;
  int sample_number;
  
  // Look at the data over and over again until we DIDN'T get an
  // interrupt while we were in the middle of it.
  do {
    sample_number = pen_state->sample_number;
    *pen_down     = pen_state->pen_down;
    x     	  = pen_adc_data->x;
    y     	  = pen_adc_data->y;
  } while (sample_number != pen_state->sample_number);

  // If some goober wired-up the ADC wrong (as on the EEK), then you
  // can un-do this in software.  Yay, software--savior of goobers
  // everywhere. 
  if (swap_xy == ALT_TOUCHSCREEN_SWAP_XY) {
    *x_adc_sample = y;
    *y_adc_sample = x;
  } else {
    *x_adc_sample = x;
    *y_adc_sample = y;
  }


  return sample_number;
}

////////////////////////////////////////////////////////////////
// Timer (alarm) callback
//
//   If you arrange for this thing to get called at ~60Hz, then the 
//   screen will be sampled at (roughly) a quarter of that rate,
//   because  it takes two samples to get each of X and Y.
//
//   This function just dispatches commands to the SPI port, 
//   and acknowledges that it did so by setting the
//   "transmit_request" variable to "0."
//   It doesn't do anything else.  It doesn't even know what the
//   commands mean. It just sends the commands it's asked to send; 
//   acknowledges that they were sent (basically: so it doesn't send
//   them twice), and exits.
//
////////////////////////////////////////////////////////////////
static
alt_u32 alarm_callback (void* context)
{
  alt_touchscreen_alarm_context* alarm_context = 
    (alt_touchscreen_alarm_context*) context;

  alt_touchscreen_hardware*         hardware  = alarm_context->hw;
  alt_touchscreen_sample_machine*   machine   = alarm_context->sample_machine; 
  alt_touchscreen_pen_state*        pen_state = alarm_context->pen_state;
  alt_touchscreen_event_flag_group* flags     = alarm_context->event_flags;

  int pen_detect;

  
  // If the sample-machine isn't ready, it could only be because it's
  // still busy.  If it's busy, we don't want 
  // to go around starting any action of any kind.
  // 
  if (!sample_machine_ready(machine)) {
    // Note that this should never happen.
    // This means that we're "falling behind," and the sample-machine
    // isn't done with the last sample when the alarm goes off asking
    // for the next sample.
    //
    // Make a note of this in a debug flag, 
    //screen->sampling_running_behind_alarm++;
    return alarm_context->nticks;
  }

  // We have to read the pen-state inbetween samples...because that's
  // the way the AD7843 works.  "Inbetween samples" is right now,
  // before we kick-off another sample sequence.

  // Update our flags & states & such with this new pen-down data:
  //
  pen_detect = hardware_pen_detect (hardware);

  if (pen_detect) {
    // Launch a sample-sequence only if the pen is down.
    hardware_send_spi_command  (hardware, 
        sample_machine_next_command      (machine),
        sample_machine_link_next_command (machine));
  } else {
    // If the pen is up, this is actually important information.
    // there's no reason to launch another sample...but if we don't
    // update the pen-state, our clients won't know that the pen has
    // been lifted.  And, obviously:  They need to know.
      pen_state_update_from_detect_sample (pen_state, pen_detect);
      event_flag_group_update_from_pen_state (flags, pen_state);
  }

  return alarm_context->nticks;
}


////////////////////////////////////////////////////////////////
//
//  alt_touchscreen_get_pen
//
//  Public API
//
//  Provides the caller with a full, coherent sample of the current
//  pen-state.  Returns the "serial number" of the x,y,pen sample
//  acquired (so apps can see when the data changes).
//
//  If pen_down == 0, then x & y are meaningless.
//
//  This DOES NOT cause any actual sampling of the hardware--that
//  happens in the background.  This executes very quickly because
//  (really) it just updates a couple of variables and does a little
//  scaling arithmetic.
//
////////////////////////////////////////////////////////////////

unsigned int alt_touchscreen_get_pen (alt_touchscreen* screen,
				      int* pen_down,
				      int* x,
				      int* y)
{
  unsigned int x_adc_sample  = 0;
  unsigned int y_adc_sample  = 0;
  unsigned int sample_number = 0;

  sample_number = get_coherent_pen_data 
    (&(screen->pen_state),
     &(screen->pen_adc_data),
     screen->swap_xy,
     pen_down,
     &x_adc_sample,
     &y_adc_sample );

  // Note that we have to scale even if the pen isn't down.
  // The value you get is the LAST LOCATION the pen was seen.
  surface_scaler_compute_output (&(screen->surface_scaler),
				 x_adc_sample,  y_adc_sample,
				 x,             y             );
  return sample_number;
}


////////////////////////////////////////////////////////////////
//  
//  alt_touchscreen_stop()
//
//   Public API.
//
//   disables ISRs, unregisters alarms, and un-registers callbacks.
//   and returns touchscreen state-variables to some
//   harmless condition.
//   
////////////////////////////////////////////////////////////////

void alt_touchscreen_stop(alt_touchscreen* screen)
{
  // Turn off alarms
  alt_alarm_stop (&(screen->alarm));

  // Disable IRQs in the SPI core itself.
  hardware_stop (&(screen->hardware));

  callback_registry_init (&(screen->callback_registry));
}  

////////////////////////////////////////////////////////////////
//
//  alt_touchscreen_register_callback_func
//
//  Public API
//
// You pass-in a pointer to your callback-function, and indicate
// whether you want to register it for pen-up or pen-down events.
//
// Pass NULL to un-register a callback.
//
// returns 0 on success.
//
// You can only register one callback for each event type.  You must
// un-register it before you regster another one.  If you try to
// register multiple callbacks for the same event-type, this function
// will return a nonzero error code (and the preexisting callback will
// still be registered).
//
// alt_touchscreen_stop() unregisters all callbacks.
//
//
//  Implementation:
//    This is just a wrapper around the registry-management function 
//    The wrapper hides the "registry" details from the caller, whilst
//    preserving the modular testability of the "pure" registry functionality.
//
//
////////////////////////////////////////////////////////////////

int alt_touchscreen_register_callback_func (
    alt_touchscreen*                         screen,
    alt_touchscreen_callback_trigger         callback_reason,
    alt_touchscreen_event_callback_func      callback_func,
    void*                                    context	   )
{
  return callback_registry_register_callback 
    (&(screen->callback_registry), 
     callback_reason, 
     callback_func, 
     context);
}

							      
////////////////////////////////////////////////////////////////
//
// alt_touchscreen_event_loop_update
//
//  Public API
//
//  You call this function from your pen-management thread or, if you
//  don't have an OS, whenever you can from your main while(1) loop. 
//
//  This function DOES NOT drive the sensor or interact with the
//  sensor at all.
//
//  This is just a convenience-function for dispatching your
//  registered callbacks.  
//
//  This may seem inconvenient....but it's not *very* inconvenient;
//  and this way your callbacks run in application-context instead of
//  ISR.
//
//  This function returns nothing.
//
//  Implementation:
//    This is just a wrapper around the registry-management function 
//    The wrapper hides the "registry" details from the caller, whilst
//    preserving the modular testability of the "pure" registry functionality.
// 
//
////////////////////////////////////////////////////////////////

void alt_touchscreen_event_loop_update (alt_touchscreen* screen)
{
  alt_touchscreen_scaled_pen_data pen_data;

  alt_touchscreen_get_pen(
    screen, (&pen_data.pen_down), (&pen_data.x), (&pen_data.y));
    
  callback_registry_dispatch_from_event_flag_group 
    (&(screen->callback_registry), 
     &(screen->event_flags      ),
     &(pen_data)                );
}


////////////////////////////////////////////////////////////////
//
//  alt_touchscreen_init
//
//   Public API.  Starts the touchscreen sampling machinery
//
//   returns zero if successful.
////////////////////////////////////////////////////////////////
int alt_touchscreen_init (alt_touchscreen* screen,
			  alt_u32 spi_controller_base,
			  alt_u32 spi_controller_irq_number,
			  alt_u32 pen_detect_pio_base,
			  int samples_per_second,
			  alt_touchscreen_axis_swap_choice swap_xy)
{

  int error = 0;

  sample_machine_init    (&(screen->sample_machine));
  pen_state_init         (&(screen->pen_state  ));
  event_flag_group_init  (&(screen->event_flags));
  pen_adc_data_init      (&(screen->pen_adc_data));
  callback_registry_init (&(screen->callback_registry));

  // It feels a little silly to do all of this "initialization of
  // structures which just point to other structures,"  But this is
  // The Way to inforce purity & separatin, giving functions only and
  // exactly the minimal information they need to do their jobs.
  // Decoupling in the name of testability and all that, eh what? 
  //
  spi_isr_context_init   (&(screen->spi_isr_context),
			  &(screen->hardware),
			  &(screen->sample_machine),
			  &(screen->pen_adc_data),
			  &(screen->pen_state  ),
			  &(screen->event_flags));

  alarm_context_init     (&(screen->alarm_context),
			  samples_per_second,
			  &(screen->hardware),
			  &(screen->sample_machine),
			  &(screen->pen_state  ),
			  &(screen->event_flags));
  
  // Set some "harmless" scaling numbers.  These will just give 
  // the identity-transform on the A-to-D data.  Users have to call
  // explicit scale-setting functions if they want to.
  //
  screen->swap_xy = swap_xy;  

  alt_touchscreen_calibrate_lower_left  (screen,
					     0,      0,
					     0,      0 );
  alt_touchscreen_calibrate_upper_right  (screen,
					  4095,   4095,
					  4095,   4095 );
  
  // Now clear-out the SPI controller and put it in a known state:
  // This has the side-effect of registering the SPI interrupt
  // handler.
  error = hardware_init      (&(screen->hardware),
			      spi_controller_base,
			      spi_controller_irq_number,
			      pen_detect_pio_base,
			      &(screen->spi_isr_context));

  if (error) {
    alt_touchscreen_stop(screen);
    return error;
  }

  // Set an alarm for regular sampling.
    
  error = alt_alarm_start (&(screen->alarm),
			   screen->alarm_context.nticks,
			   alarm_callback,
			   (void*) (&(screen->alarm_context)));
  if (error) {
    // Couldn't set alarm.
    // Shut-down the entire touchscreen and return a failure code.
    alt_touchscreen_stop(screen);
    return error;
  }
 
  return 0;    // All happy; no error.
}


////////////////////////////////////////////////////////////////
//
// alt_touchscreen_calibrate_upper_right 
//
//     --and--
//
// alt_touchscreen_calibrate_lower_left
//
//  Public API
//
// The easiest way to do this is write your application and use the
// default settings and print-out the X/Y coordinates continuously.
//
//   First: Make sure you un-swap X and Y if they're swapped.  You do
//   this when you initialize the touchscreen.
//
//   Next: Put your pen in the upper-right and lower-left corners.
//   write-down the X- and Y-values.  You'll use these as the
//   "adc_value" numbers to pass into these routines.
//
//   The "screen coordinates" are whatever your application wants to
//   assign to those two corners of the screen.  
//
//   "Up/down" and "left/right" are whatever you consider them to be
//   when you're holding the pen in one of these corners.  Just plug
//   the numbers in an you'll get what you want.
//   
////////////////////////////////////////////////////////////////

void alt_touchscreen_calibrate_upper_right 
(
 alt_touchscreen* screen,
 unsigned int x_adc_value,
 unsigned int y_adc_value,
 int x_screen_coordinate,
 int y_screen_coordinate
 ) 
{ 
  surface_scaler_set_upper_right (&(screen->surface_scaler),
				  x_adc_value,         y_adc_value,
				  x_screen_coordinate, y_screen_coordinate);
}

void alt_touchscreen_calibrate_lower_left
(
 alt_touchscreen* screen,
 unsigned int x_adc_value,
 unsigned int y_adc_value,
 int x_screen_coordinate,
 int y_screen_coordinate
 ) 
{ 
  surface_scaler_set_lower_left (&(screen->surface_scaler),
				 x_adc_value,         y_adc_value,
				 x_screen_coordinate, y_screen_coordinate);
}
*/
