/*
 * BlinkLED_1.c - Blinks PC13 board LED using a blocking delay
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

void Delay(uint32_t nTime);

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
		
	while (1){
		GPIO_WriteBit(GPIOC, GPIO_Pin_13,Bit_SET);
		Delay(500);
		GPIO_WriteBit(GPIOC, GPIO_Pin_13,Bit_RESET);
		Delay(500);
    }
}

//Timer Code
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime){
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

void SysTick_Handler(void){
	if(TimingDelay != 0x00)
		TimingDelay--;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){
	/*Infinite Loop*/
	/*Use GDB to find out why we're here*/
	while(1);
}
#endif
