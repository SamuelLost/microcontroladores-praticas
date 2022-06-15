#include "MKL46Z4.h"

void initPWMPins() {
	SIM->SCGC5   |= (1 << 10);
	PORTB->PCR[0] = (1 << 8);
	PORTB->PCR[1] = (1 << 8);
	PORTB->PCR[2] = (1 << 8);
	PORTB->PCR[3] = (1 << 8);

	GPIOB->PDDR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
}

void delay(int n) {
	for (int i = 0; i < n; i++);
}

int main() {
	initPWMPins();
	char steps[] = {0x9, 0x3, 0x6, 0xC};

	int counter = 0, control = 0, mod = 513;

	while (1) {
		counter = (counter + 1) % mod;
		if (counter == (mod - 1)) control ^= 1;
		if (!control) {
			for (int i = 0; i < 4; i++) {
//				GPIOB->PCOR |= 0xF;
				GPIOB->PDOR = 0x0;
				GPIOB->PDOR |= steps[3 - i];
				delay(10000);
			}
		} else {
			for (int i = 0; i < 4; i++) {
//				GPIOB->PCOR |= 0xF;
				GPIOB->PDOR = 0x0;
				GPIOB->PDOR |= steps[i];
				delay(10000);
			}
		}
	}
	return 0;
}

