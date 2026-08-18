#ifndef __DS1302_H__
#define __DS1302_H__

void DS1302_Init();
void DS1302_SetTime(unsigned char *Time);
void DS1302_ReadTime(unsigned char *Time);
void DS1302_Stop();

#endif