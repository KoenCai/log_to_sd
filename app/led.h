#ifndef _LED_
#define _LED_

#include <stdio.h>
#include "nrf.h"
#include "boards.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

void LED_Init(void);
void LED1_Open(void);
void LED1_Close(void);
void LED1_Toggle(void);
void LED1_blink(uint16_t delay);
void LED2_Open(void);
void LED2_Close(void);
void LED2_Toggle(void);
void LED3_Open(void);
void LED3_Close(void);
void LED3_Toggle(void);
void LED4_Open(void);
void LED4_Close(void);
void LED4_Toggle(void);
void LED5_Close(void);
void LED5_Open(void);




#endif
