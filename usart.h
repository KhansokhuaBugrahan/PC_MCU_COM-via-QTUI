/*
 * usart.h
 *
 *  Created on: Jan 6, 2025
 *      Author: khans
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f4xx.h"

#define			USART6_CLOCK_ENABLE()			(RCC->APB2ENR |= (1u << 5))
#define			USART6_CLOCK_DISABLE()			(RCC->APB2ENR &= ~(1u << 5))


typedef struct {

	volatile uint32_t USART_SR;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR;
	volatile uint32_t USART_CR1;
	volatile uint32_t USART_CR2;
	volatile uint32_t USART_CR3;
	volatile uint32_t USART_GTPR;

}USART_RegDef_t;

#define 		USART6			((USART_RegDef_t*)(USART6_BASE_ADDR))

#define 		USART6_ENABLE()		(USART6->USART_CR1 |= (1u << 13))
#define 		USART6_DISABLE()	(USART6->USART_CR1 &= ~(1u << 13))

#define 		USART6_TRANSMIT_ENABLE()	(USART6->USART_CR1 |= (1u << 3))
#define 		USART6_TRANSMIT_DISABLE() (USART6->USART_CR1 &= ~(1u << 3))

#define 		USART6_RECEIVE_ENABLE()	(USART6->USART_CR1 |= (1u << 2))

/*      1000 = 8 mantissa	0.6805 x 16 = 10.88 ~= 11 = 1011
 * 		10001011 = 139    16 Mhz APB2 USART1   115200 baudrate
 */
#define 		USART6_SET_BAUDRATE_115200()	(USART6->USART_BRR = 139)

#define			USART6_TXE_BIT()				(USART6->USART_SR)

void usart6Init(void);
void usart6SendString(const char* data);
void usart6WriteByte(const uint8_t data);
char usart6GetChar(void);
#endif /* USART_H_ */
