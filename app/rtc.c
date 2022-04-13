#include "rtc.h"

int timer_flag=0;
const nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(0);

static void rtc_handler(nrf_drv_rtc_int_type_t int_type)
{
    if (int_type == NRF_DRV_RTC_INT_OVERFLOW)
    {
				timer_flag = 1;
				nrf_rtc_task_trigger(rtc.p_reg,NRF_RTC_TASK_TRIGGER_OVERFLOW);
				
    }
}

void lfclk_config(void)
{
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
    nrf_drv_clock_lfclk_request(NULL);
}

void rtc_config(void)
{
    uint32_t err_code;
    nrf_drv_rtc_config_t config = NRF_DRV_RTC_DEFAULT_CONFIG;
		//config.prescaler = 4095;// 8 Hz (125ms*16 = 2s)
		//config.prescaler = 2047;// 16 Hz (62.5ms*16 = 1s)
		//config.prescaler = 1023;// 32 Hz (31.25ms*16 = 0.5s)
		config.prescaler = (int)(1000.0 * 32.768 / 16.0 / RTC_Time_s) - 1;
    err_code = nrf_drv_rtc_init(&rtc, &config, rtc_handler);
    APP_ERROR_CHECK(err_code);

   	nrf_rtc_task_trigger(rtc.p_reg,NRF_RTC_TASK_TRIGGER_OVERFLOW);//触发溢出事件
    APP_ERROR_CHECK(err_code);
		
		nrf_drv_rtc_overflow_enable(&rtc,true);    
    nrf_drv_rtc_enable(&rtc);//启动RTC实例
}

void rtc_overflow_enable(void)
{
    nrf_drv_rtc_overflow_enable(&rtc,true);
		nrf_rtc_task_trigger(rtc.p_reg,NRF_RTC_TASK_TRIGGER_OVERFLOW);
}

void rtc_overflow_stop(void)
{
    nrf_drv_rtc_overflow_disable(&rtc);
}
