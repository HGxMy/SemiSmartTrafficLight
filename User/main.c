#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "text.h"
#include "piclib.h"	
#include "string.h"		
#include "math.h"	 
#include "ov7670.h" 
#include "PicHandle.h"
 

 
u16 Row[320];
u16 s_xfact;      //���ڼ�¼������λ��
u16 s_yfact;

 int main(void)
 {	 
//    u8 highByte = 0xAA;
//    u8 lowByte = 0xBB;
    
	u16 pixcnt=0;				//����ͳ��
	u16 linecnt=0;//����ͳ�� 

	delay_init();	    	 //��ʱ������ʼ��	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   		//��ʼ��LCD     
    my_mem_init(SRAMIN);
	POINT_COLOR=RED;      
	LCD_Scan_Dir(U2D_L2R);									   						    
	while(OV7670_Init())//��ʼ��OV7670
	{
	}
	delay_ms(1500);	 		 
	OV7670_Window_Set(10,174,240,320);	//���ô���  			    		    
	LCD_Clear(BLACK);
	while(1)
	{	
        delay_ms(1000);
        LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		while(OV7670_VSYNC==0);//
		while(OV7670_VSYNC==1);//		ֻ����VSYNCΪ��ʱ���Ŵ�������	
//****************************����һ��ͼƬ���ݿ�ʼ*******************************
        for(linecnt = 0; linecnt < 240; linecnt++)  // ����240��
        {
            while(OV7670_HREF == 0);  // �ȴ�HREF�ź�Ϊ�ߣ���ʾ������Ч
            for(pixcnt = 0; pixcnt < 320; pixcnt++)  // ÿ��320������
            {
                while(OV7670_PCLK == 0);  // �ȴ�����ʱ��PCLKΪ��
                Row[pixcnt] = GPIOC->IDR & 0xFF;// ��ȡ���ֽ�
                while(OV7670_PCLK == 1);  // �ȴ�PCLKΪ��
                Row[pixcnt] <<= 8;// ����8λ��׼���洢���ֽ�
                while(OV7670_PCLK == 0);  // �ȴ�PCLKΪ��
                Row[pixcnt] |= GPIOC->IDR & 0xFF;// ��ȡ���ֽ�
                
                while(OV7670_PCLK == 1);  // �ȴ�PCLKΪ��
//                Color[linecnt][pixcnt] = Row[pixcnt];
                LCD->LCD_RAM = Row[pixcnt];  // ��ʾͼ������
                
            }
        }
//****************************����һ��ͼƬ���ݽ���*******************************
        
//****************************����һ��ͼƬ���ݽ���*******************************
        Send_Frame_Header();  // ����֡ͷ
        for (linecnt = 0; linecnt < 240; linecnt++)  // ����240��
        {
            delay_ms(10);
            for (pixcnt = 0; pixcnt < 320; pixcnt++)  // ÿ��320������
            {
                uint16_t pixel = LCD_ReadPoint(pixcnt,linecnt);  // ��ȡLCD�Դ��е���������
                uint8_t high_byte = (pixel >> 8) & 0xFF;  // ��ȡ��8λ
                uint8_t low_byte = pixel & 0xFF;          // ��ȡ��8λ

                // ���͸�8λ�͵�8λ
                Send_Image_Data(&high_byte, 1);
                Send_Image_Data(&low_byte, 1);
            }
        }
        Send_Frame_Tail();  // ����֡β
//************************************************************************
	   	   										
        
    }
}
