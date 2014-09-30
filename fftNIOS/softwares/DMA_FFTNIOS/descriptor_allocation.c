#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "alt_types.h"
#include "altera_avalon_sgdma_descriptor.h"


/**********************************************************************************
 * This function is called with double pointers so that it can modify (allocate)  *
 * the regions in memory to be pointed at. The easiest way to call this function  *
 * is to pass in single pointers by reference (thereby creating double pointers). *
 *                                                                                *
 * Since the descriptor masters are 256 bits wide (32 bytes) we must ensure that  *
 * all descriptors are located on 32 byte boundaries. This function will allocate *
 * enough space for one additional descriptor and slide the pointer from the      *
 * beginning until it is on a 32 byte boundary. Malloc can only provide 8 byte    *
 * alignment so without a custom memory allocation library this step is necessary *
 *                                                                                *
 * Returns 0 for sucess, 1 for failure.                                           *
 **********************************************************************************/
alt_u32 descriptor_allocation(alt_sgdma_descriptor ** transmit_descriptors,
                      alt_sgdma_descriptor ** transmit_descriptors_copy,
                      alt_sgdma_descriptor ** receive_descriptors,
                      alt_sgdma_descriptor ** receive_descriptors_copy,
                      alt_u32 number_of_buffers)
{
  /* Allocate some big buffers to hold all descriptors which will slide until
   * the first 32 byte boundary is found */
  void * temp_ptr_1, * temp_ptr_2;


/**************************************************************
   * Allocation of the transmit descriptors                   *
   * - First allocate a large buffer to the temporary pointer *
   * - Second check for sucessful memory allocation           *
   * - Third put this memory location into the pointer copy   *
   *   to be freed before the program exits                   *
   * - Forth slide the tempory pointer until it lies on a 32  *
   *   byte boundary (descriptor master is 256 bits wide)     * 
   ************************************************************/  
  temp_ptr_1 = malloc((number_of_buffers + 2) * ALTERA_AVALON_SGDMA_DESCRIPTOR_SIZE);
  if(temp_ptr_1 == NULL)
  {
    printf("Failed to allocate memory for the transmit descriptors\n");
    return 1; 
  }
  *transmit_descriptors_copy = (alt_sgdma_descriptor *)temp_ptr_1;
  
  while((((alt_u32)temp_ptr_1) % ALTERA_AVALON_SGDMA_DESCRIPTOR_SIZE) != 0)
  {
    temp_ptr_1++;  // slide the pointer until 32 byte boundary is found
  }
  *transmit_descriptors = (alt_sgdma_descriptor *)temp_ptr_1;
/**************************************************************/


  /* Clear out the null descriptor owned by hardware bit.  These locations
   * came from the heap so we don't know what state the bytes are in (owned bit could be high).*/
  transmit_descriptors[number_of_buffers]->control = 0;

/**************************************************************
   * Allocation of the receive descriptors                    *
   * - First allocate a large buffer to the temporary pointer *
   * - Second check for sucessful memory allocation           *
   * - Third put this memory location into the pointer copy   *
   *   to be freed before the program exits                   *
   * - Forth slide the tempory pointer until it lies on a 32  *
   *   byte boundary (descriptor master is 256 bits wide)     * 
   ************************************************************/  
  temp_ptr_2 = malloc((number_of_buffers + 2) * ALTERA_AVALON_SGDMA_DESCRIPTOR_SIZE);
  if(temp_ptr_2 == NULL)
  {
    printf("Failed to allocate memory for the receive descriptors\n");
    return 1; 
  }
  *receive_descriptors_copy = (alt_sgdma_descriptor *)temp_ptr_2;
  
  while((((alt_u32)temp_ptr_2) % ALTERA_AVALON_SGDMA_DESCRIPTOR_SIZE) != 0)
  {
    temp_ptr_2++;  // slide the pointer until 32 byte boundary is found
  }
  *receive_descriptors = (alt_sgdma_descriptor *)temp_ptr_2;
/**************************************************************/
  
  /* Clear out the null descriptor owned by hardware bit.  These locations
   * came from the heap so we don't know what state the bytes are in (owned bit could be high).*/
  receive_descriptors[number_of_buffers]->control = 0;


  return 0;  // no failures in allocation
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
