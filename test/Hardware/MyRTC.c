#include "stm32f10x.h"
#include "time.h"
//第一步：rcc
//第二步:配置LSE,然后RTCCLK(选择LSE） 
//第三步 预分频
//第四步 分配32768
uint16_t MyRTC_Time[]={2015,10,29,13,01,59};
void MyRTC_SetTime(void);
void MyRTC_Init(void)
{
	if(BKP_ReadBackupRegister(BKP_DR1)!=0xFFFF){
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);		//开启PWR的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);	
	
	/*备份寄存器访问使能*/
	PWR_BackupAccessCmd(ENABLE);
	
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)!=SET);
	
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
	
	RTC_WaitForLastTask();
	RTC_WaitForSynchro();
	
	//分频
	RTC_SetPrescaler(32767);
	RTC_WaitForLastTask();
	
	// 每次初始化都设置时间
	MyRTC_SetTime();
	
	BKP_WriteBackupRegister(BKP_DR1,0xFFFF);}
	else
	{RTC_WaitForLastTask();
	RTC_WaitForSynchro();}
}
void MyRTC_SetTime(void)
{
	time_t time_cnt;		//定义秒计数器数据类型
	struct tm time_date;	//定义日期时间数据类型
	
	time_date.tm_year = MyRTC_Time[0] - 1900;		//将数组的时间赋值给日期时间结构体
	time_date.tm_mon = MyRTC_Time[1] - 1;
	time_date.tm_mday = MyRTC_Time[2];
	time_date.tm_hour = MyRTC_Time[3];
	time_date.tm_min = MyRTC_Time[4];
	time_date.tm_sec = MyRTC_Time[5];
	
	time_cnt = mktime(&time_date) - 8 * 60 * 60;	//调用mktime函数，将日期时间转换为秒计数器格式
													//- 8 * 60 * 60为东八区的时区调整
	
	RTC_SetCounter(time_cnt);						//将秒计数器写入到RTC的CNT中
	RTC_WaitForLastTask();							//等待上一次操作完成
}

void MyRTC_ReadTime(void)
{
	time_t time_cnt;		//定义秒计数器数据类型
	struct tm time_date;	//定义日期时间数据类型
	
	time_cnt = RTC_GetCounter() + 8 * 60 * 60;		//读取RTC的CNT，获取当前的秒计数器
													//+ 8 * 60 * 60为东八区的时区调整
	
	time_date = *localtime(&time_cnt);				//使用localtime函数，将秒计数器转换为日期时间格式
	
	MyRTC_Time[0] = time_date.tm_year + 1900;		//将日期时间结构体赋值给数组的时间
	MyRTC_Time[1] = time_date.tm_mon + 1;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[5] = time_date.tm_sec;
}
