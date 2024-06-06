#include "car_init.h"
#include "gec_gpio.h"
#include "gec_time.h"
#include "gec_uart.h"
#include "gec_int.h"
#include <stdio.h>


/*
	gec_gpio_init:配置管脚的工作模式
	Param： None
	Retval：None
*/
void gec_gpio_init(void)
{
	//将PA4,5,6,7
    Gec_GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_MODE_OUT_PP);
	Gec_GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_MODE_OUT_PP);
	Gec_GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_MODE_OUT_PP);
	Gec_GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_MODE_OUT_PP);
	//将PB8,9设置为上拉输入
	Gec_GPIO_Init(GPIOB, GPIO_Pin_12, GPIO_MODE_IN_PULLUP);
	Gec_GPIO_Init(GPIOB, GPIO_Pin_13, GPIO_MODE_IN_PULLUP);
	
}

/*
	car_go:小车向前行驶
	Param： None
	Retval: None
*/
void car_go(void)
{
	//小车左，右轮向前行驶
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_0, 1);//PB0设置为1
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_1, 0);//余下同理
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_3, 0);
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_4, 1);
}

/*
	car_go:小车停止行驶
	Param： None
	Retval：None
*/
void car_stop(void)
{
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_0, 0);//PB0设置为0
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_1, 0);//余下同理
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_3, 0);
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_4, 0);
}

/*
	car_go:小车向后行驶
	Param： None
	Retval：None
*/
void car_back(void)
{
	//小车左，右轮向后行驶
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_0, 0);//PB0设置为0
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_1, 1);//余下同理
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_3, 1);
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_4, 0);
}

/*
	car_go:小车向左行驶
	Param： None
	Retval：None
*/
void car_left(void)
{
	//小车右轮向前行驶
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_0, 1);//PB0设置为1
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_1, 0);//余下同理
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_3, 0);
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_4, 0);
}

/*
	car_go:小车向右行驶
	Param： None
	Retval：None
	*/
void car_right(void)
{
	//小车左轮向前行驶
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_0, 0);//PB0设置为0
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_1, 0);//余下同理
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_3, 0);
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_4, 1);
}

/*
	car_inleft:小车向右倒车
	Param： None
	Retval：None
*/
void car_inright(void)
{
	//小车左轮向后行驶
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_0, 0);//PB0设置为0
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_1, 0);//余下同理
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_3, 1);
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_4, 0);
}

/*
	car_inright:小车向左倒车
	Param： None
	Retval：None
*/
void car_inleft(void)
{
	//小车右轮向后行驶
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_0, 0);//PB0设置为0
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_1, 1);//余下同理
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_3, 0);
   Gec_GPIO_Set_Value(GPIOB, GPIO_Pin_4, 0);
}

/*
	infrared_detecton:红外循迹，使小车沿着黑色轨迹行驶
	Param： None
	Retval：None
*/
void infrared_detecton(void)
{
	int A,B;
	A=Gec_GPIO_Get_Value(GPIOB,GPIO_Pin_12);
	B=Gec_GPIO_Get_Value(GPIOB,GPIO_Pin_13);
	if(A==0 && B==0)//小车双轮没压线
	{
		car_go();	//小车向前行驶	
		mdelay(17);
		car_stop();
		mdelay(15);
	
	}
	
	if(A==1 && B==0)//小车右轮压线
	{
		car_right();//小车向右行驶
		mdelay(16);
		car_stop();
		mdelay(15);
	}
	
	if(A==0 && B==1)//小车左轮压线
	{
		
		car_left();//小车向左行驶
		mdelay(16);
		car_stop();
		mdelay(15);
	}
	
	if(A==1 && B==1)//小车双轮压线
	{
		car_stop();//小车停止
	}
}

/*
	car_avoid:躲避障碍物，小车正常行驶
	param： None
	Retval：None
*/
void car_avoid(void)
{
	int A,B;//定义变量A,B来接受PB9,8的值
	A=Gec_GPIO_Get_Value(GPIOB,GPIO_Pin_12);
	B=Gec_GPIO_Get_Value(GPIOB,GPIO_Pin_13);

	if(A==1 && B==1)//A,B都为1，无障碍物，小车向前行驶
	{
		car_go();	//小车向前行驶	
	
	}
	
	if(B==0 && A==1)//左边有障碍物
	{
		car_inleft();//小车向左倒车
		mdelay(500);
		car_right();//小车向右行驶
		mdelay(500);
	}
	   
	if(B==1 && A==0)//右边有障碍物
	{
		car_inright();//小车向右倒车
		mdelay(500);
		car_left();//小车向左行驶
		mdelay(500);
	}
	   
	if(B==0 && A==0)//前面有障碍物
	{
	    car_back();//小车后退
		mdelay(300);
		car_inright();//小车向右倒车
		mdelay(300);	   
	}		
}

/*
	uart_init_do:蓝牙控制小车驱动
	Param；None
	Retval；None
*/
void uart_init_do(void)
{
	 int num;//num来接收串口1的字节数量
	 unsigned char data[20];//数组用来储存串口1传来的字符
	 num=Gec_UART_Read(USART1,data,1);
		if(num==1&&data[0]=='a')//字节数量为1且数组data第一位为'a'，小车向前走
		{
		  car_go();
		}
		
		if(num==1&&data[0]=='b')//余下同理
		{
		  car_back();
		}
		
		if(num==1&&data[0]=='c')
		{
		  car_left();
		}
		
		if(num==1&&data[0]=='d')
		{
		  car_right();
		}
		
		if(num==1&&data[0]=='e')
		{
		  car_stop();
		}
		
		if(num==1&&data[0]=='f')
		{
		  car_inleft();
		}
		
		if(num==1&&data[0]=='g')
		{
		  car_inright();
		}
}

/*
	uart_init；将串口1初始化
	Param； None
	Retval：None
*/
void uart_init(void)
{
	Gec_UART_Init(USART1,9600,USART_Parity_No,8,USART_StopBits_1);//配置串口1的模式
	Gec_Int_Register(BSP_INT_ID_USART1,uart_init_do);
	Gec_Int_Enable(BSP_INT_ID_USART1);//串口使能
}
	


