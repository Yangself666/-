#include <REGX52.H>
#include <Delay.h>

//KeyNum1，加1按钮生效
//KeyNum2，减1按钮生效
//KeyNum3，清0按钮生效
unsigned char KeyNum = 0 ;
unsigned char PressKey(){
	if(P2_1 == 0){
		Delay(20) ;
		while(P2_1 == 0) ;
		Delay(20) ;
		KeyNum = 1 ;
	}
	if(P2_2 == 0){
		Delay(20) ;
		while(P2_2 == 0) ;
		Delay(20) ;
		KeyNum = 2 ;
	}
	if(P2_3	== 0){
		Delay(20) ;
		while(P2_3 == 0) ;
		Delay(20) ;
		KeyNum = 3 ;
	}
	return KeyNum ;
}