#include "key.h"
#include "stm32f10x.h"
#include "Delay.h"

void Key_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3; 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	  
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4; 
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0; 
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

 u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1;
    u8 key_value = 0;

    u8 KEY0 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3);
    u8 KEY1 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4);
    u8 WK = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

    if (mode == 1) key_up = 1;

    if (key_up && (KEY0 == 0 || KEY1 == 0 || WK == 0))
    {
        Delay_ms(10);
        key_up = 0;
        if (KEY0 == 0) key_value = KEY0_press;
        else if (KEY1 == 0) key_value = KEY1_press;
        else if (WK == 0) key_value = WK_press;
    }
    else if (KEY0 == 1 && KEY1 == 1 && WK == 1)
    {
        key_up = 1;
    }

    return key_value;
}
