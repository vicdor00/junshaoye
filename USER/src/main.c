#include <stdio.h>
#include "gec_gpio.h"
#include "gec_int.h"
#include "gec_time.h"
#include "gec_uart.h"
#include "gec_init.h"
#include "fashion_star_uart_servo.h"
#include "ring_buffer.h"
#include "uart.h"
#include "car_init.h"


/*李政明专属代码，不可盗用，若经发现，严惩不贷*/
int main()
{
//    int num;	
	gec_gpio_init();//引脚初始化
	car_stop();
	uart_init();//串口初始化
	while(1)
	{
		
	}
}

