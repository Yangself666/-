#include <REGX52.H>
#include <Delay.h>
#include <Display.h>

unsigned char MODE = 0;
unsigned int delayCount = 0;
unsigned int isProduct = 0; //1是正常计数，5是物品卡住
void Product()
{
	switch (MODE)
	{
	case 0:
	{
		if (P2_0 == 0)
		{
			MODE = 1;
		}
	}
	break;

	case 1:
	{
		delayCount++;
		if (delayCount > 50)
		{
			delayCount = 0;
			if (P2_0 == 1)
			{
				MODE = 0;
			}
			else
			{
				MODE = 2;
			}
		}
	}
	break;

	case 2:
	{
		delayCount++;
		Delay(500); //停留多少秒
		if (P2_0 == 1)
		{
			isProduct = 1;
			MODE = 0;
		}
		else
		{
			MODE = 3;
		}
	}
	break;
	case 3:
	{
		delayCount++;
		if (delayCount > 5000)
		{
			delayCount = 0;
			if (P2_0 == 0)
			{
				isProduct = 5; //xiang
			}
		}
	}
	break;
	}
}
