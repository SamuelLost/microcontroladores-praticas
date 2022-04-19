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
 * @file    SWITCH_LED_FRDM-KL43Z.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define pin_led_1 1
#define pin_led_2 29
#define pin_sw_1 12
#define pin_sw_2 5

typedef struct {
	uint32_t PCR[32];
}PORTRegs_t;

#define PORT_A ((PORTRegs_t *) 0x40049000)
#define PORT_E ((PORTRegs_t *) 0x4004D000)

typedef struct {
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;

}GPIORegs_t;

#define GPIO_A ((GPIORegs_t *) 0x400FF000)
#define GPIO_E ((GPIORegs_t *) 0x400FF100)

/*
 * @brief   Application entry point.
 */
int main(void) {

	SIM->SCGC5 |= (1 << 9) | (1 << 13);

	//LEDs
	PORT_E->PCR[1] |= (1 << 8);
	PORT_E->PCR[29] |= (1 << 8);

	//SWs
	PORT_A->PCR[12] |= (1 << 8) | (1 << 1) | (1 << 0);
	PORT_A->PCR[5] |= (1 << 8) | (1 << 1) | (1 << 0);

	GPIO_E->PDDR |= (1 << 1);
	GPIO_E->PDDR |= (1 << 29);
	GPIO_E->PSOR |= (1 << 1);
	GPIO_E->PSOR |= (1 << 29);

	while(1){
		if(GPIO_A->PDIR & (1 << 12)){
			// LED OFF
			GPIO_E->PSOR |= (1 << 1);
		}else{
			//LED ON
			GPIO_E->PCOR |= (1 << 1);
		}

		//DEU CRT
		if(GPIO_A->PDIR & (1 << 5)){
			// LED OFF
			GPIO_E->PSOR |= (1 << 29);
		}else{
			//LED ON
			GPIO_E->PCOR |= (1 << 29);
		}
	}
    return 0 ;
}
