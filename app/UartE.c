#include "UartE.h"



uint8_t buff_1[255] = {0};
uint8_t buff_2[255] = {0};

ring_buffer_t r_buf;
uint8_t r_buff[4096] = {0};
uint8_t print_buff[10240*10] = {0};

uint32_t cnt_t = 0;

void uartE_DMA_Init(int32_t baud)
{
	switch(baud)
	{
		case 921600:
			NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud921600; 
			break;
		case 460800:
			NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud460800; 
			break;
		case 250000:
			NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud250000; 
			break;
		case 230400:
			NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud230400; 
			break;
		default:
			NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud115200; 
	}
	
	NRF_UART0->PSELRXD = UARTE_RXD;          
	NRF_UART0->PSELTXD = UARTE_TXD; 

	NRF_UARTE0->CONFIG = 0x00;
	
	NRF_UARTE0->RXD.PTR = (uint32_t)(buff_1); 								//配置DMA接收缓冲区
	NRF_UARTE0->RXD.MAXCNT = RX_BUFF_SIZE;   								//配置DMA接收长度 
	
	NRF_UARTE0->SHORTS = 1<<5; 

	NRF_UARTE0->ENABLE = 0x08;

	NRF_UARTE0->EVENTS_ENDRX = 0;
	NRF_UARTE0->EVENTS_RXSTARTED = 0;
	
	NRF_UARTE0->INTEN = 0;
	NRF_UARTE0->INTEN = 1<<4;      						//ENDRX
	NRF_UARTE0->INTEN |= 1<<19;								//RXSTARTED
	NVIC_SetPriority(UARTE0_UART0_IRQn, 0);
	NVIC->ISER[UARTE0_UART0_IRQn>>5] |= 0x01<<(UARTE0_UART0_IRQn&0x1f); 		//使能UARTE中断	
	
	NRF_UARTE0->TASKS_STARTRX = 1;
	
}


void UARTE0_UART0_IRQHandler__(void)
{
		static uint64_t cnt = 0;
	
		if(NRF_UARTE0->EVENTS_ENDRX)
		{
			NRF_UARTE0->EVENTS_ENDRX = 0;			
			if ((cnt%2)==1)									// buff_1
			{
				for (uint8_t cycle=0; cycle< RX_BUFF_SIZE;cycle++)    //NRF_UARTE0->RXD.MAXCNT
				{
					ring_buffer_write_byte(&r_buf, buff_1[cycle]);
				}					
			}
			else
			{
				for (uint8_t cycle=0; cycle< RX_BUFF_SIZE;cycle++)
				{
					ring_buffer_write_byte(&r_buf, buff_2[cycle]);
				}			
			}
		}
		
		if(NRF_UARTE0->EVENTS_RXSTARTED)
		{			
			NRF_UARTE0->EVENTS_RXSTARTED = 0;		

			cnt++;
			if((cnt%2)==1)
			{
				NRF_UARTE0->RXD.PTR = (uint32_t)(buff_2); 					
			}
			else
			{
				NRF_UARTE0->RXD.PTR = (uint32_t)(buff_1); 										
			}			
		}
}

void ringbuffer_creat(void)
{
	ring_buffer_creat(&r_buf, r_buff, sizeof(r_buff) );					// ring_buffer_creat(&r_buf, r_buff, sizeof(r_buff)-1);	
}

void readbuff(void)
{
			uint16_t temp = ring_buffer_get_length(&r_buf);
			if (temp > 0)
			{
				LED5_Open();
				for(uint16_t cycle=0; cycle< temp;cycle++)
				{
					ring_buffer_read_byte(&r_buf, print_buff+cycle+cnt_t);
				}
				cnt_t = cnt_t + temp;
				LED5_Close();
			}
			//return cnt_t;
}

