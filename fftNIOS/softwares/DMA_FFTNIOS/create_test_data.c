#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "alt_types.h"
#include "altera_avalon_sgdma.h"
#include "sys/alt_cache.h"


/**********************************************************************************
 * This function is responsible for allocating the data buffer for each           *
 * descriptor. A random buffer length will be generated if you set the minimum    *
 * and maximum buffer lengths to be different. To run a more controlled test, set *
 * the minimum and maximum buffer lengths to be equal.                            *
 *                                                                                *
 * Returns 0 for sucess, 1 for failure.                                           *
 **********************************************************************************/
alt_u32 create_test_data(alt_sgdma_descriptor * transmit_descriptors,
                      alt_sgdma_descriptor * receive_descriptors,
                      alt_u32 number_of_buffers,
                      alt_u32 minimum_buffer_length,
                      alt_u32 maximum_buffer_length)
{

  alt_u32 buffer_counter, contents_counter, temp_length;
  alt_u32 *transmit_ptr, *receive_ptr;
  alt_u8 *transmit_ptr_copy, *receive_ptr_copy;  // will use these to fill up the tx buffers and clear the rx buffers
  alt_u32 temp_data = 0;  
  char c;


  /*  Initialization of the buffer memories and the transmit+receive descriptors */
  for(buffer_counter = 0; buffer_counter < number_of_buffers; buffer_counter++)
  {
    /*  Generate a random buffer length between within MINIMUM_BUFFER_LENGTH and MAXIMUM_BUFFER_LENGTH */
    if(minimum_buffer_length == maximum_buffer_length)  // if you don't want a random length set these equal
    {  
      temp_length = minimum_buffer_length;
    }
    else
    {
      if(minimum_buffer_length > maximum_buffer_length)
      {
         printf("Please set the maximum buffer length to be larger than\n");
         printf("the minimum buffer length (in includes_and_settigns.h)\n");
         return 1;
      }
      temp_length = (rand() % (maximum_buffer_length - minimum_buffer_length)) + minimum_buffer_length;      
    }
    
    
    transmit_ptr = (alt_u32 *)malloc(temp_length);  // this descriptor will point at a buffer of length (temp_length)
    if(transmit_ptr == NULL)
    {
      printf("Allocating a transmit buffer region failed\n");
      return 1; 
    }
    receive_ptr = (alt_u32 *)malloc(temp_length);  // since the same contents will be received the length is the same
    if(receive_ptr == NULL)
    {
      printf("Allocating a receive buffer region failed\n");
      return 1; 
    }


    /* This will populate sequential data (modulo 256) in each transmit buffer a byte at a time.
     * The recieve buffers are also cleared with zeros so that each time this software is run
     * the data can be reverified.  Before this function returns a flush will be performed to
     * make sure none of these writes are still in the data cache.
     */
    transmit_ptr_copy = (alt_u8 *)transmit_ptr;
    receive_ptr_copy = (alt_u8 *)receive_ptr;
    for(contents_counter = 0; contents_counter < temp_length; contents_counter++)
    {
      transmit_ptr_copy[contents_counter] = (alt_u8)(temp_data & 0xFF);
      receive_ptr_copy[contents_counter] = 0;
      temp_data++;
    }

    /* This will create a descriptor that is capable of transmitting data from an Avalon-MM buffer
     * to a packet enabled Avalon-ST FIFO component */
    alt_avalon_sgdma_construct_mem_to_stream_desc(&transmit_descriptors[buffer_counter],  // descriptor
                                                  &transmit_descriptors[buffer_counter+1], // next descriptor
                                                  transmit_ptr,  // read buffer location
                                                  (alt_u16)temp_length,  // length of the buffer
                                                  0, // reads are not from a fixed location
                                                  0, // start of packet is enabled for the Avalon-ST interfaces
                                                  0, // end of packet is enabled for the Avalon-ST interfaces,
                                                  0);  // there is only one channel

		/* This will create a descriptor that is capable of transmitting data from an Avalon-ST FIFO
		* to an Avalon-MM buffer */


    alt_avalon_sgdma_construct_stream_to_mem_desc(&receive_descriptors[buffer_counter],  // descriptor
                                                  &receive_descriptors[buffer_counter+1], // next descriptor
                                                  receive_ptr,  // write buffer location
                                                  (alt_u16)temp_length,  // length of the buffer
                                                  0); // writes are not to a fixed location 

       /* printf("\n\nDescriptor Transmit %d", buffer_counter);
		printf("\nRead addr: 0x%x, pad: %d", transmit_descriptors[buffer_counter].read_addr, transmit_descriptors[buffer_counter].read_addr_pad);
		printf("\nWrite add: 0x%x, pad: %d", transmit_descriptors[buffer_counter].write_addr, transmit_descriptors[buffer_counter].write_addr_pad);
		printf("\nNext:      0x%x, pad: %d", transmit_descriptors[buffer_counter].next, transmit_descriptors[buffer_counter].next_pad);
		printf("\nBytes to transfer: %d", transmit_descriptors[buffer_counter].bytes_to_transfer);
		printf("\nRead_burst: 0x%x", transmit_descriptors[buffer_counter].read_burst);
		printf("\nWrite_burst: 0x%x", transmit_descriptors[buffer_counter].write_burst);
		printf("\nActual_bytes_transferred: %d", transmit_descriptors[buffer_counter].actual_bytes_transferred);
		printf("\nStatus: 0x%x", transmit_descriptors[buffer_counter].status);
		printf("\nControl: 0x%x", transmit_descriptors[buffer_counter].control);*/

		printf("\n\nDescriptor Receive %d", buffer_counter);
		printf("\nRead addr: 0x%x, pad: %d", receive_descriptors[buffer_counter].read_addr, receive_descriptors[buffer_counter].read_addr_pad);
		printf("\nWrite add: 0x%x, pad: %d", receive_descriptors[buffer_counter].write_addr, receive_descriptors[buffer_counter].write_addr_pad);
		printf("\nNext:      0x%x, pad: %d", receive_descriptors[buffer_counter].next, receive_descriptors[buffer_counter].next_pad);
		printf("\nBytes to transfer: %d", receive_descriptors[buffer_counter].bytes_to_transfer);
		printf("\nRead_burst: 0x%x", receive_descriptors[buffer_counter].read_burst);
		printf("\nWrite_burst: 0x%x", receive_descriptors[buffer_counter].write_burst);
		printf("\nActual_bytes_transferred: %d", receive_descriptors[buffer_counter].actual_bytes_transferred);
		printf("\nStatus: 0x%x", receive_descriptors[buffer_counter].status);
		printf("\nControl: 0x%x", receive_descriptors[buffer_counter].control);
        c = getchar();

  }
  
  alt_dcache_flush_all();  // make sure all the transmit buffers and cleared receive buffers go out to main memory
  
  return 0;  // no failures creating data buffers
}


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
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/
