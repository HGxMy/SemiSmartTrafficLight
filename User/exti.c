#include "public.h"

extern int phase;
extern int count;
extern int cycle;
extern int traffic;
extern const char* light_state[3];

void EXTI_GPIOE3_init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);

    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    EXTI_InitTypeDef EXTI_InitStructure;

    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
}

void EXTI3_IRQHandler(void) {
    Delay_ms(10);
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
			if(traffic == cycle){
				switch(traffic){
					case 0:
						printf("Light: %s, Remaining Time: %d seconds >>正常车流量<<\r\n", light_state[phase],count);
						break;
					case 1:
						printf("Light: %s, Remaining Time: %d seconds >>拥堵时间段<<\r\n", light_state[phase],count);
						break;
					case 2:
						printf("Light: %s, Remaining Time: %d seconds >>稀疏时间段<<\r\n", light_state[phase],count);
						break;
				}
			}
			else{
				printf("Light: %s, Remaining Time: %d seconds >>正在修改红绿灯颜色<<\r\n", light_state[phase],count);
			}
			EXTI_ClearITPendingBit(EXTI_Line3);
    }
}
