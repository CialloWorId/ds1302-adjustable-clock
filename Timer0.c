#include <REGX52.H>

void Timer0_Init()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TF0 = 0;
	TL0 = 0x66;
	TH0 = 0xFC;
	ET0 = 1;
	EA = 1;
}

void Timer0_Start()
{
	TR0 = 1;
}

void Timer0_Stop()
{
	TR0 = 0;
}

/*
void Timer0_Rountine(void) interrupt 1
{
	static unsigned int T0Count = 0;
	TL0 = 0x66;
	TH0 = 0xFC;
	T0Count++;
	if(T0Count >= 1000)
	{
		T0Count = 0;
	}
}
*/