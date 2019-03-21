#include<stm32f10x.h>
#include<stm32f10x_rcc.h>
#include "time_stm32.h"

static void __empty() {
	// Empty
}
void SysTick_HandlerV(void) __attribute__ ((weak, alias("__empty")));


void delay_ms(uint32_t time_ms){
	uint32_t currTime = millis();
	while((millis() - currTime) < time_ms);
}

void delay_us(uint32_t time_us){
	uint32_t currTime = micros();
	while((micros() - currTime) < time_us);
}

void Time_Init(){
	if (SysTick_Config(SystemCoreClock/1000))
		while(1);
}

void SysTick_Handler(void){
    SysTick_HandlerV();
	milliseconds++;	
}