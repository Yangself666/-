#include <REGX52.H>



//����1ms�Ķ�ʱ��Timer0
void Timer0(void)
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TL0 = 0x18;
	TH0 = 0xFC;
	TF0 = 0;
	TR0 = 1;
	ET0 = 1;
	EA	= 1;
	PT0 = 0;
}
//��ʱ��0ʹ��ģ��
//void Timer0_run() interrupt 1{
//	static unsigned int T0Count = 0;
//	TL0 = 0x18;
//	TH0 = 0xFC;
//	T0Count ++ ;
//	if(T0Count >= 1000){
//		T0Count = 0;
//		//toDo
//	}
//}

//����1ms�Ķ�ʱ��Timer1
//void Timer1(void)
//{
//	TMOD &= 0x0F;
//	TMOD |= 0x10;
//	TL0 = 0x18;
//	TH0 = 0xFC;
//	TF1 = 0;
//	TR1 = 1;
//	ET1 = 1;
//	EA	= 1;
//	PT1 = 0;
//}



//��ʱ��1ʹ��ģ��
//void Timer1_run() interrupt 3{
//	static unsigned int T0Count = 0;
//	TL0 = 0x18;
//	TH0 = 0xFC;
//	T0Count ++ ;
//	if(T0Count >= 1000){
//		T0Count = 0;
//		//toDo
//	}
//}