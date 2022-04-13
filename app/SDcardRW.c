#include "SDcardRW.h"

char readFatfsBuf[50];
char logName[8] = "LOG_";
char Config_txt[21]={0};

FATFS FatFs;
FRESULT fr;
FIL fil;

int32_t readBoud = 0;
bool openflag =0;

extern uint32_t cnt_t;
extern uint8_t print_buff[];

NRF_BLOCK_DEV_SDC_DEFINE(
	m_block_dev_sdc,
	NRF_BLOCK_DEV_SDC_CONFIG(
					SDC_SECTOR_SIZE,
					APP_SDCARD_CONFIG(SDC_MOSI_PIN, SDC_MISO_PIN, SDC_SCK_PIN, SDC_CS_PIN)
	 ),
	 NFR_BLOCK_DEV_INFO_CONFIG("Nordic", "SDC", "1.00")
);

//============文件管理系统初始化===============//
void fatfs_init()
{	
	DSTATUS disk_state = STA_NOINIT;
	// Initialize FATFS disk I/O interface by providing the block device.
	static diskio_blkdev_t drives[] =
	{
					DISKIO_BLOCKDEV_CONFIG(NRF_BLOCKDEV_BASE_ADDR(m_block_dev_sdc, block_dev), NULL)
	};
	diskio_blockdev_register(drives, ARRAY_SIZE(drives));
	NRF_LOG_INFO("Initializing disk 0 (SDC)...");
	NRF_LOG_FLUSH();
	do
	{
		disk_state = disk_initialize(0);
		NRF_LOG_INFO("waiting SDcard init...");
		NRF_LOG_FLUSH();
		LED1_blink(200);
		
	}while(disk_state);
	LED1_Open();
	uint32_t blocks_per_mb = (1024uL * 1024uL) / m_block_dev_sdc.block_dev.p_ops->geometry(&m_block_dev_sdc.block_dev)->blk_size;
	uint32_t capacity = m_block_dev_sdc.block_dev.p_ops->geometry(&m_block_dev_sdc.block_dev)->blk_count / blocks_per_mb;
	NRF_LOG_INFO("Capacity: %d MB", capacity);
	NRF_LOG_FLUSH();
}

//===============CONFIG文件 新创建或读取==================//
int32_t fatfs_readconfig(void)
{
	UINT bw;
	UINT br;
	f_mount(&FatFs, "", 0);
	fr = f_open(&fil, FILE_CONFIG, FA_CREATE_NEW);
	//如无则直接创建新config文件
	if(fr == 0)
	{
		f_open(&fil, FILE_CONFIG,FA_WRITE);
		f_write(&fil, Default_CONFIG, sizeof(Default_CONFIG) - 1, &bw);
		f_close(&fil);
		NRF_LOG_INFO("Default_CONFIG = %s",Default_CONFIG);
		NRF_LOG_FLUSH();
	}
	fr = f_open(&fil, FILE_CONFIG, FA_READ);
	f_read(&fil,readFatfsBuf,sizeof readFatfsBuf,&br);
	f_close(&fil);

	for(int n=0;n>=0;n++)
		{
			Config_txt[n] = readFatfsBuf[n];
			if(readFatfsBuf[n] ==',')	//判断标识位逗号‘，’
				{
					for(int m=5;m<n;m++)
							readBoud = readBoud*10+(readFatfsBuf[m]-48);	//提取boud值																			
					NRF_LOG_INFO("readBoud=%d",readBoud);
					for(int m=n+5,j=4;m>0;m++,j++)
					{
						if(readFatfsBuf[m]=='\0' ||readFatfsBuf[m]==27||readFatfsBuf[m]>48+9)break;  //ASCII 27 -> ESC (Escape)		
						logName[j] = readFatfsBuf[m];								
					}				
					NRF_LOG_INFO("NextPack=%s",logName);
					NRF_LOG_FLUSH();
					break;					
				}
								
		}
		return readBoud;//返回获取波特率
}

