#include "LCD1602.h"
#include "DS1302.h"

unsigned char TimeSet_Select;
unsigned char Tips_Table[6][6] = {"Year", "Month", "Date", "Hour", "Minute", "Second"};
unsigned char Tips_Column[6] = {13, 12, 13, 13, 11, 11};
unsigned char Maximum_Value[6] = {99, 12, 31, 23, 59, 59};

void timeset(unsigned char KeyNum, unsigned char Blink, char *Time)
{
    if (Blink)
    {
        LCD_ShowString(1 + TimeSet_Select / 3, 1 + (TimeSet_Select % 3) * 3, "  ");
    }
    else
    {
        LCD_ShowNum(1 + TimeSet_Select / 3, 1 + (TimeSet_Select % 3) * 3, Time[TimeSet_Select], 2);
    }

    switch (KeyNum)
    {
    case 2:
        LCD_ShowNum(1 + TimeSet_Select / 3, 1 + (TimeSet_Select % 3) * 3, Time[TimeSet_Select], 2);
        TimeSet_Select++;
        if (TimeSet_Select > 5)
        {
            TimeSet_Select = 0;
        }
        LCD_ShowString(2, 11, "      ");
        LCD_ShowString(2, Tips_Column[TimeSet_Select], Tips_Table[TimeSet_Select]);
        break;
    case 3:
        Time[TimeSet_Select]++;
        if (Time[TimeSet_Select] > Maximum_Value[TimeSet_Select])
        {
            if (TimeSet_Select == 1 || TimeSet_Select == 2)
            {
                Time[TimeSet_Select] = 1;
            }
            else
            {
                Time[TimeSet_Select] = 0;
            }
        }
        break;
    case 4:
        Time[TimeSet_Select]--;
        if (TimeSet_Select == 1 || TimeSet_Select == 2)
        {
            if (Time[TimeSet_Select] < 1)
            {
                Time[TimeSet_Select] = Maximum_Value[TimeSet_Select];
            }
        }
        else
        {
            if (Time[TimeSet_Select] < 0)
            {
                Time[TimeSet_Select] = Maximum_Value[TimeSet_Select];
            }
        }
        break;
    }

    if (TimeSet_Select == 0 || TimeSet_Select == 1)
    {
        if (Time[1] == 1 || Time[1] == 3 || Time[1] == 5 || Time[1] == 7 || Time[1] == 8 || Time[1] == 10 || Time[1] == 12)
        {
            Maximum_Value[2] = 31;
        }
        else
        {
            Maximum_Value[2] = 30;
        }

        if (Time[1] == 2)
        {
            int Full_Year = 2000 + Time[0];
            Maximum_Value[2] = 28;
            if ((Full_Year % 4 == 0 && Full_Year % 100 != 0) || Full_Year % 400 == 0)
            {
                Maximum_Value[2] = 29;
            }
        }

        if (Time[2] > Maximum_Value[2])
        {
            Time[2] = Maximum_Value[2];
            LCD_ShowNum(1, 7, Time[2], 2);
        }
    }
}

void timeshow(char *Time)
{
    unsigned char i, Temp[6];
    DS1302_ReadTime(Temp);
    if (Temp[5] != Time[5])
    {
        for (i = 0; i < 6; i++)
        {
            Time[i] = Temp[i];
            LCD_ShowNum(1 + i / 3, 5 + (i % 3) * 3, Time[i], 2);
        }
    }
}

void Select_Clean()
{
    TimeSet_Select = 0;
}