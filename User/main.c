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
u16 s_xfact;      //用于记录特征点位置
u16 s_yfact;

 int main(void)
 {	 
//    u8 highByte = 0xAA;
//    u8 lowByte = 0xBB;
    
	u16 pixcnt=0;				//像素统计
	u16 linecnt=0;//行数统计 

	delay_init();	    	 //延时函数初始化	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();		  			//初始化与LED连接的硬件接口
	LCD_Init();			   		//初始化LCD     
    my_mem_init(SRAMIN);
	POINT_COLOR=RED;      
	LCD_Scan_Dir(U2D_L2R);									   						    
	while(OV7670_Init())//初始化OV7670
	{
	}
	delay_ms(1500);	 		 
	OV7670_Window_Set(10,174,240,320);	//设置窗口  			    		    
	LCD_Clear(BLACK);
	while(1)
	{	
        delay_ms(1000);
        LCD_SetCursor(0x00,0x0000);	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		while(OV7670_VSYNC==0);//
		while(OV7670_VSYNC==1);//		只有在VSYNC为低时，才传输数据	
//****************************拍摄一张图片数据开始*******************************
        for(linecnt = 0; linecnt < 240; linecnt++)  // 遍历240行
        {
            while(OV7670_HREF == 0);  // 等待HREF信号为高，表示数据有效
            for(pixcnt = 0; pixcnt < 320; pixcnt++)  // 每行320个像素
            {
                while(OV7670_PCLK == 0);  // 等待像素时钟PCLK为高
                Row[pixcnt] = GPIOC->IDR & 0xFF;// 读取低字节
                while(OV7670_PCLK == 1);  // 等待PCLK为低
                Row[pixcnt] <<= 8;// 左移8位，准备存储高字节
                while(OV7670_PCLK == 0);  // 等待PCLK为高
                Row[pixcnt] |= GPIOC->IDR & 0xFF;// 读取高字节
                
                while(OV7670_PCLK == 1);  // 等待PCLK为低
//                Color[linecnt][pixcnt] = Row[pixcnt];
                LCD->LCD_RAM = Row[pixcnt];  // 显示图像数据
                
            }
        }
//****************************拍摄一张图片数据结束*******************************
        
//****************************发送一张图片数据结束*******************************
        Send_Frame_Header();  // 发送帧头
        for (linecnt = 0; linecnt < 240; linecnt++)  // 遍历240行
        {
            delay_ms(10);
            for (pixcnt = 0; pixcnt < 320; pixcnt++)  // 每行320个像素
            {
                uint16_t pixel = LCD_ReadPoint(pixcnt,linecnt);  // 读取LCD显存中的像素数据
                uint8_t high_byte = (pixel >> 8) & 0xFF;  // 获取高8位
                uint8_t low_byte = pixel & 0xFF;          // 获取低8位

                // 发送高8位和低8位
                Send_Image_Data(&high_byte, 1);
                Send_Image_Data(&low_byte, 1);
            }
        }
        Send_Frame_Tail();  // 发送帧尾
//************************************************************************
	   	   										
        
    }
}
