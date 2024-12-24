#ifndef _usart_H
#define _usart_H
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "stdio.h"
void Usart1_init(void);
void USART1_IRQHandler(void);

#endif
