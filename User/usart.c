#include "usart.h"
#include <stdio.h>
#include "Delay.h"

#if 1
#pragma import(__use_no_semihosting)             
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f) {
    USART_SendData(USART1, (uint8_t) ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}
#endif
int cycle = 0;
void Usart1_init(void)
{
    
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  
	
    GPIO_InitTypeDef GPIO_InitStruct;
	
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		
		USART_InitTypeDef USART_InitStruct;
	
	  USART_InitStruct.USART_BaudRate=115200;
		USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		USART_InitStruct.USART_Parity=USART_Parity_No;
		USART_InitStruct.USART_StopBits=USART_StopBits_1;
		USART_InitStruct.USART_WordLength=USART_WordLength_8b;
		USART_Init (USART1,&USART_InitStruct);
	  USART_Cmd (USART1,ENABLE);
		
		
		
		
		NVIC_InitTypeDef NVIC_InitStruct;
		
		NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
		
		NVIC_Init(&NVIC_InitStruct);
		
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}
		
int fgetc(FILE *f)
{
		while (USART_GetITStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        char r = (char)USART_ReceiveData(USART1);
        if(r == '1') cycle = 1;
				else if(r == '2') cycle = 2;
    }
}





