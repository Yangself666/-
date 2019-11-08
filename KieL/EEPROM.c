#include <REGX52.H>
#include <INTRINS.H>//Ϊ������_nop_����

//SCK P2_5 ;
//SDA P2_6 ;

void EEPROMInit(){//��ʼ������
	P2_5 = 1 ;
	_nop_();
	P2_6 = 1 ;
	_nop_();
}

void EEPROMStart(){//�����ź�
	P2_6 = 1 ;
	_nop_();
	P2_5 = 1 ;
	_nop_();
	P2_6 = 0 ;
	_nop_();
}

void EEPROMStop(){//ֹͣ�ź�
	P2_6 = 0 ;
	_nop_();
	P2_5 = 1 ;
	_nop_();
	P2_6 = 1 ;
	_nop_();
}

void EEPROMRespons(){//��Ӧ�ź�
	unsigned char i = 0 ;
	P2_5 = 1 ;
	_nop_() ;
	while((P2_6 == 1) && (i < 255 )){
		i ++ ;//��ֹ����
	}
	P2_5 = 0 ;
	_nop_() ;
}