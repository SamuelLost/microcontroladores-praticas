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

/* Delay n milliseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */
void LCD_init(void) {
	SIM->SCGC5 |= (1 << 13);

	PORTE->PCR[2] |= (1 << 8);	// D0
	PORTE->PCR[3] |= (1 << 8);  // D1
	PORTE->PCR[6] |= (1 << 8);  // D2
	PORTE->PCR[16] |= (1 << 8); // D3
	PORTE->PCR[17] |= (1 << 8); // D4
	PORTE->PCR[18] |= (1 << 8); // D5
	PORTE->PCR[19] |= (1 << 8); // D6
	PORTE->PCR[31] |= (1 << 8); // D7


	// PINOS DE CONTROLE
	PORTE->PCR[20] |= (1 << 8); // RS
	PORTE->PCR[21] |= (1 << 8); // R/W
	PORTE->PCR[22] |= (1 << 8); // E


	GPIOE->PDDR |= (1 << 2) | (1 << 3) | (1 << 6) | (1 << 16) | (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20) | (1 << 21) | (1 << 22) | (1 << 31);

	GPIOE->PDOR |= (1 << 2) | (1 << 3) | (1 << 6) | (1 << 16) | (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20) | (1 << 21) | (1 << 22) | (1 << 31);
}

void GPIO_setByte(char c){
	//colocar os dados nos pinos de dados D0-D7
	GPIOE->PDOR &= 0xFFFFFF00;			// zerar os bytes menos significativos
	GPIOE->PDOR |= (unsigned int) c;	// setar os bits em 1 no byte menos significativo
}

//Gerar o pulso de Enable de ~450ns
void GPIO_enableE(){
	//gerar um pulso de ~450ns
	GPIOC->PSOR = (1 << 22); // setar em 1
	delay(1);
	GPIOC->PCOR = (1 << 22); // setar em 1
}

void GPIO_setRS(lcd_RS_type i){
	if(i == COMANDO){
		GPIOC->PCOR = (1 << 20);		// Seta o LCD no Modo de COMANDO
	}else if(i = DADO){
		GPIOC->PSOR = (1 << 20);		// Seta o LCD no Modo de DADOS
	}
}

// Transferir um byte ao LCD
void  escreveLCD(char c, uint32_t t){
	GPIO_setByte(c);			// c byes
	GPIO_enableE();
	delay(t);					// t tempo de processamento em multiplos de 2 us
}

// Inicializar o LCD
void initLCD(){
	//esperar por mais de 30ns = 30000us/2 = 15000
	delay(15000);

	GPIO_setRS(COMANDO);
	escreveLCD(0x38, 20);		// Function Set: 39us/2 --> 20
	escreveLCD(0x0C, 20);		// Display ON/OFF Control: 39us/2 --> 20
	escreveLCD(0x01, 765);		// Display Clear: 1530us/2 --> 765
	escreveLCD(0x06, 20);		// Entry mode set: 39us/2 --> 20
}

void scan_temperature(void){
	static uint16_t adc_result;
	static uint16_t adc_result_avg;
	static uint16_t temp;
	static uint8_t loopcntr;

	uint32_t data;
	uint32_t voltage;

	/* Incrementa a cada 50 ms */
	loopcntr++;

	ADC0->SC1[0] = ( (TEMPERATURE_SENSOR_CHN & (8 << 0)) | (ADC0->SC1[0] & ((1 << 6) | (1 << 5)  )
					) );

	while(ADC0->SC2 & (1 << 7)); 	 // Conversion in progress
	while(!(ADC0->SC1[0] & (1 << 7) )); // Run until the conversion is complete
	//while((ADC0->SC1[0] & (1 << 7)) == 0); // add

	/* Obtém o resultado do ADC para o sensor de temperatura */
	adc_result  = adc_result + ADC0->R[0];

	//data = ADC0->R[0];//ADD

	/* Pegue 16 amostras para calcular a temperatura */
	if (loopcntr >= 16){
		adc_result_avg = adc_result >> 4;       /* obtendo o valor médio do ADC*/
		temp = ((adc_result_avg * VREF_FACTOR) >> 10); /* Calcular a temperatura */

		adc_result = 0;
		loopcntr = 0;
	}
	/* Exibe a temperatura */
	display_temperature(temp);
	/* Desativa o módulo ADC */
	ADC0->SC1[0] |= (0b11111 << 0);
}

// Escrever uma mensagem str no LCD a partir do endereço especificado
// end endereço da DDRAM
// str mensagem
void escreveMensagem(uint8_t end, char* str){
	//Possicione o curso no end
	uint8_t tmp = 0b10000000 | end;		// seta o bit 7 em 1
	GPIO_setRS(COMANDO);				// Comando
	escreveLCD(tmp, 20);				// seta o endereço do cursor

	// Chaveia para o modo de DADO
	GPIO_setRS(DADO);
	while(*str){
		escreveLCD(*str, 20);
		str++;
	}
}

void display_temperature(uint8_t temp){
	static char lcd_str[] = "00 (C)"; /* temperature */
	static uint8_t prev_temp = 0;     /* Previous temperature */

	if (prev_temp != temp){
		prev_temp = temp;

		/* Move cursor para 6th bloco na linha 2 */
		//escreveLCD(0x46, 20);
		lcd_str[0] = ((uint8_t)(temp / 10)) + '0'; /* Higher digit in ASCII */
		lcd_str[1] = ((uint8_t)(temp % 10)) + '0'; /* Lower digit in ASCII */
		escreveMensagem(0x46, lcd_str); /* Write to LCD */
	}
}

int main (void) {
	int result;
	ADC0_init(); /* Configure ADC0 */
	while (1) {
		ADC0->SC1[0] = 9; /* start conversion on channel 0 */
		while(!(ADC0->SC1[0] & 0x80)) { } /* wait for COCO */
		result = ADC0->R[0]; /* read conversion result and clear COCO flag */
		//		temperature = result * 330.0 / 65536; /* convert voltage to temperature */
		//		printf("\r\nTemp = %6.2dC", temperature); /* convert to string */

		float temperature = result * 330.0 / 65536;

		printf("Temperatura %d C\n", (int) temperature);
	}
}
void ADC0_init(void)
{
	SIM->SCGC5 |= (1 << 10); /* clock to PORTE */
	PORTB->PCR[1] = 0; /* PTB1 analog input */


	SIM->SCGC5 |= 0x2000; /* clock to PORTE */
	PORTE->PCR[20] = 0; /* PTE20 analog input */
	SIM->SCGC6 |= 0x8000000; /* clock to ADC0 */
	ADC0->SC2 &= ~0x40; /* software trigger */
	ADC0->SC3 |= 0x07; /* 32 samples average */
	/* clock div by 4, long sample time, single ended 16 bit, bus clock */
	ADC0->CFG1 = 0x40 | 0x10 | 0x0C | 0x00;
}

void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}
