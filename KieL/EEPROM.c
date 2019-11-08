#include <REGX52.H>
#include <INTRINS.H>//为了引入_nop_方法

//SCK P2_5 ;
//SDA P2_6 ;

void EEPROMInit(){//初始化程序
	P2_5 = 1 ;
	_nop_();
	P2_6 = 1 ;
	_nop_();
}

void EEPROMStart(){//启动信号
	P2_6 = 1 ;
	_nop_();
	P2_5 = 1 ;
	_nop_();
	P2_6 = 0 ;
	_nop_();
}

void EEPROMStop(){//停止信号
	P2_6 = 0 ;
	_nop_();
	P2_5 = 1 ;
	_nop_();
	P2_6 = 1 ;
	_nop_();
}

void EEPROMRespons(){//回应信号
	unsigned char i = 0 ;
	P2_5 = 1 ;
	_nop_() ;
	while((P2_6 == 1) && (i < 255 )){
		i ++ ;//防止卡死
	}
	P2_5 = 0 ;
	_nop_() ;
}