/* p7_3.c: A to D conversion of channel 0
 * This program converts the analog input from channel 0 (PTE20)
 * using software trigger continuously. PTE20 is connected to
 * an LM34 Fahrenheit temperature sensor. The conversion result
 * is displayed as temperature through UART0 virtual serial port.
 * 16-bit precision is used for conversion. At higher precision,
 * the noise is more significant so 32 samples averaging is used.
 * The LM34 output voltage is 10mV/degreeF. The ADC of FRDM-KL25Z
 * uses 3.3V as Vref so:
 * temperature = result * 330.0 / 65536
 * Open a terminal emulator at 115200 Baud rate at the host PC and
 * observe the output.
 */
#include "MKL46Z4.h"
#include <stdio.h>
#include "fsl_clock.h"

void ADC0_init(void);
void delayMs(int n);
int adc_cal(void);
int main (void) {
	int result;
	ADC0_init(); /* Configure ADC0 */
	int flag = 0;
	while (1) {
		ADC0->SC1[0] = 9; /* start conversion on channel 0 */
		while(!adcCalibration()); /* wait for calibration */
		while(!(ADC0->SC1[0] & (1 << 7))) { } /* wait for COCO */
		result = ADC0->R[0]; /* read conversion result and clear COCO flag */

		float temperature = result * 300.0 / 65536;

		printf("Temperatura %d C\n", (int) temperature);
	}
}
void ADC0_init(void) {

	SIM->SCGC6 |= (1 << 27); /* clock to ADC0 */
	ADC0->SC2  &= ~(1 << 6); /* software trigger */
	ADC0->SC3  |= (0b11 << 0) | (1 << 2); /* 32 samples average */

	/* clock div by 4, long sample time, single ended 16 bit, bus clock */
	ADC0->CFG1 = (0b10 << 5) | (1 << 4) | (0b11 << 2) | 0x00;
	/*Single-ended conversions*/
	ADC0->SC1[0] &= ~(1 << 5);
}

bool adcCalibration(void) {
	uint16_t calib;

	ADC0->SC3 |= (1 << 7); 	 	// Start calibration process

	while (ADC0->SC3 & (1 << 7)); // Wait for calibration to end

	if (ADC0->SC3 & (1 << 6))	// Check for successful calibration
		return false;

	calib = 0;
	calib += ADC0->CLPS + ADC0->CLP4 + ADC0->CLP3 +
			     ADC0->CLP2 + ADC0->CLP1 + ADC0->CLP0;
	calib /= 2;
	calib |= 0x8000; 	// Set MSB
	ADC0->PG = calib;

	calib = 0;
	calib += ADC0->CLMS + ADC0->CLM4 + ADC0->CLM3 +
			     ADC0->CLM2 + ADC0->CLM1 + ADC0->CLM0;
	calib /= 2;
	calib |= 0x8000;	// Set MSB
	ADC0->MG = calib;

	return true;
}
