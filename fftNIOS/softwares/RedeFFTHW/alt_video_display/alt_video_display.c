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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <sys/alt_cache.h>
#include <malloc.h>
#include <priv/alt_file.h>
#include <sys/alt_irq.h>
#include <altera_avalon_sgdma.h>
#include <altera_avalon_sgdma_descriptor.h>
#include <altera_avalon_sgdma_regs.h>
#include "system.h"
#include "alt_video_display.h"

/******************************************************************
*                   PUBLIC API FUNCTIONS                          *
******************************************************************/ 

/******************************************************************
*  Function: alt_video_display_init
*
*  Purpose: Initializes the display controller. Gets memory for the 
*           frame buffer and descriptor buffers, intitalizes the 
*           descriptors, sets the resolution of the frame buffers,
*           clears all the frame buffers, then finally opens 
*           the SGDMA, registers the SGDMA callback function and
*           starts the SGDMA.
* 
*  Returns: *Note non-standard return code!*:
*           Pointer to the display controller structure, or NULL on failure.
******************************************************************/
alt_video_display* alt_video_display_init( char* sgdma_name,
                                           int width,
                                           int height,
                                           int color_depth,
                                           int buffer_location,
                                           int descriptor_location,
                                           int num_buffers)
{
  alt_video_display* display;
  unsigned int bytes_per_pixel, bytes_per_frame, descriptors_per_frame, i;
  int result;
  
  // We'll need these values more than once, so let's pre-calculate them. 
  bytes_per_pixel = color_depth >> 3; // same as /8
  bytes_per_frame = (( width * height ) * bytes_per_pixel );
  
  // Calculate the number of descriptors needed for each frame 
  if( bytes_per_frame <= ALT_VIDEO_DISPLAY_BYTES_PER_DESC ) {
    descriptors_per_frame = 1;
  }
  else if(( bytes_per_frame % ALT_VIDEO_DISPLAY_BYTES_PER_DESC) == 0) {
    descriptors_per_frame = bytes_per_frame / ALT_VIDEO_DISPLAY_BYTES_PER_DESC;
  }
  else { 
    descriptors_per_frame = 
      ( bytes_per_frame / ALT_VIDEO_DISPLAY_BYTES_PER_DESC ) + 1;
  }
  
  // Check for too many frame buffers
  if( num_buffers > ALT_VIDEO_DISPLAY_MAX_BUFFERS ) {
  	num_buffers = ALT_VIDEO_DISPLAY_MAX_BUFFERS;
  }
  
  // Allocate our display struct 
  display = (alt_video_display*) malloc(sizeof(alt_video_display));
  if(!display) {
    return NULL;
  }
  
  // Fill out the display structure 
  display->width = width;
  display->height = height;
  display->color_depth = color_depth;
  display->num_frame_buffers = num_buffers;
  display->bytes_per_frame = bytes_per_frame;
  display->bytes_per_pixel = bytes_per_pixel;
  display->buffer_being_displayed = 0;
  display->buffer_being_written = (num_buffers > 1) ? 1:0;
  display->descriptors_per_frame = descriptors_per_frame;
  
  // Allocate our frame and descriptor buffers 
  if(alt_video_display_allocate_buffers( display,
                                         bytes_per_frame,  
                                         buffer_location, 
                                         descriptor_location, 
                                         num_buffers ) ) {
    return NULL;
  }  
  
  // Now construct SGDMA descriptors for each frame buffer 
  for( i = 0; i < num_buffers; i++ ) {
    alt_video_display_setup_frame_descriptors(
      display,                                    // our display
      display->buffer_ptrs[i],                    // frame 
      display->buffer_ptrs[i]->buffer,            // frame location
      display->buffer_ptrs[i]->desc_base );       // descriptor memory 
  }

  // Clear all frame buffers to black 
  for( i = 0; i < num_buffers; i++ ) {
    memset( (void*)(display->buffer_ptrs[i]->buffer), 
      ALT_VIDEO_DISPLAY_BLACK_8, display->bytes_per_frame );
  }
  
  // Open the SGDMA 
  display->sgdma = alt_avalon_sgdma_open(sgdma_name);
  if(!display->sgdma) {
    return NULL;
  }
  
  /* Enable SGDMA "parking" mode */
  IOWR_ALTERA_AVALON_SGDMA_CONTROL(LCD_SGDMA_BASE, 
    ALTERA_AVALON_SGDMA_CONTROL_PARK_MSK);
  
  /* Now start the SGDMA */
  result = alt_avalon_sgdma_do_async_transfer(
    display->sgdma, 
    display->buffer_ptrs[display->buffer_being_displayed]->desc_base);
  	
  if(result) {
    return NULL;
  }
  
  return ( display );
}

