#ifndef _key_H
#define _key_H
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#define KEY0_press 1
#define KEY1_press 2
#define WK_press   3

void Key_init(void);
u8 KEY_Scan(u8 mode);


#endif
