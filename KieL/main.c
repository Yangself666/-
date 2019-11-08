#include <REGX52.H>
#include <INTRINS.H>
#include <Delay.h>
#include <Display.h>
#include <Product.h>
#include <Key.h>
#include <EEPROM.h>
//��������COUNT
unsigned int COUNT = 0;
unsigned int WAIT ;
void main(){
	//һֱ��ʾ���֣�ʹ���жϼӼ�
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
		while(isProduct == 5){//ͣ����ʱ������������
			P2_4 = 1 ;//���������й���
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
			P2_4 = 1 ;//��������
			WAIT = 1 ;//���λ
			while(WAIT){//��ѭ���޷�չʾ������Ϣ��ʹ�ñ�ǺͶ�ʱ�����п���ѭ����ֹͣ
				Timer0() ;//����5�붨ʱ����
				DisplayErr2() ;//չʾE002
			}
			P2_4 = 0 ;//������ֹͣ
			COUNT = 0 ;//��������0
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