/******************************************************************
*  Function: alt_video_display_close
*
*  Purpose: Closes the display and frees all malloc'd memory
*
*  Returns:  void 
*
******************************************************************/
void alt_video_display_close( alt_video_display* display, 
                              int buffer_location, 
                              int descriptor_location )
{
  int i;
  
  // Stop the sgdma
  alt_avalon_sgdma_stop( display->sgdma );  

  // Free our frame buffers and descriptor buffers
  for( i = 0; i < display->num_frame_buffers; i++ ) {
    // Free the frame buffer if it was on the heap
    if( buffer_location == ALT_VIDEO_DISPLAY_USE_HEAP )
      free( display->buffer_ptrs[i]->buffer );
    
    // Free the descriptor buffer it was on the heap
    if( descriptor_location == ALT_VIDEO_DISPLAY_USE_HEAP )
      free( display->buffer_ptrs[i]->desc_base );

    // Free the buffer pointer struct
    free( display->buffer_ptrs[i] );
  }

  // Finally free our display struct
  free( display );
}

/******************************************************************
*  Function: alt_video_display_register_written_buffer
*
*  Purpose: Registers the buffer pointed to by buffer_being_written
*           as being finished and ready for display.
*
*  Returns: 0 - Everything is groovy.
*           1 - buffer_being_written is now equal to buffer_being_displayed
*                 - It would be a good idea to wait for buffer_being_displayed 
*                   to increment before writing to buffer_being_written.
*
******************************************************************/
int alt_video_display_register_written_buffer( alt_video_display* display )
{
  int ret_code, prev_frame_index;
  alt_sgdma_descriptor *desc_prev_frame_tail;
  alt_sgdma_descriptor *desc_being_registered_head, *desc_being_registered_tail;

  /* 
   * Prepare relevant SGDMA descriptors in the frame being registered:
   *  - Set the new frame's head-descriptor transfer count to 0
   *  - Ensure that the new frame descriptor chain loops (tail points to head)
   *  - Point the previous frame at the new one to "break" its loop
   */
  desc_being_registered_head = 
    display->buffer_ptrs[display->buffer_being_written]->desc_base;
  desc_being_registered_tail = desc_being_registered_head + 
    (display->descriptors_per_frame - 1);
      
  IOWR_16DIRECT(
    (alt_u32)(&desc_being_registered_head->actual_bytes_transferred), 
    0, (alt_u16) 0x0);
  IOWR_32DIRECT((alt_u32)(&desc_being_registered_tail->next), 0, 
    (alt_u32)(desc_being_registered_head)); 
 
  /* Find the tail of the descriptor chain in the last frame registered */
  prev_frame_index = (display->buffer_being_written - 1);

  if(prev_frame_index < 0) {
    prev_frame_index = (display->num_frame_buffers - 1);
  }

  desc_prev_frame_tail = display->buffer_ptrs[prev_frame_index]->desc_base;
  desc_prev_frame_tail += (display->descriptors_per_frame - 1);
       
  IOWR_32DIRECT((alt_u32)(&desc_prev_frame_tail->next), 0, 
    (alt_u32)(desc_being_registered_head));
  
  /* 
   * Update frame_being_written index. Note: The new index may *not* be 
   * safe to write to; alt_video_display_buffer_is_available() must be 
   * called to verify this).
   */
  display->buffer_being_written = 
    ( display->buffer_being_written + 1 ) % display->num_frame_buffers;

  if( display->buffer_being_written == display->buffer_being_displayed ) {
    ret_code = 1;
  }
  else {
    ret_code = 0;
  }
  
  return(ret_code);
}

