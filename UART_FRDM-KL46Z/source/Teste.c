//
//#include "MKL46Z4.h"
//#include <clock_config.h>
//#include <fsl_clock.h>
//
//static int i = 0;
//int mcg_clk_khz;
//int core_clk_khz;
//
//#define BAUD	115200
//unsigned char queue[128];
//uint8_t wptr;
//uint8_t rptr;
//
//#define INCR_PTR(x) x == 127 ? 0 : (x+1)
//
//void UART1_IRQHandler(void)
//{
//	uint8_t data;
//	uint8_t status = UART1->S1;
//
//	if((UART1->S1 & UART_S1_RDRF_MASK)) {
//		queue[wptr] = UART1->D;
//		wptr = INCR_PTR(wptr);
//
//		if(wptr == rptr)
//			rptr = INCR_PTR(rptr);
//	}
//
//	if((UART1->S1 & UART_S1_TDRE_MASK)){
//		uart_sendString("Samuel");
//	}
//}
//
//char uart_getchar ()
//{
//      /* Aguarde até que o personagem seja recebido */
//      while (!(UART1->S1 & UART_S1_RDRF_MASK));
//
//      /* Retornar os dados de 8 bits do receptor */
//      return UART1->D;
//}
//
//void uart_sendchar (char data)
//{
//      /* Aguarde até que o personagem seja recebido */
//      while (!(UART1->S1 & UART_S1_TDRE_MASK));
//
//      /* Retornar os dados de 8 bits do receptor */
//      UART1->D = data;
//}
//void uart_sendString(char *string){
//	while (*string){
//		__disable_irq();
//
//		// Transmit Data Register Empty Flag
//		//!(UART1->S1 & UART_S1_TDRE_MASK)
//		while(!(UART1->S1 & (1 << 7))) { }
//
//		// Sending caracter
//		UART1->D = *string;
//
//		__enable_irq();
//
//		string++;
//	}
//}
//
//int main(void)
//{
//	uint32_t sbr;
//	uint8_t temp;
//	char data;
//	uint8_t reg;
//	uint32_t mcg_clk_hz;
//
//	// Select MCGFLLCLK (48MHz) as UART0 clock
//	SIM->SOPT2 |= (0b01 << 26);
//
//	/* Ativar relógios para LPTMR, PORTA_A, PORTA_D, PORTA_B e PORTA_E */
//	SIM->SCGC5 = (1 << SIM_SCGC5_PORTE_SHIFT);
//
//	SIM->SCGC4 = (1 << SIM_SCGC4_UART1_SHIFT);
//
////	mcg_clk_hz = CLOCK_GetCoreSysClkFreq();
////	CLOCK_GetFreq(kCLOCK_)
//
//	/* PORTA_E 0, 1 são UART */
//	PORTE->PCR[0] =(3 << 8);
//	PORTE->PCR[1] =(3 << 8);
//
//	UART1->C1 = 0;    // TIPO DE PARIDADE
//
//	/* Desabilite Transmitir e Receber antes de qualquer configuração */
//	UART1->C2 = UART1->C2 & ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
//
//	sbr = (48000000)/(BAUD * 16);
//
//	UART1->BDH = 0x0;
//	UART1->BDL = 0x1A;
//
//	/* Habilite Transmitir e Receber antes de qualquer configuração */
//	UART1->C2 = UART1->C2 | (UART_C2_RE_MASK | UART_C2_TE_MASK | UART_C2_RIE_MASK | UART_C2_TIE_MASK);
//	NVIC_EnableIRQ(UART1_IRQn);
//
//	data = 32;
//
//	for(;;) {
//		/*uint8_t ch;
//		ch = uart_getchar();
//		uart_sendchar(ch);*/
//	}
//
//    return 0;
//}
