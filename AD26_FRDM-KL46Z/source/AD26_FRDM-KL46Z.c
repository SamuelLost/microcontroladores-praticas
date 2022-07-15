/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    AD26_FRDM-KL46Z.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
void ADC0_init(void) {

	SIM->SCGC6 |= (1 << 27); /* clock to ADC0 */
	ADC0->SC2  &= ~(1 << 6); /* software trigger */
	ADC0->SC3  |= (0b11 << 0) | (1 << 2); /* 32 samples average */
	/* clock div by 4, long sample time, single ended 16 bit, bus clock */
	ADC0->CFG1 = (0b10 << 5) | (1 << 4) | (0b11 << 2) | 0x00;
	ADC0->SC1[0] &= ~(1 << 5);
}
int main(void) {


	ADC0_init();
	while (1) {
		ADC0->SC1[0] |= (0b11010 << 0); /* start conversion on channel 0 */
		while((ADC0->SC1[0] & 0x80)) { } /* wait for COCO */
		uint16_t result = ADC0->R[0]; /* read conversion result and clear COCO flag */
//		temperature = result * 330.0 / 65536; /* convert voltage to temperature */
//		printf("\r\nTemp = %6.2dC", temperature); /* convert to string */
		float temperature = result * 300.0 / 65536;

		printf("Temperatura %d C\n", (int) temperature);
	}

    return 0 ;
}
