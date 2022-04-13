#ifndef _UARTE_H_
#define _UARTE_H_

#include "ring_buffer.h"
#include "Board_Config.h"
#include "led.h"


void uartE_DMA_Init(int32_t baud);
void ringbuffer_creat(void);
void readbuff(void);
void reset_cnt_t(void);

#endif
