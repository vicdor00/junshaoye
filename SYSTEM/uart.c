#include "gec_uart.h"
#include "gec_int.h"
#include "uart.h"

#if 0
volatile  char  USART1_RecvBuf[128] = {0}; //����USART1���յ�����
volatile  char  USART2_RecvBuf[128] = {0}; //����USART2���յ�����

volatile  uint32_t  USART1_RecvCnt = 0;  //��¼USART1���յ����ݸ���
volatile  uint32_t  USART2_RecvCnt = 0;  //��¼USART2���յ����ݸ���

volatile  uint32_t  USART1_RecvFlag = 0; //USART1�Ľ��ձ�־  1 ��Ч  0 ��Ч
volatile  uint32_t  USART2_RecvFlag = 0; //USART2�Ľ��ձ�־  1 ��Ч  0 ��Ч
#endif

#if USART1_ENABLE
    uint8_t usart1SendBuf[USART_SEND_BUF_SIZE+1];
	uint8_t usart1RecvBuf[USART_RECV_BUF_SIZE+1];
	RingBufferTypeDef usart1SendRingBuf;
	RingBufferTypeDef usart1RecvRingBuf;
	Usart_DataTypeDef usart1;
	 
#endif

#if USART2_ENABLE
    uint8_t usart2SendBuf[USART_SEND_BUF_SIZE+1];
	uint8_t usart2RecvBuf[USART_RECV_BUF_SIZE+1];
	RingBufferTypeDef usart2SendRingBuf;
	RingBufferTypeDef usart2RecvRingBuf;
	Usart_DataTypeDef usart2;
#endif

void uart1_isr(void)
{
    uint8_t ucTemp;
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        // �Ӵ��ڶ�ȡһ���ַ�
        ucTemp = USART_ReceiveData(USART1);
        // �µ��ַ���ӵ����ڵĻ��λ��������
        RingBuffer_Push(usart1.recvBuf, ucTemp);
    }
}

void uart2_isr(void)
{
	uint8_t ucTemp;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{
		// �Ӵ��ڶ�ȡһ���ַ�
		ucTemp = USART_ReceiveData(usart2.pUSARTx);
		// �µ��ַ���ӵ����ڵĻ��λ��������
		RingBuffer_Push(usart2.recvBuf, ucTemp);
	}
}

void uart1_init(uint32_t bard_rate)
{
	Gec_UART_Init(USART1 ,bard_rate,USART_Parity_No, 8,USART_StopBits_1);
	Gec_Int_Register(BSP_INT_ID_USART1, uart1_isr);
	
	Gec_Int_Enable(BSP_INT_ID_USART1);
	
	
	#if USART1_ENABLE	
    // ��ֵ�ṹ��usartָ��
    usart1.pUSARTx = USART1;
   
    // ��ʼ��������(���ζ���)
    RingBuffer_Init(&usart1SendRingBuf,  USART_SEND_BUF_SIZE, usart1SendBuf);
    RingBuffer_Init(&usart1RecvRingBuf, USART_RECV_BUF_SIZE,  usart1RecvBuf);
    usart1.recvBuf = &usart1RecvRingBuf;
    usart1.sendBuf = &usart1SendRingBuf;
	#endif
	
}

void uart2_init(uint32_t bard_rate)
{
	
	Gec_UART_Init(USART2 ,bard_rate,USART_Parity_No, 8,USART_StopBits_1);
	Gec_Int_Register(BSP_INT_ID_USART2, uart2_isr);
	Gec_Int_Enable(BSP_INT_ID_USART2);
	
	#if USART2_ENABLE
		// ��ֵ�ṹ��usartָ��
        usart2.pUSARTx = USART2;
		// ��ʼ��������(���ζ���)
		RingBuffer_Init(&usart2SendRingBuf,  USART_SEND_BUF_SIZE, usart2SendBuf);
		RingBuffer_Init(&usart2RecvRingBuf, USART_RECV_BUF_SIZE,  usart2RecvBuf);
		usart2.recvBuf = &usart2RecvRingBuf;
		usart2.sendBuf = &usart2SendRingBuf;    
	#endif
}

// �����ڷ��ͻ�����������ȫ������ȥ
void Usart_SendAll(Usart_DataTypeDef *usart)
{
	uint8_t value;
	while(RingBuffer_GetByteUsed(usart->sendBuf))
	{
		value = RingBuffer_Pop(usart->sendBuf);
		USART_SendData(usart->pUSARTx, value);
		while (USART_GetFlagStatus(usart->pUSARTx, USART_FLAG_TXE) == RESET);	
	}
}
