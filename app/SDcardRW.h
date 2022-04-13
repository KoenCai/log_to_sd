#ifndef _SDCARDRW_
#define _SDCARDRW_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board_Config.h"
#include "led.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "ff.h"
#include "diskio_blkdev.h"
#include "nrf_block_dev_sdc.h"


void fatfs_init(void);
void create_config(void);
int32_t fatfs_readconfig(void);
void logName_plus(void);
char* create_newfile(void);
void printf_data( char* FILE);
void WirteToSD(char* Wirte_file);
void cheakBUFFdata(void);

#endif