/******************************************************************
*  Function: alt_video_display_buffer_is_available
*
*  Purpose: Checks for a free frame buffer to write to.
*
*  Returns:  0 - Found free buffer.  buffer_being_written now points to it.
*           -1 - Free buffer not available at this time. 
*
******************************************************************/
int alt_video_display_buffer_is_available( alt_video_display* display )
{
  int ret_code = 0, next_buf_index;
  alt_sgdma_descriptor *desc;
  
  if(display->num_frame_buffers > 1) {
    /* 
     * The user, via this API call, is asking us to see if its safe to 
     * write to the buffer display->buffer_ptrs[display->buffer_being_written].
     * 
     * To do so, we need to ensure that display->buffer_being_displayed
     * is accurate. The SGDMA could have finished any number of previously-
     * registered-for-display buffers and gone on to the next one, as long
     * as the user registered them with the 
     * alt_video_display_register_written_buffer() routine.
     *
     * Here we will inspect any such registered buffers that exist between
     * where buffer_being_written and buffer_being_displayed are to determine
     * if the SGDMA has processed them. If it has, then we know that the 
     * previous buffer is no longer being transferred to the video display
     * device, and is now safe to be written again, and update
     * the buffer_being_displayed index accordingly.
     */
    next_buf_index = 
      ((display->buffer_being_displayed + 1) % display->num_frame_buffers); 
      
    /* Inspect all buffers until we reach the one being written */
    while(next_buf_index != display->buffer_being_written ) {
      desc = display->buffer_ptrs[next_buf_index]->desc_base;
      /* 
       * If there are signs of actual data transfer having occured, we 
       * can safely increment the buffer_being_displayed index
       */
      if(IORD_16DIRECT(&desc->actual_bytes_transferred, 0) > 0) {
        display->buffer_being_displayed = next_buf_index; 
      }
        
      next_buf_index = ((next_buf_index + 1) % display->num_frame_buffers);
    }
    
    if( display->buffer_being_written == display->buffer_being_displayed ) { 
      ret_code = -1;
    }
  } /* if (# frame buffers > 1) */
  /* 
   * There is only one display buffer. In this case, you're always 
   * overwriting the "live" buffer on the screen. No sense in reporting 
   * a problem since you asked for it.
   */
  else {
    ret_code = 0;
  }

  return (ret_code);
}

/******************************************************************
*  Function: alt_video_display_clear_screen
*
*  Purpose: Uses the fast memset routine to clear the entire frame
*           buffer.  User can specify black(0x00) or white(0xFF).
*
******************************************************************/
inline void alt_video_display_clear_screen(alt_video_display* display, 
                                           char color)
{
  memset( (void*)(display->buffer_ptrs[display->buffer_being_written]->buffer), 
    color, display->bytes_per_frame );
}

/******************************************************************
*                     PRIVATE FUNCTIONS                           *
******************************************************************/ 

/******************************************************************
 * alt_video_display_setup_frame_descriptors
 * 
 * Populate and prepare a video frame's SGDMA descriptors. 
 * 
 * Arguments:
 *   *display: The video display the frame is being prepared for
 *   *frame: The video frame you're constructing
 *   *buffer: The starting-address of your physical display buffer. 
 *    This must be a single, continuous span of memory large enough 
 *    for each pixel in the frame.
 *   *desc_base: The starting-address of memory allocated for 
 *    SGDMA descriptors. Descriptor memory must be aligned to a 
 *    0x20 boundary.
 ******************************************************************/
void alt_video_display_setup_frame_descriptors(
  alt_video_display *display,
  alt_video_frame *frame,
  alt_u32 *buffer,
  alt_sgdma_descriptor *desc_base)
{
  int i;
  alt_u16 length;
  alt_32 buffer_no_cache_bypass;
  alt_sgdma_descriptor *last_descriptor;
  
  /*
   * We don't want the "uncached" bit set in the buffer address we hand
   * off to the SGDMA, so we mask it out here.
   */
  buffer_no_cache_bypass = 
    (alt_u32) alt_remap_cached( buffer, display->bytes_per_frame );
  
  for(i=0; i<display->descriptors_per_frame; i++){
    /* 
     * Calculate the data length associated with each descriptor, taking
     * into account the edge cases 
     */
    if(i == (display->descriptors_per_frame-1)) {
      length = (display->bytes_per_frame % ALT_VIDEO_DISPLAY_BYTES_PER_DESC);

       /* 
        * The init routine calculated the number of desriptors per frame, 
        * based on frame size (bytes) and bytes per descriptor. Being evenly
        * divisible on this last frame means a full-length sized frame.
        */
       if(length == 0) {
         length = ALT_VIDEO_DISPLAY_BYTES_PER_DESC;
       }
    }
    else {
      length = ALT_VIDEO_DISPLAY_BYTES_PER_DESC;
    }
    
    /* Construct the descriptor */
    alt_avalon_sgdma_construct_mem_to_stream_desc(
      (frame->desc_base + i),                    /* Descriptor */
      ( frame->desc_base + i + 1 ),              /* Next descriptor */
      (alt_u32*)( (alt_u8*)buffer_no_cache_bypass +
         (ALT_VIDEO_DISPLAY_BYTES_PER_DESC*i) ), /* Read Address */
      length,                                    /* Transfer length */
      0,                                         /* Don't read fixed addr */
      i==0?1:0,                                  /* Generate SOP @ first desc */
      i==(display->descriptors_per_frame-1)?1:0, /* Generate EOP @ last desc */
      0                                          /* Streaming channel: N/A */
    );
    
    /* 
     * The last descriptor we created above requires a special modification: 
     * Its "next" pointer should point back to the first descriptor in the 
     * chain to create a loop.
     * 
     * This was not done done in the above SGDMA descriptor creation routine 
     * call because that routine always terminates the 'next' descriptor 
     * pointer to prevent the SGDMA from continuing into unknown memory.
     */
    if( i == ( display->descriptors_per_frame - 1 ) ) {  
      last_descriptor = (alt_sgdma_descriptor *) (frame->desc_base + i);
      
      IOWR_32DIRECT((alt_u32)(&last_descriptor->next), 0, 
        (alt_u32)(frame->desc_base));
    }
  }
}

