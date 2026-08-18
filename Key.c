#include <REGX52.H>
#include "Delay.h"

unsigned char Key()
{
	unsigned char KeyNum = 0;
	if((P3 & 0x0F) != 0x0F)
	{
		Delay(20);
		if((P3 & 0x0F) != 0x0F)
		{
			switch(P3 & 0x0F)
			{
				case 0x0D: KeyNum = 1;break;
				case 0x0E: KeyNum = 2;break;
				case 0x0B: KeyNum = 3;break;
				case 0x07: KeyNum = 4;break;
			}
		}
		while((P3 & 0x0F) != 0x0F);
		Delay(20);
		return KeyNum;
	}	
	return 0;
	
//	if(!P3_1)
//	{
//		Delay(20);
//		while(!P3_1);
//		Delay(20);
//		KeyNum = 1;
//	}
//	if(!P3_0)
//	{
//		Delay(20);
//		while(!P3_0);
//		Delay(20);
//		KeyNum = 2;
//	}
//	if(!P3_2)
//	{
//		Delay(20);
//		while(!P3_2);
//		Delay(20);
//		KeyNum = 3;
//	}
//	if(!P3_3)
//	{
//		Delay(20);
//		while(!P3_3);
//		Delay(20);
//		KeyNum = 4;
//	}
}
