#include <REGX52.H>

#define DS1302_SECOND 0X80
#define DS1302_MINUTE 0X82
#define DS1302_HOUR 0X84
#define DS1302_DATE 0X86
#define DS1302_MONTH 0X88
#define DS1302_YEAR 0X8C
#define DS1302_WP 0X8E

sbit DS1302_SCLK = P3 ^ 6;
sbit DS1302_IO = P3 ^ 4;
sbit DS1302_CE = P3 ^ 5;

void DS1302_WriteByte(unsigned char Command, Data)
{
    unsigned char i;

    DS1302_CE = 1;

    for (i = 0; i < 8; i++)
    {
        DS1302_IO = Command & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }

    Data = (Data / 10) * 16 + Data % 10;
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = Data & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }

    DS1302_CE = 0;
}

unsigned char DS1302_ReadByte(unsigned char Command)
{
    unsigned char i, Data = 0x00;

    DS1302_CE = 1;

    Command++;
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = Command & (0x01 << i);
        DS1302_SCLK = 0;
        DS1302_SCLK = 1;
    }

    DS1302_IO = 1;
    for (i = 0; i < 8; i++)
    {
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
        if (DS1302_IO)
        {
            Data |= (0x01 << i);
        }
    }
    DS1302_IO = 0;

    DS1302_CE = 0;

    return (Data / 16) * 10 + Data % 16;
}

void DS1302_Init()
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}

void DS1302_Stop()
{
    DS1302_WriteByte(DS1302_WP, 0x00);
    DS1302_WriteByte(DS1302_SECOND, 0x80);
}

void DS1302_SetTime(unsigned char *Time)
{
    DS1302_WriteByte(DS1302_WP, 0x00);
    DS1302_WriteByte(DS1302_YEAR, Time[0]);
    DS1302_WriteByte(DS1302_MONTH, Time[1]);
    DS1302_WriteByte(DS1302_DATE, Time[2]);
    DS1302_WriteByte(DS1302_HOUR, Time[3]);
    DS1302_WriteByte(DS1302_MINUTE, Time[4]);
    DS1302_WriteByte(DS1302_SECOND, Time[5]);
}

void DS1302_ReadTime(unsigned char *Time)
{
    Time[0]=DS1302_ReadByte(DS1302_YEAR);
    Time[1]=DS1302_ReadByte(DS1302_MONTH);
    Time[2]=DS1302_ReadByte(DS1302_DATE);
    Time[3]=DS1302_ReadByte(DS1302_HOUR);
    Time[4]=DS1302_ReadByte(DS1302_MINUTE);
    Time[5]=DS1302_ReadByte(DS1302_SECOND);
}