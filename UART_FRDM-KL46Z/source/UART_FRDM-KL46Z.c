/**
 * @file    UART_FRDM-KL46Z.c
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
#include "UART.h"
#include "GPIO.h"
/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

// #define KEY_LED_RED_ON 'a'
// #define KEY_LED_BLUE_ON 's'
// #define KEY_LED_GREEN_ON 'd'
// #define KEY_LEDS_OFF 'w'
// #define KEY_LED_SMOOTHING_MODE 'q'

static uint8_t isMenuOpen;
static uint8_t isLoggingStarted;
static unsigned char *buffer;
volatile unsigned char *read;

volatile char userInputData;
// volatile char isLedRedOn;
// volatile char isLedGreenOn;
// volatile char isLedBlueOn;
// volatile uint16_t pwm;

void menu(void){
	uart_sendString("================================= \r\n");
	uart_sendString("a. TO TURN ON/OFF THE RED LED \r\n");
	uart_sendString("d. TO TURN ON/OFF THE GREEN LED \r\n");
	uart_sendString("r. TO TURN OFF THE LEDS \r\n");
	uart_sendString("q. SELECT SMOOTHING MODE \r\n");
	uart_sendString("================================= \r\n");
}

void sleep(int n) {
	for (int i =  0; i < n; ++i)
		for (int j = 0; j < 4800; ++j);
}

void UART0_IRQHandler(void){
	// Receive Data Register Full Flag
	// 1 - Receive data buffer full.
	if ((UART0->S1 & (1 << 5))){
//		userInputData = uart_getchar();
//		isLoggingStarted = 0;
		UART0->C2 &= ~(UART_C2_RIE_MASK); //apos receber desabilita //cver fav

	}
	if((UART0->S1 & (1 << 7))) {
//		uart_sendString("Samuel\n\r");
//		uart_sendchar(userInputData);
		UART0->C2 &= ~UART_C2_TIE_MASK; //apos enviar desabilita
	}
}

int main (void) {
	// Configure System Clock
	sysClockConfig();

	// Initialize UART module
	// gpioInit();

	//PWM init
	// pwmInitModule();

	// Initialize GPIO module
	UART0_init(115200);

	menu();


	while (1) {
		userInputData = uart_getchar();
		uart_sendchar(userInputData);
	}
}




