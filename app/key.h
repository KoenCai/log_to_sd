#ifndef _KEY_
#define _KEY_

#include <stdio.h>
#include "nrf.h"
#include "boards.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

void KEY_Init(void);

uint8_t KEY1_Down(void);

uint8_t KEY2_Down(void);

uint8_t KEY3_Down(void);

uint8_t KEY4_Down(void);

#endif
