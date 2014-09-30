#ifndef INCLUDES_AND_SETTINGS_H_
#define INCLUDES_AND_SETTINGS_H_


#define NUMBER_OF_BUFFERS 250//500  /* each direction so double this for the total */
#define MINIMUM_BUFFER_LENGTH 64
#define MAXIMUM_BUFFER_LENGTH 1500  /* set this to the same value as the min for a fixed size, also don't exceed 65535 */

/* Making sure that there will be enough space for code (maximum of 1.5MB) */
#if ((2 * NUMBER_OF_BUFFERS * MAXIMUM_BUFFER_LENGTH) > 1572864)
  #error Your total buffer space has exceeded the limit.  Please reduce the\
         buffer space so that there is enough room to hold Nios II code.
#endif

/* prototypes to include in the main file */
alt_u32 descriptor_allocation(alt_sgdma_descriptor ** transmit_descriptors,
                      alt_sgdma_descriptor ** transmit_descriptors_copy,
                      alt_sgdma_descriptor ** receive_descriptors,
                      alt_sgdma_descriptor ** receive_descriptors_copy,
                      alt_u32 number_of_buffers);

alt_u32 create_test_data(alt_sgdma_descriptor * transmit_descriptors,
                      alt_sgdma_descriptor * receive_descriptors,
                      alt_u32 number_of_buffers,
                      alt_u32 minimum_buffer_length,
                      alt_u32 maximum_buffer_length);

void validate_results(alt_sgdma_descriptor * transmit_descriptors,
                      alt_sgdma_descriptor * receive_descriptors,
                      alt_u32 number_of_buffers);


#endif /*INCLUDES_AND_SETTINGS_H_*/
