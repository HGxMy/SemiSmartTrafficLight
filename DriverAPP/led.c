#include "led.h"
void Led_init(void)
{
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	 GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
   GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
   GPIO_Init(GPIOB,&GPIO_InitStruct);
     
	 GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
   GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
   GPIO_Init(GPIOE,&GPIO_InitStruct);
	
}
void Led_on(char *ch)
{
	if(strcmp(ch,LED0)==0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	if(strcmp(ch,LED1)==0)
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}
	
void Led_off(char *ch)
{
	if(strcmp(ch,LED0)==0)
		  GPIO_SetBits(GPIOB,GPIO_Pin_5);
	if(strcmp(ch,LED1)==0)
		  GPIO_SetBits(GPIOE,GPIO_Pin_5);
}
void Led_toggle(char *ch) {
    if (strcmp(ch, "LED0") == 0) {
        if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5) == Bit_SET) {
            GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        } else {
            GPIO_SetBits(GPIOB, GPIO_Pin_5);
        }
    }
    if (strcmp(ch, "LED1") == 0) {
        if (GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_5) == Bit_SET) {
            GPIO_ResetBits(GPIOE, GPIO_Pin_5);
        } else {
            GPIO_SetBits(GPIOE, GPIO_Pin_5);
        }
    }
}
