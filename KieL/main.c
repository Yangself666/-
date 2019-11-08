#include <REGX52.H>
#include <INTRINS.H>
#include <Delay.h>
#include <Display.h>
#include <Product.h>
#include <Key.h>
#include <EEPROM.h>
//计数常量COUNT
unsigned int COUNT = 0;
unsigned int WAIT ;
void main(){
	//一直显示数字，使用中断加减
	P2_4 = 0 ;
	EEPROMInit();
	while(1){
		EEPROMStart();
		Display(COUNT);
		KeyNum = PressKey();
		Product();
		
		if(isProduct == 1){
			COUNT ++;
			isProduct = 0 ;
		}
		while(isProduct == 5){//停留长时间后进入错误界面
			P2_4 = 1 ;//蜂鸣器进行工作
			DisplayErr1();
		}
		
		if(KeyNum == 1){
			COUNT ++ ;
			KeyNum = 0 ;
		}
		if(KeyNum == 2){
			COUNT -- ;
			KeyNum = 0 ;
		}
		if(KeyNum == 3){
			COUNT = 0 ;
			KeyNum = 0 ;
		}
		
		if(COUNT > 9999){
			P2_4 = 1 ;//蜂鸣器响
			WAIT = 1 ;//标记位
			while(WAIT){//不循环无法展示错误信息，使用标记和定时器进行控制循环的停止
				Timer0() ;//进行5秒定时任务
				DisplayErr2() ;//展示E002
			}
			P2_4 = 0 ;//蜂鸣器停止
			COUNT = 0 ;//计数器置0
		}
	}
}
void Timer0_run() interrupt 1{
	static unsigned int T0Count = 0;
	TL0 = 0x18;
	TH0 = 0xFC;
	T0Count ++ ;
	if(T0Count >= 5000){
		T0Count = 0;
		//todo
		WAIT = 0 ;
	}
}