//=============================Config文件 logName+1===========================//
void logName_plus()
{
	UINT bw;
	static char str[21];
	strcpy(str, Config_txt);
	logName[7]=logName[7]+1;
	if(logName[7]==(10+48)){logName[7]=48+0;
													logName[6]=logName[6]+1;}									
	if(logName[6]==(10+48)){logName[6]=48+0;
													logName[5]=logName[5]+1;}
	if(logName[5]==(10+48)){logName[5]=48+0;
													logName[4]=logName[4]+1;}
	if(logName[4]==(10+48)){logName[4]=48+0;
													logName[5]=48+0;
													logName[6]=48+0;
													logName[7]=48+0;}//当文件名超过9999，置0	
	f_unlink(FILE_CONFIG);
	fr = f_open(&fil, FILE_CONFIG, FA_CREATE_NEW);												
	f_open(&fil, FILE_CONFIG,FA_WRITE);
	strcat(str,logName);														
	f_write(&fil,str,sizeof(str) - 1, &bw);
	f_close(&fil);

}

//==========================读文件data====================//
void printf_data( char* FILE)
{
		UINT br;
		static char readtxtBuf[read_data_max];
		fr = f_open(&fil, FILE, FA_READ);
		if(fr == 0)
		{
			f_read(&fil,readtxtBuf,sizeof readtxtBuf,&br);
			f_close(&fil);
			NRF_LOG_INFO("%s\r%s",FILE,readtxtBuf);			
		}
		else
			NRF_LOG_INFO("read data failed ",readtxtBuf );
		
		NRF_LOG_FLUSH();
		memset(readtxtBuf,0,sizeof(readtxtBuf));
		
}
//===========================创建新文件==============================//
char* create_newfile(void)
{
	static char Wirte_file[13] ;
	strcpy(Wirte_file,logName);	
	fr = f_open(&fil, strcat(Wirte_file,File_suffix), FA_CREATE_NEW);
		if(fr == 0)
			 //f_close(&fil);	
			 ;		
		else
			NRF_LOG_INFO("Create file already existed, error code = %d",fr);
			NRF_LOG_FLUSH();
		logName_plus();
		return Wirte_file;
					
}

//===========================SD卡写入数据==============================//
void WirteToSD(char* Wirte_file)
{
	UINT bw;
	if(openflag == 0)	
	{
		fr = f_open(&fil, Wirte_file, FA_WRITE);
		openflag = 1;
	}
	if(fr == 0)
	{
		f_lseek(&fil,f_size(&fil));
		f_write(&fil, print_buff, cnt_t, &bw);
		f_sync(&fil);
	}
	else
		NRF_LOG_INFO("WirteToSD error code fr = %d",fr);
		NRF_LOG_FLUSH();

}


//======================测试接收的printf_buff,替换掉WirteToSD()================================//
/*
0123456789

*/
//char framebuff[12]={'0','1','2','3','4','5','6','7','8','9','\x0d','\x0a'};
void cheakBUFFdata(void)
{		
		char cpybuff[12]={0};
		for(int16_t i=0;i<=cnt_t;i++)
		{
			if(cnt_t - i < 12)
				return;
			strncpy(cpybuff,print_buff+i,12);
			for(int16_t n=0;n<=9;n++)
			{
				if(cpybuff[n] == 9+48) //这帧头是9
				{
					i=i+n+2;
					break;
				}
				else if(cpybuff[n] == '\x0d') //这帧头是'\x0d'
				{
					i=i+n+1;
					break;
				}
				else if(cpybuff[n] == '\x0a' ||cpybuff[n] == '\0') //这帧头是'\x0a'或者结束符
				{
					i=i+n;
					break;
				}
				else if(cpybuff[n] + 1 != cpybuff[n+1] )//判断与下一个字符是否连续
				{					
					i+=11;
					NRF_LOG_INFO("wrong = %s",cpybuff);
			    NRF_LOG_FLUSH();
					break;
				}
			}

		}

}

