#include <stdbool.h>   
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#include "led.h"
#include "key.h"
#include "rtc.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "ff.h"
#include "diskio_blkdev.h"
#include "nrf_block_dev_sdc.h"
#include "SDcardRW.h"
#include "UartE.h"

extern int timer_flag;
extern uint32_t cnt_t;

static void log_init(void)
{
	  ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}
static void UarteWirteToSD(char* fileName)
{
			LED4_Toggle();				
			if(cnt_t != 0)
				WirteToSD(fileName);
			cnt_t=0;
			timer_flag=0;	
}

int main(void)
{	
	log_init();
	LED_Init();
	KEY_Init();
	lfclk_config();
	rtc_config();
	fatfs_init();
	int32_t uarteBaud = fatfs_readconfig();
	uartE_DMA_Init(uarteBaud);
	char* Wirte_file = create_newfile();
	ringbuffer_creat();
	
	while(true)
	{
		readbuff();
		
  	if(timer_flag == 1)				
			UarteWirteToSD(Wirte_file);						
		
		if(KEY1_Down() == 0)
			printf_data(FILE_CONFIG);

		if(KEY2_Down() == 0)
			printf_data(Wirte_file);
		

	}
}
/********************************************END FILE**************************************/


