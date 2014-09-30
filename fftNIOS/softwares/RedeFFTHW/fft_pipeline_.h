/*
 * fft_pipeline_.h
 *
 *  Created on: 24/01/2012
 *      Author: Danilo
 */

#ifndef FFT_PIPELINE__H_
#define FFT_PIPELINE__H_

#ifndef __ALTERA_AVALON_FFT_REGS_H__
#define __ALTERA_AVALON_FFT_REGS_H__

#include <io.h>
#include "system.h"

//#define IORD_ALTERA_AVALON_PWM_DIVIDER(base)            IORD(base, 0)
#define FFT_START()      IOWR(FFT_PIPELINE_0_BASE, 0x0800, 1) // 0x0800
#define FFT_ESCREVE_DADO(pos, data) IOWR(FFT_PIPELINE_0_BASE, pos , data)
#define FFT_LE_DADO(pos) IORD(FFT_PIPELINE_0_BASE, pos)
#define FFT_FINISHED() IORD(FFT_PIPELINE_0_BASE, 0x0800) // 0x0800;


#endif /* __ALTERA_AVALON_PWM_REGS_H__ */
#endif /* FFT_PIPELINE__H_ */
