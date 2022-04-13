#ifndef _RTC_
#define _RTC_

#include "Board_Config.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"
#include "app_error.h"


#define COMPARE_COUNTERTIME  (3UL)  
#define LED_TOGGLE_INTERVAL         APP_TIMER_TICKS(100)   

void lfclk_config(void);

void rtc_config(void);

void rtc_overflow_enable(void);

void rtc_overflow_stop(void);

#endif
