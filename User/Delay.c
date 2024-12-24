#include "Delay.h"
void Delay_ms(uint16_t u16ms)
{
		 for(volatile uint32_t i = 0; i < 8000*u16ms;i++)  __asm("NOP");
}
