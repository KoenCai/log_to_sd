#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

//FATFS设定
#define read_data_max  1024											//按键读取文件内容字节
#define FILE_CONFIG   "CONFIG.TXT"							//Config文件名
#define Default_CONFIG "Boud=921600,Log_0001"		//默认Config内容
#define File_suffix ".txt"											//文件后缀

//UARTE设定
#define RX_BUFF_SIZE    255	

//RTC设定
#define RTC_Time_s      1											  //数据存SD卡的时间间隔（秒）


#if 1

#define W02L  //使用W02L板子 
//LED定义pin
#define led_0 NRF_GPIO_PIN_MAP(1, 6)
#define led_4 NRF_GPIO_PIN_MAP(0, 20)
#define led_5	NRF_GPIO_PIN_MAP(1, 5)

//KEY定义pin
#define key_1 NRF_GPIO_PIN_MAP(1, 12)
#define key_2 NRF_GPIO_PIN_MAP(1, 13)

//SPI定义pin
#define SDC_SCK_PIN     NRF_GPIO_PIN_MAP(1,10) 
#define SDC_MOSI_PIN    NRF_GPIO_PIN_MAP(1,11) 
#define SDC_MISO_PIN    NRF_GPIO_PIN_MAP(1,14)  
#define SDC_CS_PIN      NRF_GPIO_PIN_MAP(1,04)  

//UARTE定义pin
#define UARTE_RXD 27  
#define UARTE_TXD 40 

#else

//SPI定义pin
#define SDC_SCK_PIN     NRF_GPIO_PIN_MAP(0, 20)  //< SDC serial clock (SCK) pin.
#define SDC_MOSI_PIN    NRF_GPIO_PIN_MAP(0, 21)  //< SDC serial data in (DI) pin.
#define SDC_MISO_PIN    NRF_GPIO_PIN_MAP(0, 19)  //< SDC serial data out (DO) pin.
#define SDC_CS_PIN      NRF_GPIO_PIN_MAP(0, 22)  //< SDC chip select (CS) pin.  

//UARTE定义pin
#define UARTE_RXD 8    
#define UARTE_TXD 6   

#endif	


#endif
