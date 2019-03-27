file:///home/jefferson/stm32f1_stdper/Projects/blinkLED_3/src/main.c
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "time_stm32.h"

uint32_t tWaitMs = 1000;
uint32_t previousMillis = 0;

int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //Enable Peripheral Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    //Configure Pins
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //Configure sysTick timer via time_stm32.h
    Time_Init();
    while (1)
    {
        static int ledval = 0;
        uint32_t curentMillis = millis();

        if(curentMillis-previousMillis)
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (ledval) ? Bit_SET : Bit_RESET);
        ledval = 1 - ledval;
    }
    return 0;
}

void SysTick_HandlerT(void)
{
    
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    while (1);
}
#endif