/******************************************************************
 * alt_video_display_get_descriptor_span
 * 
 * Calculate the number of bytes requireed for descriptor storage
 * of a particular display. This is useful for allocating memory or
 * allocating pointers at runtime for creating new video frames.
 * 
 * This routine adds two to the physical number of descriptors stored
 * in the display's properties in order to assist your memory-allocation
 * needs; the SGDMA API requires a "next" which, for the final descriptor
 * in a chain requires one extra descriptor. A second "extra" descriptor-span 
 * is added to afford address alignment; SGDMA descriptors must be aligned
 * to 0x20-byte boundaries. The alt_video_display_allocate_buffers() routine
 * contains examples of these.
 * 
 * Arguments:
 *   - *display: (Initialized) Video display to calculate descriptor memory
 *               requirements for
 * 
 * Returns:
 *   - Size (bytes) of descriptor memory required.
 ******************************************************************/
alt_u32 alt_video_display_get_descriptor_span(alt_video_display *display)
{
  return ((display->descriptors_per_frame+2) * sizeof(alt_sgdma_descriptor));
}

/******************************************************************
*  Function: alt_video_display_allocate_buffers
*
*  Purpose: Allocates memory for both the frame buffers and the 
*           descriptor chains.
* 
*           If ALT_VIDEO_DISPLAY_USE_HEAP is specified for either
*           the buffer_location or descriptor_location, the memory
*           is allocated from the heap. Otherwise, buffer_location and 
*           descriptor_locaiton are presumed to contain the base address 
*           of memory sufficient to hold the requested number of descriptors
*           and video frames. This memory space may be quite large.
* 
*  Returns:  0 - Success
*           -1 - Error allocating memory
******************************************************************/
int alt_video_display_allocate_buffers( alt_video_display* display,
                                       int bytes_per_frame,
                                       int buffer_location,
                                       int descriptor_location,
                                       int num_buffers )
{
  int i, ret_code = 0;
  
  /* Allocate our frame buffers and descriptor buffers */
  for( i = 0; i < num_buffers; i++ ) {
    display->buffer_ptrs[i] = 
      (alt_video_frame*) malloc( sizeof( alt_video_frame ));
      
    if(display->buffer_ptrs[i] == NULL) {
      ret_code = -1;
    }
    
    if( buffer_location == ALT_VIDEO_DISPLAY_USE_HEAP ) {
      display->buffer_ptrs[i]->buffer = 
        (void*) alt_uncached_malloc(( bytes_per_frame ));
        
      if( display->buffer_ptrs[i]->buffer == NULL )
        ret_code = -1;
    }
    else {
      display->buffer_ptrs[i]->buffer = (void*)alt_remap_uncached(
        (void*)(buffer_location + (i * bytes_per_frame)), bytes_per_frame);
    }
    
    if( descriptor_location == ALT_VIDEO_DISPLAY_USE_HEAP ) {
      /*
       * The SGDMA controller requires all descriptors to be aligned to
       * the size of an SGDMA descriptor (32 bytes).  Use memalign() to 
       * get properly aligned address.
       */
      display->buffer_ptrs[i]->desc_base = (alt_sgdma_descriptor*)
        memalign( 32, alt_video_display_get_descriptor_span( display ) );
      
      if( display->buffer_ptrs[i]->desc_base == NULL ) {
        ret_code = -1;
      }
    }
    else {
      display->buffer_ptrs[i]->desc_base = 
        (alt_sgdma_descriptor*)((void*)descriptor_location + 
          (i * alt_video_display_get_descriptor_span( display )));
    } 
  }
 
  return ret_code;
}
