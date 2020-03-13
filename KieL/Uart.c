#include "reg52.h"
#include "stdio.h"



uchar str[] = "yes,you are good!";

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


 
/*发送一个 字符*/
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