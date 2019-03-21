#ifndef _TIME_STM32_H
#define _TIME_STM32_H

volatile uint32_t milliseconds;
volatile uint32_t microseconds;

void Time_Init();
void delay_ms(uint32_t time_ms);
void delay_us(uint32_t time_us);

static inline uint32_t millis(void){
    return milliseconds;
}

static inline uint32_t micros(void)
{
    uint32_t temp_ms;
    uint32_t tick_cnt;
    uint32_t microseconds;

     do{
         tick_cnt = SysTick->VAL;
         temp_ms = millis();
     } while (temp_ms != millis());
    //temp_ms = millis();
    microseconds = temp_ms*1000 + (1000 - tick_cnt/72); 
    return microseconds;
}

#endif