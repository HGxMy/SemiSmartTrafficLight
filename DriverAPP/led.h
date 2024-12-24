#include "stm32f10x_gpio.h"
#include "string.h"
#define LED0 "LED0"
#define LED1 "LED1"
void Led_init(void);
void Led_on(char *ch);
void Led_off(char *ch);
void Led_toggle(char *ch);
