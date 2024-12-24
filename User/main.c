#include "public.h"
extern int count;
extern int traffic_light[3][3];
extern int traffic;
int main(void) {
		count = traffic_light[0][0];
		traffic = 0;
		Led_init();
    Usart1_init();
    Key_init();
    EXTI_GPIOE3_init();
    Timer2_Init();
		Led_on(LED0);
    while (1) {
    }
}
