#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Timer0.h"
#include "Clock.h"
#include "Key.h"

#define TIMESHOW 0
#define TIMESET 1

unsigned char i, KeyNum, Blink;
char Time[6] = {07, 07, 13, 0, 0, 0};

void main()
{
    unsigned char MODE = TIMESHOW;

    DS1302_Init();
    LCD_Init();
    Timer0_Init();
    DS1302_SetTime(Time);

    LCD_ShowString(1, 5, "  -  -  ");
    LCD_ShowString(2, 5, "  :  :  ");

    for (i = 0; i < 6; i++)
    {
        LCD_ShowNum(1 + i / 3, 5 + (i % 3) * 3, Time[i], 2);
    }

    while (1)
    {
        KeyNum = Key();

        if (KeyNum == 1)
        {
            if (MODE == TIMESHOW)
            {
                MODE = TIMESET;
                Select_Clean();
                DS1302_Stop();
                Timer0_Start();

                LCD_ShowString(1, 1, "  -  -          ");
                LCD_ShowString(2, 1, "  :  :          ");

                for (i = 0; i < 6; i++)
                {
                    LCD_ShowNum(1 + i / 3, 1 + (i % 3) * 3, Time[i], 2);
                }

                LCD_ShowString(1, 10, "TimeSet");
                LCD_ShowString(2, 13, "Year");
            }
            else
            {
                MODE = TIMESHOW;
                DS1302_SetTime(Time);
                Timer0_Stop();

                LCD_ShowString(1, 1, "      -  -      ");
                LCD_ShowString(2, 1, "      :  :      ");

                for (i = 0; i < 6; i++)
                {
                    LCD_ShowNum(1 + i / 3, 5 + (i % 3) * 3, Time[i], 2);
                }
            }
        }

        if (MODE == TIMESHOW)
        {
            timeshow(Time);
        }
        else
        {
            timeset(KeyNum, Blink, Time);
        }
    }
}

void Timer0_Rountine(void) interrupt 1
{
    static unsigned int T0Count = 0;
    TL0 = 0x66;
    TH0 = 0xFC;
    T0Count++;
    if (T0Count >= 500)
    {
        T0Count = 0;
        if (Blink)
        {
            Blink = 0;
        }
        else
        {
            Blink = 1;
        }
    }
}