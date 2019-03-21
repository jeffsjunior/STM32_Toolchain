/*
 * BlinkLED_4.c - Blinks PC13 board LED using a nonblocking delay defined in
 * a library defined in the library directory
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

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "time_stm32.h"

#define Millis

#ifdef Millis
uint32_t tWaitMillis = 1000;
uint32_t previousMillis = 0;
#endif

#ifdef Micros
uint32_t tWaitMicros = 100;
uint32_t previousMicros = 0;
#endif

int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //Enable Peripheral Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    //Configure Pins
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //Configure sysTick timer via time_stm32.h
    Time_Init();
    while (1)
    {
        static int ledval = 1;
        #ifdef Millis
        uint32_t curentMillis = millis();

        if(curentMillis-previousMillis >= tWaitMillis){
            previousMillis = curentMillis;
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, (ledval) ? Bit_SET : Bit_RESET);
            ledval = 1 - ledval;
        }
        #endif
        #ifdef Micros
        uint32_t curentMicros = micros();
        if(curentMicros-previousMicros >= tWaitMicros){
            previousMicros = curentMicros;
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, (ledval) ? Bit_SET : Bit_RESET);
            ledval = 1 - ledval;
        }
        #endif
    }
    return 0;
}

void SysTick_HandlerV(void)
{
    //This function is called within SysTick_Handler used by time_stm32
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    while (1);
}
#endif