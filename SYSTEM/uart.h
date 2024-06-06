#ifndef  __UART_H__
#define  __UART_H__
#include "ring_buffer.h"

#define USART_RECV_BUF_SIZE 500
#define USART_SEND_BUF_SIZE 500


//串口使能标志
#define USART1_ENABLE 1
#define USART2_ENABLE 1
#define USART3_ENABLE 0

typedef struct
{  
    USART_TypeDef *pUSARTx;
    // 发送端缓冲区
    RingBufferTypeDef *sendBuf;
	// 接收端缓冲区
    RingBufferTypeDef *recvBuf;
} Usart_DataTypeDef;

#if USART1_ENABLE
    extern Usart_DataTypeDef usart1;
    extern uint8_t usart1SendBuf[USART_SEND_BUF_SIZE+1];
	extern uint8_t usart1RecvBuf[USART_RECV_BUF_SIZE+1];
	extern RingBufferTypeDef usart1SendRingBuf;
	extern RingBufferTypeDef usart1RecvRingBuf;
#endif

#if USART2_ENABLE
	extern Usart_DataTypeDef usart2;
	extern uint8_t usart2SendBuf[USART_SEND_BUF_SIZE+1];
	extern uint8_t usart2RecvBuf[USART_RECV_BUF_SIZE+1];
	extern RingBufferTypeDef usart2SendRingBuf;
	extern RingBufferTypeDef usart2RecvRingBuf;
	

#endif

extern void uart1_init(uint32_t bard_rate);
extern void uart2_init(uint32_t bard_rate);
extern void Usart_SendAll(Usart_DataTypeDef *usart);
#endif

