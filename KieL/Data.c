#include <EEPROM.h>
#include <Delay.h>

unsigned int dataReader()
{
	char front = rom_read(0x00);
	char end = rom_read(0x01);
	unsigned int temp = front + end * 128;
	return temp;
}

void dataWrite(unsigned int temp)
{
//	if (temp <= 255)
//	{
//		rom_write(0x00, 0x00);
//		rom_write(0x01, temp);
//	}
//	else
//	{
//		//16进制的前两位
//		unsigned int front = temp / 256;
//		unsigned int end = temp % 256;
//		rom_write(0x00, front);
//		rom_write(0x01, end);
//	}
	char front = temp%128;
	char end = temp/128;
	rom_write(0x00, front);
	rom_write(0x01, end);
	
}