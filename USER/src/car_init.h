#ifndef _CAR_INIT_H_
#define _CAR_INIT_H_
#include "gec_gpio.h"
#include "gec_time.h"
#include <stdio.h>
#include "gec_uart.h"
#include "gec_int.h"

void gec_gpio_init(void);//配置管脚的工作模式
void car_go(void);//小车向前行驶
void car_stop(void);//小车停止行驶
void car_back(void);//小车向后行驶
void car_left(void);//小车向左行驶
void car_right(void);//小车向右行驶
void car_inright(void);//小车向右倒车
void car_inleft(void);//小车向左倒车
void infrared_detecton(void);//红外循迹，使小车沿黑色轨迹行驶
void car_avoid(void);//红外检测障碍物，使小车正常行驶
void uart_init(void);//串口初始化
void uart_init_do (void);//蓝牙串口控制小车


#endif
