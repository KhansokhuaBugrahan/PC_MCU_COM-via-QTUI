/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include <stm32f4xx.h>
#include <stdint.h>
#include <stdio.h>
#include "armcortexm4.h"
#include "gpio.h"
#include "usart.h"
#include "adc.h"
#include "i2c.h"
#include "i2clcd.h"


float digitalToTemperature(const uint16_t adcValue)
{
	float voltage = ( (3.3) * adcValue) / 4095.;
	float temperature = voltage / 0.01;

	return temperature;
}

int main(void)
{
				 fpuInit();
				 sysTickInit();


     	 	 	 	 	 // GPIO LEDs CONFIG
     	GPIO_Handle_t LEDs_D0_TO_D7[8] = {
    		   	   	   	   	   	   	   	   	{
    		   	   	   	   	   	   	   	    .PORTNAME = GPIOD,
											.PINCONF.PIN = GPIO_PIN_0,
											.PINCONF.MODE = GPIO_MODE_OUTPUT,
											.PINCONF.OTYPE = GPIO_OTYPE_PP,
											.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
											.PINCONF.PUPD = GPIO_PUPD_PD,
											.PINCONF.AF = GPIO_AF_NO
       	   	   	   	   	   	   	   	   	   	},

										 };


				for (int pin = 0;  pin < BYTE_SIZE; ++pin)
				{
					 LEDs_D0_TO_D7[pin] = LEDs_D0_TO_D7[0];
					 LEDs_D0_TO_D7[pin].PINCONF.PIN = pin;
					 gpioInit(&LEDs_D0_TO_D7[pin]);
				}


     	 	 	 	 	 //ADC CONFIG
     	 	 	 GPIO_Handle_t ADC_PA2 = {  .PORTNAME = GPIOA,
     	 	 			 	 	 	 	 	.PINCONF.PIN = GPIO_PIN_2,
											.PINCONF.MODE = GPIO_MODE_ANALOG,
											.PINCONF.OTYPE = GPIO_OTYPE_PP			,
											.PINCONF.OSPEED = GPIO_OSPEED_VHIGH,
											.PINCONF.PUPD = GPIO_PUPD_NO,
											.PINCONF.AF = AFNO
         		 					     };
         		 gpioInit(&ADC_PA2);
         		 adc1Configuration(ADC_RESOLUTION_12, ADC_MODE_CONTINUOUS_CONV, ADC_CHANNEL_2, ADC_SAMPLING_144_CYCLE);
         		 adc1SequenceLength(ADC_CONVERSION_LENGTH_1);
         		 adc1ChannelSequence(ADC_CHANNEL_2, ADC_CHANNEL_SEQUENCE_1);





         		 	 	 // USART CONFIG
         		GPIO_Handle_t USART_RX_PC7 = {  .PORTNAME = GPIOC,
												.PINCONF.PIN = GPIO_PIN_7,
												.PINCONF.MODE = GPIO_MODE_ALTARNATE,
												.PINCONF.OTYPE = GPIO_OTYPE_PP,
												.PINCONF.OSPEED = GPIO_OSPEED_VHIGH,
												.PINCONF.PUPD = GPIO_PUPD_NO,
												.PINCONF.AF = AF8

											 };
				GPIO_Handle_t USART_TX_PC6 = {  .PORTNAME = GPIOC,
												.PINCONF.PIN = GPIO_PIN_6,
												.PINCONF.MODE = GPIO_MODE_ALTARNATE,
												.PINCONF.OTYPE = GPIO_OTYPE_PP			,
												.PINCONF.OSPEED = GPIO_OSPEED_VHIGH,
												.PINCONF.PUPD = GPIO_PUPD_NO,
												.PINCONF.AF = AF8
											 };
				gpioInit(&USART_TX_PC6);
				gpioInit(&USART_RX_PC7);


				GPIO_Handle_t I2C1_SCL_PB6 = {  .PORTNAME = GPIOB,
												.PINCONF.PIN = GPIO_PIN_6,
												.PINCONF.MODE = GPIO_MODE_ALTARNATE,
												.PINCONF.OTYPE = GPIO_OTYPE_OD,
												.PINCONF.OSPEED = GPIO_OSPEED_VHIGH,
												.PINCONF.PUPD = GPIO_PUPD_PU,
												.PINCONF.AF = AF4

											 };
			    GPIO_Handle_t I2C1_SDA_PB7 = {  .PORTNAME = GPIOB,
											.PINCONF.PIN = GPIO_PIN_7,
											.PINCONF.MODE = GPIO_MODE_ALTARNATE,
											.PINCONF.OTYPE = GPIO_OTYPE_OD,
											.PINCONF.OSPEED = GPIO_OSPEED_VHIGH,
											.PINCONF.PUPD = GPIO_PUPD_PU,
											.PINCONF.AF = AF4
			    							 };
			    gpioInit(&I2C1_SCL_PB6);
			    gpioInit(&I2C1_SDA_PB7);



				/*
				 * Peripheral Inits
				 */
				adc1Init();
				usart6Init();

				i2cInit();
				lcdInit();

				lcdPutCursor(0, 3);
			    lcdSendString ("TEMPERATURE");


         		 while(1)
         		 {
         			if(USART6->USART_SR & (1u << 5)) // check  whether data received or not
         			{
         				uint8_t receivedData = USART6->USART_DR;
         				gpioWritePortLowByte(GPIOD, GPIO_PIN_RESET);
         				gpioWritePortLowByte(GPIOD, receivedData);
         			}

         			uint16_t adcValue = adc1ReadValue();
         			float temperature = digitalToTemperature(adcValue) / 2;

         			char stringRepresantationOfTemperature[7];

         			sprintf(stringRepresantationOfTemperature, "%.2f", temperature);
         			usart6SendString(stringRepresantationOfTemperature);
         			lcdPutCursor(1, 0);
         			lcdSendString(LCD_CLEAR_LINE);
         			lcdPutCursor(1, 5);
         			lcdSendString(stringRepresantationOfTemperature);
         			lcdSendData((char)223);
         			lcdSendData('C');
         			delay_ms(1000);
         		 }
}
