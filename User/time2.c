#include "public.h"

int traffic_light[3][3] = {
    {10, 4, 10},//平常
    {12, 4, 8},//车流量比较多
    {8, 4, 12}//车流量比较少
};
char* light_state[3] = {"Green", "Yellow", "Red"};
int count;
extern int cycle;
int phase = 0;
int led_state = 0;
int traffic;
void Timer2_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 9999;
    TIM_TimeBaseStructure.TIM_Prescaler = 7199;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        if (count > 0) {
            count--;
        }
				
				
        if (phase == 0) {
            Led_on("LED0");
            Led_off("LED1");
        } else if (phase == 1) {
            if(led_state == 0) Led_off("LED0");
						else Led_on("LED0");
						led_state =!led_state;
            Led_off("LED1");
        } else if (phase == 2) {
            Led_off("LED0");
            Led_on("LED1");
        }
				
				
        if (count == 0) {
						phase++;
            if (phase >= 3) {
                phase = 0;
								traffic = cycle;
						}
            count = traffic_light[traffic][phase];
        }
    }
}

