/******************************************************************************
* Copyright(c)2007 Altera Corporation, San Jose, California, USA.             *
* All rights reserved. All use of this software and documentation is          *
* subject to the License Agreement located at the end of this file below.     *
*******************************************************************************
* Author - JCJB                                                               *
* Date - 04/09/2007                                                           *
*                                                                             *
* This design example shows how to use the scatter gather DMA (SGDMA) to      *
* perform transfers between Avalon-MM and Avalon-ST interfaces.  This         *
* software uses the SGDMA in an interrupt configuration but waits on the      *
* interrupt before proceeding to validate the data that was transfered.       *
*                                                                             *
* This design example performs the following transfers:                       *
*                                                                             *
* SSRAM(MM) --> (MM)SGDMA(ST) --> (ST)SGDMA(MM) --> SSRAM(MM)                 *
*                                                                             *
* Two SGDMA components are used in this system since Avalon-ST is a           *
* uni-directional point to point method of connecting IP. Between each SGDMA  *
* Avalon-ST interface are a pair of FIFOs performing a clock crossing.  This  *
* clock crossing is simply present to demonstrate how you can change clock    *
* domains between Avalon-ST based components.                                 *
*******************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "altera_avalon_sgdma.h"
#include "altera_avalon_sgdma_regs.h"
#include "alt_types.h"
#include "includes_and_settings.h"  // setup is located in this file



/* These will gate the data checking near the end of main */
volatile alt_u8 tx_done = 0;
volatile alt_u8 rx_done = 0;

void transmit_callback_function(void * context)
{
  tx_done++;  /* main will be polling for this value being 1 */
}

void receive_callback_function(void * context)
{
  rx_done++;  /* main will be polling for this value being 1 */
}


int main()
{
	alt_u32 return_code;
	alt_sgdma_dev * transmit_DMA;
	alt_sgdma_dev * receive_DMA;
	 /* Needs one allocated descriptor at the end to mark the tail of the list.
	   * Copies are made so that they can be put back on the heap when we are done.
	   * The copies are a superset of the other pointers so by freeing them at the
	   * end we'll be freeing transmit_descriptors and receive_descriptors as well. */
    alt_sgdma_descriptor *transmit_descriptors, *transmit_descriptors_copy;
	alt_sgdma_descriptor *receive_descriptors, *receive_descriptors_copy;
	char c;


	printf("\nHello from NIOS. Press s to continue..\n");

	while(1){
		c = getchar();
		if(c=='s') break;
	}
	printf("Starting\n");

  /* Open a SG-DMA for MM-->ST and ST-->MM (two SG-DMAs are present) */
  transmit_DMA = alt_avalon_sgdma_open("/dev/sgdma_mm_to_st");
  receive_DMA = alt_avalon_sgdma_open("/dev/sgdma_st_to_mm");
  printf("SGDMAs opened\n");
  

/**************************************************************
   * Making sure the SG-DMAs were opened correctly            *
   ************************************************************/
  printf("Verifing pointers\n");
  if(transmit_DMA == NULL)
  {
    printf("Could not open the transmit SG-DMA\n");
    c=getchar();

  }else
	printf("Transmit not null\n");

  if(receive_DMA == NULL)
  {
    printf("Could not open the receive SG-DMA\n");
    c=getchar();

  }else
	  printf("Receive not null\n");
/**************************************************************/
  

/**************************************************************
   * Allocating descriptor table space from main memory.      * 
   * Pointers are passed by reference since they will be      *
   * modified by this function.                               *
   ************************************************************/
  printf("Allocating descriptors\n");
  return_code = descriptor_allocation(&transmit_descriptors,
                                &transmit_descriptors_copy,
                                &receive_descriptors,
                                &receive_descriptors_copy,
                                NUMBER_OF_BUFFERS);
  printf("Verifing descriptors\n");
  if(return_code == 1)
  {
    printf("Allocating the descriptor memory failed... exiting\n");
    return 1; 
  }else
	  printf("Descriptors allocated\n");
/**************************************************************/


/**************************************************************
   * Allocating data buffers and populating them with data    *
   ************************************************************/
  return_code = create_test_data(transmit_descriptors,
                                 receive_descriptors,
                                 NUMBER_OF_BUFFERS,
                                 MINIMUM_BUFFER_LENGTH,
                                 MAXIMUM_BUFFER_LENGTH);
  if(return_code == 1)
  {
    printf("Allocating the data buffers failed... exiting\n");
    return 1; 
  }else
	printf("Data created\n");
/**************************************************************/


/**************************************************************
   * Register the ISRs that will get called when each (full)  *
   * transfer completes                                       *
   ************************************************************/ 
  alt_avalon_sgdma_register_callback(transmit_DMA,
                                    &transmit_callback_function,
                                    (ALTERA_AVALON_SGDMA_CONTROL_IE_GLOBAL_MSK | ALTERA_AVALON_SGDMA_CONTROL_IE_CHAIN_COMPLETED_MSK),
                                    NULL);
  alt_avalon_sgdma_register_callback(receive_DMA,
                                    &receive_callback_function,
                                    (ALTERA_AVALON_SGDMA_CONTROL_IE_GLOBAL_MSK | ALTERA_AVALON_SGDMA_CONTROL_IE_CHAIN_COMPLETED_MSK),
                                    NULL);
  printf("Callbacks initializated\n");
/**************************************************************/


/**************************************************************
   * Starting both the transmit and receive transfers         *
   ************************************************************/
  printf("Starting up the SGDMA engines\n");

  /* Prime the SGDMA engines with the descriptor lists (first one, it's a linked list) */
  if(alt_avalon_sgdma_do_async_transfer(transmit_DMA, &transmit_descriptors[0]) != 0)
  {
    printf("Writing the head of the transmit descriptor list to the DMA failed\n");
    return 1;
  }
  printf("Transmit started\n");
  if(alt_avalon_sgdma_do_async_transfer(receive_DMA, &receive_descriptors[0]) != 0)
  {
    printf("Writing the head of the receive descriptor list to the DMA failed\n");
    return 1;
  }
  printf("Receive started\n");
/**************************************************************/


/**************************************************************
   * Blocking until the SGDMA interrupts fire                 *
   ************************************************************/
  while(tx_done == 0) {}
    printf("The transmit SGDMA has completed\n");
  while(rx_done == 0) {}
    printf("The receive SGDMA has completed\n");
/**************************************************************/


/**************************************************************
   * Verify the returned data and free up the data buffers    *
   ************************************************************/
  validate_results(transmit_descriptors,
                   receive_descriptors,
                   NUMBER_OF_BUFFERS);
/**************************************************************/


/**************************************************************
   * Stop the SGDMAs and free up the descriptor memory        *
   ************************************************************/
  alt_avalon_sgdma_stop(transmit_DMA);
  alt_avalon_sgdma_stop(receive_DMA);

  free(transmit_descriptors_copy);
  free(receive_descriptors_copy);
/**************************************************************/


  printf("Exiting...%c", 4); // 4 will terminate the console

  return 0;
}

