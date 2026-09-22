#include <REGX52.H>
#include<INTRINS.H>

sbit BUZ = P2^5;

void BuzzerDelay(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 112;
	while (--i);
}

void Buzzer(unsigned int Time)
{
    unsigned int i;
    for (i = 0; i < 100; i++)
	{
		BUZ = !BUZ;
		BuzzerDelay();
	}
}