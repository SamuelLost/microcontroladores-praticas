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
 * @file    LED.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
typedef struct {
	uint32_t PCR[32];
}PORTRegs_t;

// portB18 led red
// portB19 led verde
// portD_1 led azul

#define PORT_B ((PORTRegs_t *) 0x4004A000)
#define PORT_D ((PORTRegs_t *) 0x4004C000)

typedef struct{
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;
}GPIORegs_t;

#define GPIO_B ((GPIORegs_t * ) 0x400FF040)
#define GPIO_D ((GPIORegs_t * ) 0x400FF0C0)
//
//#define SetBit(valor, bit) ((valor) |=  (1 << bit))
//#define ClrBit(valor, bit) ((valor) &= ~(1 << bit))
//
//#define BitSet(value, bit) ((value) |=  (1 << bit)) // Enable the bit in value.
//#define BitClr(value, bit) ((value) &= ~(1 << bit)) // Clean the bit in value.
/*
 * @brief   Application entry point.
 */
void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}

void toggleColors();
void colorRedBlue();
void colorBlueGreen();
void colorRedGreen();
void colorRGB();

int main(void) {

	SIM->SCGC5 |= (1 << 10) | (1 << 12); // ATIVAR O CLOCK DA PORT_B ( 1 << 10) E PORT_D (1 << 12)

	PORT_B->PCR[18] |= (1 << 8); // SET AS GPIO
	PORT_B->PCR[19] |= (1 << 8);
	PORT_D->PCR[1]  |= (1 << 8); // SET AS GPIO
	GPIO_B->PDDR |= (1 << 18); //GPIO_B pin 18 as output.
	GPIO_B->PDDR |= (1 << 19); //GPIO_B pin 19 as output.
	GPIO_D->PDDR |= (1 << 1); //GPIO_D pin 1 as output.

	GPIO_B->PSOR |= (1 << 18); //TURN OFF RED LED
	GPIO_B->PSOR |= (1 << 19); //TURN OFF GREEN LED
	GPIO_D->PSOR |= (1 << 1); //TURN OFF BLUE LED
	while(1) {
		toggleColors();
		delayMs(1000);
		colorBlueGreen();
		delayMs(1000);
		colorRedBlue();
		delayMs(1000);
		colorRedGreen();
		delayMs(1000);
		colorRGB();
	}

	return 0 ;
}

void toggleColors() {
	GPIO_B->PCOR |= (1 << 18); //TURN ON RED LED
	delayMs(1000);
	GPIO_B->PSOR |= (1 << 18); //TURN OFF RED LED
	delayMs(1000);

	GPIO_B->PCOR |= (1 << 19); //TURN ON GREEN LED
	delayMs(1000);
	GPIO_B->PSOR |= (1 << 19); //TURN OFF GREEN LED
	delayMs(1000);

	GPIO_D->PCOR |= (1 << 1); //TURN ON BLUE LED
	delayMs(1000);
	GPIO_D->PSOR |= (1 << 1); //TURN OFF BLUE LED
}

void colorRedBlue() {
	GPIO_B->PCOR |= (1 << 18); //TURN ON RED LED
	delayMs(1000);
	GPIO_D->PCOR |= (1 << 1); //TURN ON BLUE LED
	delayMs(1000);

	GPIO_B->PSOR |= (1 << 18); //TURN OFF RED LED
	delayMs(1000);
	GPIO_D->PSOR |= (1 << 1); //TURN OFF BLUE LED

}
void colorBlueGreen() {
	GPIO_B->PCOR |= (1 << 19); //TURN ON GREEN LED
	delayMs(1000);
	GPIO_D->PCOR |= (1 << 1); //TURN ON BLUE LED
	delayMs(1000);

	GPIO_D->PSOR |= (1 << 1); //TURN OFF BLUE LED
	delayMs(1000);
	GPIO_B->PSOR |= (1 << 19); //TURN OFF GREEN LED
}
void colorRedGreen() {
	GPIO_B->PCOR |= (1 << 18); //TURN ON RED LED
	delayMs(1000);
	GPIO_B->PCOR |= (1 << 19); //TURN ON GREEN LED
	delayMs(1000);

	GPIO_B->PSOR |= (1 << 18); //TURN OFF RED LED
	delayMs(1000);
	GPIO_B->PSOR |= (1 << 19); //TURN OFF GREEN LED
}
void colorRGB() {
	GPIO_B->PCOR |= (1 << 18); //TURN ON RED LED
	delayMs(1000);
	GPIO_B->PCOR |= (1 << 19); //TURN ON GREEN LED
	delayMs(1000);
	GPIO_D->PCOR |= (1 << 1); //TURN ON BLUE LED
	delayMs(1000);

	GPIO_B->PSOR |= (1 << 18); //TURN OFF RED LED
	delayMs(1000);
	GPIO_B->PSOR |= (1 << 19); //TURN OFF GREEN LED
	delayMs(1000);
	GPIO_D->PSOR |= (1 << 1); //TURN OFF BLUE LED
	delayMs(1000);

}

