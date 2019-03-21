/*
 * BlinkLED_2.c - Blinks PC13 board LED using a nonblocking delay
 * 
 * Copyright (C) 2019  Jefferson Silveira
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Original Author: Geoffrey Brown (Discovering the STM32 Microcontroller)
 * Modified by: Jefferson Silveira 
 */		

#include<stm32f10x.h>
#include<stm32f10x_rcc.h>
#include<stm32f10x_gpio.h>

volatile uint32_t milliseconds = 0;

uint32_t tWaitMs = 10;
uint32_t previousMillis = 0;


static inline uint32_t millis(void){
    return milliseconds;
}

int main(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	//Enable Peripheral Clocks
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//Configure Pins
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//Configure SysTick Timer
	if (SysTick_Config(SystemCoreClock/1000))
		while(1);

  while (1)
  {
		static int ledval = 1;
		uint32_t curentMillis = millis();

		if(curentMillis-previousMillis >= tWaitMs){
				previousMillis = curentMillis;
				GPIO_WriteBit(GPIOC, GPIO_Pin_13, (ledval) ? Bit_SET : Bit_RESET);
				ledval = 1 - ledval;
		}
  }
    return 0;
}

void SysTick_Handler(void){
	milliseconds++;	
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){
	/*Infinite Loop*/
	/*Use GDB to find out why we're here*/
	while(1);
}
#endif
