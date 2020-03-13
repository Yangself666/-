#include <REGX52.H>
#include <stdio.h>
#include <INTRINS.H>
#include <Delay.h>
#include <Display.h>
#include <Key.h>
#include <EEPROM.h>
#include <Data.h>
#include <Timer.h>
#include <Uart.h>

#define uchar unsigned char
#define uint unsigned int 
	
void uart_cfg();
void send_byte(uchar by);
void send_string(uchar *p);
void toString(unsigned int temp);

//计数常量COUNT
unsigned int COUNT;
unsigned int WAIT;
unsigned int flag ;
unsigned char name[] = "Device001";
unsigned char buffer[4];
void main()
{
	uart_cfg(); //波特率4800,初始化
	//一直显示数字，使用中断加减
	P2_4 = 0;
	//开机先从eeprom中读取数据
	COUNT = dataReader();
	
	Delay(1000);//等待一秒连接wifi
	//开机即发送请求
	send_string("AT+CIPSTART=\"TCP\",\"yangself.cn\",549\r\n");
	Delay(50);
	send_string("AT+CIPMODE=1\r\n");
	Delay(50);
	send_string("AT+CIPSEND\r\n");
	Delay(50);
	send_string("GET /counter/addData?cName=");
	send_string(name);
	send_string("&num=");
	//这里要把数字转换成字符串
	toString(COUNT);
	send_string(buffer);
	send_string(" HTTP/1.1\r\n");
	Delay(50);
	send_string("Host: yangself.cn\r\n\r\n");
	Delay(50);
	send_string("+++");

	while (1)
	{
		COUNT = dataReader();
		KeyNum = PressKey();
		Display(COUNT);
		if(flag > 500){//25秒一次从串口发送数据
			send_string("AT+CIPSTART=\"TCP\",\"yangself.cn\",549\r\n");
			Delay(50);
			send_string("AT+CIPMODE=1\r\n");
			Delay(50);
			send_string("AT+CIPSEND\r\n");
			Delay(50);
			send_string("GET /counter/addData?cName=");
			send_string(name);
			send_string("&num=");
			//这里要把数字转换成字符串
			toString(COUNT);
			send_string(buffer);
			send_string(" HTTP/1.1\r\n");
			Delay(50);
			send_string("Host: yangself.cn\r\n\r\n");
			Delay(50);
			send_string("+++");
			flag = 0;
		}
		flag++;
		if (KeyNum == 4)
		{
			COUNT = dataReader();
			COUNT++;
			dataWrite(COUNT);
			KeyNum = 0;
		}
		
		
		COUNT = dataReader();
		Display(COUNT);
		while (KeyNum == 5)
		{			  //停留长时间后进入错误界面
			P2_4 = 1; //蜂鸣器进行工作
			DisplayErr1();
		}
		
		COUNT = dataReader();
		Display(COUNT);
		if (KeyNum == 1)
		{
			COUNT = dataReader();
			COUNT++;
			dataWrite(COUNT);
			KeyNum = 0;
		}
		COUNT = dataReader();
		Display(COUNT);
		if (KeyNum == 2)
		{
			COUNT = dataReader();
			COUNT--;
			dataWrite(COUNT);
			KeyNum = 0;
		}
		COUNT = dataReader();
		Display(COUNT);
		if (KeyNum == 3)
		{
			COUNT = 0;
			dataWrite(COUNT);
			KeyNum = 0;
		}
		COUNT = dataReader();
		Display(COUNT);
		if (dataReader() > 9999)
		{
			P2_4 = 1; //蜂鸣器响
			WAIT = 1; //标记位
			while (WAIT)
			{				   //不循环无法展示错误信息，使用标记和定时器进行控制循环的停止
				Timer0();	  //进行5秒定时任务
				DisplayErr2(); //展示E002
			}
			P2_4 = 0;  //蜂鸣器停止
			COUNT = 0; //计数器置0
			dataWrite(COUNT);
		}
		COUNT = dataReader();
		Display(COUNT);
	}
}
void Timer0_run() interrupt 1
{
	static unsigned int T0Count = 0;
	TL0 = 0x18;
	TH0 = 0xFC;
	T0Count++;
	if (T0Count >= 5000)
	{
		T0Count = 0;
		//todo
		WAIT = 0;
	}
}


void uart_cfg(){
 
       SCON = 0X50;//MODE 1
      TMOD&= 0X0F;//清除T1的控制位
      TMOD|= 0X20;//T1的工作模式2
      PCON|= 0X80;//倍频

      TH1 = 0xf3; //4800
      TL1 = TH1;

      ET1 = 0;//禁止T1中断 
//      EA = 1; 
      TR1 = 1;      
//      ES = 1;//使能串口中断 ,无论是TI/RI出现，只要中断打开，单片机就进入中断函数。
 }

 void send_byte(uchar by){

    SBUF = by;
    while(!TI);//当写下这句的时候，就不要在中断函数里面在写TI = 0;这句了，不然进入中断函数将TI清零之后，程序就会一直卡在这里
    TI = 0;       //在这里将TI清零
}
/*发送一个字符串*/
void send_string(uchar *p){

    while(*p!= '\0'){
    
        send_byte(*p);
        p++;

    }
}

void toString(unsigned int temp){
	sprintf(buffer, "%d", temp);
}

