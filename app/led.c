#include "led.h"
#include "Board_Config.h"

#ifdef W02L

	
void LED_Init(void)
{
	nrf_gpio_cfg_output(led_0);
	nrf_gpio_cfg_output(led_4);
	nrf_gpio_cfg_output(led_5);
	LED1_Close();
	LED4_Close();
	LED5_Close();
}
void LED1_Open(void)
{
	nrf_gpio_pin_clear(led_0);
}

void LED1_Close(void)
{
  nrf_gpio_pin_set(led_0);
}
void LED1_Toggle(void)
{
  nrf_gpio_pin_toggle(led_0);
}	

void LED1_blink(uint16_t delay)
{
	nrf_gpio_pin_toggle(led_0);
	nrf_delay_ms(delay/2);
	nrf_gpio_pin_toggle(led_0);
	nrf_delay_ms(delay/2);
}	
void LED4_Open(void)
{
	nrf_gpio_pin_clear(led_4);
}

void LED4_Close(void)
{
  nrf_gpio_pin_set(led_4);
}
void LED4_Toggle(void)
{
	nrf_gpio_pin_toggle(led_4);
}	

void LED2_Toggle(void) //临时
{
	nrf_gpio_pin_toggle(led_4);
}	
void LED5_Close(void)
{
	nrf_gpio_pin_set(led_5);
}
void LED5_Open(void)
{
	nrf_gpio_pin_clear(led_5);
}	
#else
//===============LED初始化==================//
void LED_Init(void)
{
	// Configure LED-pins as outputs
	nrf_gpio_cfg_output(BSP_LED_0);
	nrf_gpio_cfg_output(BSP_LED_1);
	nrf_gpio_cfg_output(BSP_LED_2);
	nrf_gpio_cfg_output(BSP_LED_3);
	
	nrf_gpio_cfg_output(RTS_PIN_NUMBER);
	nrf_gpio_cfg_output(CTS_PIN_NUMBER);
	
	LED1_Close();
	LED2_Close();
	LED3_Close();
	LED4_Close();
}
//================LED函数===================//
void LED1_Open(void)
{
	nrf_gpio_pin_clear(BSP_LED_0);
}

void LED1_Close(void)
{
	nrf_gpio_pin_set(BSP_LED_0);
	
}
void LED1_Toggle(void)
{
  nrf_gpio_pin_toggle(BSP_LED_0);
	
}
void LED1_blink(uint16_t delay)
{
	nrf_gpio_pin_toggle(BSP_LED_0);
	nrf_delay_ms(delay/2);
	nrf_gpio_pin_toggle(BSP_LED_0);
	nrf_delay_ms(delay/2);
}	
void LED2_Open(void)
{
	nrf_gpio_pin_clear(BSP_LED_1);
	}

void LED2_Close(void)
{
	nrf_gpio_pin_set(BSP_LED_1);
	
}
void LED2_Toggle(void)
{
  nrf_gpio_pin_toggle(BSP_LED_1);
}
void LED3_Open(void)
{
	nrf_gpio_pin_clear(BSP_LED_2);
}

void LED3_Close(void)
{
	nrf_gpio_pin_set(BSP_LED_2);
	
}
void LED3_Toggle(void)
{
  nrf_gpio_pin_toggle(BSP_LED_2);
}
void LED4_Open(void)
{
	nrf_gpio_pin_clear(BSP_LED_3);
}

void LED4_Close(void)
{
  nrf_gpio_pin_set(BSP_LED_3);
}
void LED4_Toggle(void)
{
  nrf_gpio_pin_toggle(BSP_LED_3);
}


#endif


