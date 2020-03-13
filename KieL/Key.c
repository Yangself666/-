#include <REGX52.H>
#include <Delay.h>
#include <Display.h>
#include <Data.h>
#include <EEPROM.h>
#include <Timer.h>

//KeyNum1，加1按钮生效
//KeyNum2，减1按钮生效
//KeyNum3，清0按钮生效
unsigned char KeyNum = 0;
unsigned int testTime;
unsigned char PressKey()
{
	unsigned int tempCOUNT = dataReader();
	testTime = 0;
	if (P2_1 == 0)
	{
		Delay(20);
		while (P2_1 == 0)
		{
			Display(tempCOUNT);
		}
		Delay(20);
		KeyNum = 1;
	}
	if (P2_2 == 0)
	{
		Delay(20);
		while (P2_2 == 0)
		{
			Display(tempCOUNT);
		}
		Delay(20);
		KeyNum = 2;
	}
	if (P2_3 == 0)
	{
		Delay(20);
		while (P2_3 == 0)
		{
			Display(tempCOUNT);
		}
		Delay(20);
		KeyNum = 3;
	}

	//商品
	if (P2_0 == 0)
	{
		Delay(20);
		while (P2_0 == 0)
		{
			DisplayRunning();
			testTime++;
			if(testTime > 7500)
			{
				KeyNum = 5;
				testTime = 0;
				return KeyNum;
			}
		}
		Delay(20);
		testTime = 0;
		KeyNum = 4;
	}

	return KeyNum;
}
