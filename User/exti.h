#ifndef _exti_H
#define _exti_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
void EXTI_GPIOE3_init(void);
void EXTI3_IRQHandler(void);
#endif
