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
/*
 * @brief   Application entry point.
 */
//int main(void) {
//
//	port_pin_config_t config = {0};
//
//	gpio_pin_config_t gpioLed = {
//			kGPIO_DigitalOutput,
//			1
//	};
//
//	gpio_pin_config_t swLed = {
//			kGPIO_DigitalInput,
//			0
//	};
//
//
//	CLOCK_EnableClock(kCLOCK_PortA);
//	CLOCK_EnableClock(kCLOCK_PortE);
//
//	PORT_SetPinMux(PORTE, pin_led_1, kPORT_MuxAsGpio);
//	PORT_SetPinMux(PORTE, pin_led_2, kPORT_MuxAsGpio);
//
//	config.mux = kPORT_MuxAsGpio;
//	config.pullSelect = kPORT_PullUp;
//	PORT_SetPinConfig(PORTA, 12, &config);
//
//	GPIO_PinInit(GPIOE, pin_led_1, &gpioLed);
//	GPIO_PinInit(GPIOE, pin_led_2, &gpioLed);
//
//	GPIO_PinInit(GPIOA, pin_sw_1, &swLed);
//	GPIO_PinInit(GPIOA, pin_sw_2, &swLed);
//
////	while(1){
////		if(GPIO_ReadPinInput(GPIOA, 12)){
////			GPIO_SetPinsOutput(GPIOC, (1 << 8));
////		}else{
////			GPIO_ClearPinsOutput(GPIOC, (1 << 8));
////		}
////	}
//	while (1) {
//		if (GPIO_PinRead(GPIOA, pin_sw_1)) {
////			GPIO_PortSet(PORTE, (1 << pin_led_1));
//			GPIO_PinWrite(GPIOE, pin_led_1, 1);
//		} else {
//			GPIO_PortClear(GPIOE, (1 << pin_led_1));
//		}
//
//		if(GPIO_PinRead(GPIOA, pin_sw_2)) {
////			GPIO_SetPinsOutput(PORTE, (1 << pin_led_2));
//			GPIO_PinWrite(GPIOE, pin_led_2, 1);
//		}else {
////			GPIO_ClearPinsOutput(PORTE, (1 << pin_led_1));
////			GPIO_ClearPinsOutput(PORTE, (1 << pin_led_2));
//			GPIO_PortClear(GPIOE, (1 << pin_led_2));
//		}
//	}
//    return 0 ;
//}
