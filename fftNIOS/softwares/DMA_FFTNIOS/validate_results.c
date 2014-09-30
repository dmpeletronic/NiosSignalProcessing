#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "alt_types.h"
#include "altera_avalon_sgdma.h"


/**********************************************************************************
 * This function returning nothing since it's going to print errors to the        *
 * console. It is responsible for freeing the memory allocated for each buffer    *
 * location previously allocated.                                                 *
 **********************************************************************************/
void validate_results(alt_sgdma_descriptor * transmit_descriptors,
                      alt_sgdma_descriptor * receive_descriptors,
                      alt_u32 number_of_buffers)
{
  alt_u32 buffer_counter, contents_counter, temp_length, failure = 0;
  alt_u32 * transmit_ptr, * receive_ptr;
  alt_u8 temp_transmit, temp_receive;

  /* loop through each descriptor */  
  for(buffer_counter = 0; buffer_counter < number_of_buffers; buffer_counter++)
  {
    transmit_ptr = transmit_descriptors[buffer_counter].read_addr;
    receive_ptr = receive_descriptors[buffer_counter].write_addr;
    temp_length = transmit_descriptors[buffer_counter].bytes_to_transfer;
    
    /* loop through each buffer to check the contents on each byte */
    for(contents_counter = 0; contents_counter < temp_length; contents_counter++)
    {
      temp_transmit = IORD_8DIRECT((alt_u32)transmit_ptr, contents_counter);
      temp_receive = IORD_8DIRECT((alt_u32)receive_ptr, contents_counter);
      if(temp_transmit != temp_receive)
      {
        printf("Error, sent %u, received %u, buffer: %u, index: %u\n", (unsigned int)temp_transmit, (unsigned int)temp_receive, (unsigned int)(buffer_counter+1), (unsigned int)contents_counter); 
        failure = 1;
      }
    }
    
    /* Done with these two, time to clean up after ourselves. */
    free(transmit_ptr);
    free(receive_ptr);    
  }

  if(failure == 0)
  {
    printf("The entire data transfer finished error free.\n");
  }

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
