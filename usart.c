/*
 * usart.c
 *
 *  Created on: Jan 6, 2025
 *      Author: khans
 */
#include "usart.h"
#include "armcortexm4.h"
void usart6Init(void)
{
	USART6_CLOCK_ENABLE();
	USART6_ENABLE();
	USART6_SET_BAUDRATE_115200();
	USART6_TRANSMIT_ENABLE();
	USART6_RECEIVE_ENABLE();
}
void usart6WriteByte(const uint8_t data)
{

	while(!(USART6->USART_SR & (1u << 7)))
		; // wait for data to be transmitted into shift register

		USART6->USART_DR = data; // send the single byte

	while(!(USART6->USART_SR & (1u << 6)))
		; // wait for transmission complete bit to be set


}
void usart6SendString(const char* data)
{
	while(*data)
		usart6WriteByte(*data++);

}
char usart6GetChar(void)
{
	while(!(USART6->USART_SR & (1u << 5)));
	return USART6->USART_DR;
}
