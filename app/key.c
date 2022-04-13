#include "key.h"
#include "Board_Config.h"

#ifdef W02L

void KEY_Init(void)
{
  nrf_gpio_cfg_input(key_1,NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(key_2,NRF_GPIO_PIN_PULLUP);

}


uint8_t KEY1_Down()
{
	if( nrf_gpio_pin_read(key_1)== 0 )
	{
			nrf_delay_ms(200);
			if( nrf_gpio_pin_read(key_1)== 0 )
			{
				
				 while(nrf_gpio_pin_read(key_1)== 0 );   
						return 	0	; 						
				
			}
			else
				return 1;
	}
	else
		return 1;
}
uint8_t KEY2_Down()
{
		if( nrf_gpio_pin_read(key_2)== 0 )
			{
					nrf_delay_ms(200);
					if( nrf_gpio_pin_read(key_2)== 0 )
					{
					
						while(nrf_gpio_pin_read(key_2)== 0 );   
			 			return 	0	; 
					}
					else
					  return 1;					
			}
		else
			return 1;
}


#else

//======================KEY³õÊ¼»¯=====================//
void KEY_Init(void)
{
  nrf_gpio_cfg_input(BUTTON_1,NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON_2,NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(BUTTON_3,NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(BUTTON_4,NRF_GPIO_PIN_PULLUP);
}
//=====================KEYº¯Êý=========================//
uint8_t KEY1_Down()
{
	if( nrf_gpio_pin_read(BUTTON_1)== 0 )
	{
			nrf_delay_ms(200);
			if( nrf_gpio_pin_read(BUTTON_1)== 0 )
			{
				
				 while(nrf_gpio_pin_read(BUTTON_1)== 0 );   
						return 	0	; 						
				
			}
			else
				return 1;
	}
	else
		return 1;
}
uint8_t KEY2_Down()
{
		if( nrf_gpio_pin_read(BUTTON_2)== 0 )
			{
					nrf_delay_ms(200);
					if( nrf_gpio_pin_read(BUTTON_2)== 0 )
					{
					
						while(nrf_gpio_pin_read(BUTTON_2)== 0 );   
			 			return 	0	; 
					}
					else
					  return 1;					
			}
		else
			return 1;
}

uint8_t KEY3_Down()
{
		if( nrf_gpio_pin_read(BUTTON_3)== 0 )
			{
					nrf_delay_ms(200);
					if( nrf_gpio_pin_read(BUTTON_3)== 0 )
					{
					
						while(nrf_gpio_pin_read(BUTTON_3)== 0 );   
			 			return 	0	; 
					}
					else
					  return 1;					
			}
		else
			return 1;
}
uint8_t KEY4_Down()
{
		if( nrf_gpio_pin_read(BUTTON_4)== 0 )
			{
					nrf_delay_ms(200);
					if( nrf_gpio_pin_read(BUTTON_4)== 0 )
					{
					
						while(nrf_gpio_pin_read(BUTTON_4)== 0 );   
			 			return 	0	; 
					}
					else
					  return 1;					
			}
		else
			return 1;
}


#endif

