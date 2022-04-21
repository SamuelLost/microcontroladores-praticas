/**
 * @file    SWITCH_LED.c
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
typedef struct{
	uint32_t PCR[32];
}PORTRegs_t;

#define PORT_C ((PORTRegs_t *) 0x4004B000)
#define PORT_D ((PORTRegs_t *) 0x4004C000)

typedef struct{
	 uint32_t PDOR;
	 uint32_t PSOR;
	 uint32_t PCOR;
	 uint32_t PTOR;
	 uint32_t PDIR;
	 uint32_t PDDR;
}GPIORegs_t;

#define GPIO_C ((GPIORegs_t *) 0x400FF080)
#define GPIO_D ((GPIORegs_t *) 0x400FF0C0)
/*
 * @brief   Application entry point.
 * Circuito com filtro passa-baixa com o objetivo de eliminar o bounce do botão
 */
int main(void) {
		SIM->SCGC5 = (1 << 11) | (1 << 12); //Ativando clock das portas C e D

		PORT_C->PCR[8] = (1 << 8); //MUX -> PORT_C, PIN 8

		PORT_D->PCR[4] = (1 << 8) | (1 << 1) | (1 << 0); //MUX -> PORT_D, PIN 4, PULLENABLE, PULLUP

		GPIO_C->PDDR = (1 << 8); //GPIO is OUTPUT

		GPIO_C->PSOR = (1 << 8); // LED OFF

		while(1){
			if(GPIO_D->PDIR & (1 << 4)){ //POOLING
				// LED OFF
				GPIO_C->PSOR |= (1 << 8);
			}else{
				//LED ON
				GPIO_C->PCOR |= (1 << 8);
			}
		}
    return 0 ;
}

