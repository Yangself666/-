#include <REGX52.H>
#include <Delay.h>
//Ϊ�˳���ʹ�÷��㣬��������õ����ַ����ж���
//��P0�ڽ���ʹ��
#define NUMNULL 0xFF ;
#define NUM0 0xC0 ;
#define NUM1 0xF9 ;
#define NUM2 0xA4 ;
#define NUM3 0xB0 ;
#define NUM4 0x99 ;
#define NUM5 0x92 ;
#define NUM6 0x82 ;
#define NUM7 0xF8 ;
#define NUM8 0x80 ;
#define NUM9 0x90 ;
#define NUME 0x86 ;
//�ٽ�����ܵĿ��ƴ��ڽ��ж��壬������п���
//��P1�ڽ���ʹ��
#define W0 0x1 ;
#define W1 0x2 ;
#define W2 0x4 ;
#define W3 0x8 ;


//��������ʾ�ŵ������з���ʹ��,P0
unsigned char num[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
//P1
unsigned char win[] = {0x1,0x2,0x4,0x8};


//��10���Ƶ�����ת�����������ʾ�ķ���
void Display(unsigned int number){
	//ǧλ
	int temp = number / 1000 ;
	P1 = win[3] ;
	P0 = num[temp];
	Delay(1);
	//��λ
	number = number % 1000 ;
	temp = number / 100 ;
	P1 = win[2] ;
	P0 = num[temp];
	Delay(1);
	//ʮλ
	number = number % 100 ;
	temp = number / 10 ;
	P1 = win[1] ;
	P0 = num[temp];
	Delay(1);
	//��λ
	temp = number % 10 ;
	P1 = win[0] ;
	P0 = num[temp];
	Delay(1);
}
void DisplayErr1(){
	P1 = win[3] ;
	P0 = NUME;
	Delay(1);
	P1 = win[2] ;
	P0 = NUM0;
	Delay(1);
	P1 = win[1] ;
	P0 = NUM0;
	Delay(1);
	P1 = win[0] ;
	P0 = NUM1;
	Delay(1);
}
void DisplayErr2(){
	P1 = win[3] ;
	P0 = NUME;
	Delay(1);
	P1 = win[2] ;
	P0 = NUM0;
	Delay(1);
	P1 = win[1] ;
	P0 = NUM0;
	Delay(1);
	P1 = win[0] ;
	P0 = NUM2;
	Delay(1);
}