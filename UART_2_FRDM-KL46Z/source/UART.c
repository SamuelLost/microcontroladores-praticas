//
// uart.c -- Serial I/O
//
//  Copyright (c) 2012-2013 Andrew Payne <andy@payne.org>
//

#include <MKL46Z4.h>
#include "common.h"

// Circular buffers for transmit and receive
#define BUFLEN 128

static uint8_t _tx_buffer[sizeof(RingBuffer) + BUFLEN] __attribute__ ((aligned(4)));
static uint8_t _rx_buffer[sizeof(RingBuffer) + BUFLEN] __attribute__ ((aligned(4)));

static RingBuffer *const tx_buffer = (RingBuffer *) &_tx_buffer;
static RingBuffer *const rx_buffer = (RingBuffer *) &_rx_buffer;

void UART0_IRQHandler()
{
    int status;

    status = UART0->S1;

    // If transmit data register empty, and data in the transmit buffer,
    // send it.  If it leaves the buffer empty, disable the transmit interrupt.
    if ((status & UART_S1_TDRE_MASK) && !buf_isempty(tx_buffer)) {
        UART0->D = buf_get_byte(tx_buffer);
        if(buf_isempty(tx_buffer))
            UART0->C2 &= ~UART_C2_TIE_MASK;
    }

    // If there is received data, read it into the receive buffer.  If the
    // buffer is full, disable the receive interrupt.
    if ((status & UART_S1_RDRF_MASK) && !buf_isfull(rx_buffer)) {
        buf_put_byte(rx_buffer, UART0->D);
        if(buf_isfull(rx_buffer))
            UART0->C2 &= ~UART_C2_RIE_MASK;
    }
}
// BR = (Freq/((15 + 1) * BAUD))
void uartConfigBoundRate(uint32_t baud){
	if(baud == 115200){
		UART0->BDL = 0x1A;
		UART0->BDH = 0x0;
	}else if(baud == 9600){
		UART0->BDL = 0x38;
		UART0->BDH = 0x1;
	}
}

int uart_write(char *p, int len)
{
    int i;

    for(i=0; i<len; i++) {
        while(buf_isfull(tx_buffer)){}       // Spin wait while full
        buf_put_byte(tx_buffer, *p++);
        UART0->C2 |= UART_C2_TIE_MASK;           // Turn on Tx interrupts
    }
    return len;
}

//// A blocking write, useful for error/crash/debug reporting
//int uart_write_err(char *p, int len)
//{
//    int i;
//    __disable_irq();
//    for(i=0; i<len; i++) {
//        while((UART0_S1 & UART_S1_TDRE_MASK) == 0){}  // Wait until transmit buffer empty
//
//        UART0_D = *p++;                     // Send char
//    }
//    __enable_irq();
//    return len;
//}

int uart_read(char *p, int len)
{
    int i = len;

    while(i > 0) {
        while(buf_isempty(rx_buffer)){}           // Spin wait

        *p++ = buf_get_byte(rx_buffer);
        UART0->C2 |= UART_C2_RIE_MASK;           // Turn on Rx interrupt
        i--;
    }
    return len - i;
}

//
// uart_init() -- Initialize debug / OpenSDA UART0
//
//      The OpenSDA UART RX/TX is connected to pins 27/28, PTA1/PTA2 (ALT2)
//
//void uart_init(int baud_rate)
//{
//	// Select MCGFLLCLK as UART0 clock
//	SIM->SOPT2 |= (0b01 << 26);
//
//	// Enable UART0 Clock
//	SIM->SCGC4 |= (1 << 10);
//
//	// Enable PORTA clock
//	SIM->SCGC5 |= (1 << 9);
//
//	// PTA1 as ALT2 (UART0) -> UART0_RX
//	PORTA->PCR[1] |=  (0b010 << 8);
//
//	//PTA2 as ALT2 (UART0) -> UART0_TX
//	PORTA->PCR[2] |=  (0b010 << 8);
//
//    UART0->C2 = 0;
//    UART0->C1 = 0;
//    UART0->C3 = 0;
//    UART0->S2 = 0;
//
//    // Configure Baud Rate
//    uartConfigBoundRate(baud_rate);
//
//    // Initialize transmit and receive circular buffers
//    buf_reset(tx_buffer, BUFLEN);
//    buf_reset(rx_buffer, BUFLEN);
//
//    // Enable the transmitter, receiver, and receive interrupts
//    UART0->C2 = UART_C2_RE_MASK | UART_C2_TE_MASK | UART_C2_RIE_MASK;
//    NVIC_EnableIRQ(UART0_IRQn);
//}

void uart_init(int baud_rate)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

    // Turn on clock to UART0 module and select 48Mhz clock (FLL/PLL source)
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);                 // FLL/PLL source

    // Select "Alt 2" usage to enable UART0 on pins
    PORTA->PCR[1] = PORT_PCR_MUX(2);
    PORTA->PCR[2] = PORT_PCR_MUX(2);

    UART0->C2 = 0;
    UART0->C1 = 0;
    UART0->C3 = 0;
    UART0->S2 = 0;

    // Set the baud rate divisor
    #define OVER_SAMPLE 16
    uint16_t divisor = (48000000 / OVER_SAMPLE) / baud_rate;
    UART0->C4 = UART0_C4_OSR(OVER_SAMPLE - 1);
    UART0->BDH = (divisor >> 8) & UART_BDH_SBR_MASK;
    UART0->BDL = (divisor & UART_BDL_SBR_MASK);

    // Initialize transmit and receive circular buffers
    buf_reset(tx_buffer, BUFLEN);
    buf_reset(rx_buffer, BUFLEN);

    // Enable the transmitter, receiver, and receive interrupts
    UART0->C2 = UART_C2_RE_MASK | UART_C2_TE_MASK | UART_C2_RIE_MASK;
    NVIC_EnableIRQ(UART0_IRQn);
}
