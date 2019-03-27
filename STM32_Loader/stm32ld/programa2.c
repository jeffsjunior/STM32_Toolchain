#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <time_stm32.h>

#define Micros

#ifdef Millis
uint32_t tWaitMillis = 1;
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

void SysTick_HandlerT(void)
{
    
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    while (1);
}
#endif