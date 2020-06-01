#ifndef __1602LCD_H
#define __1602LCD_H

#include "stm32f10x.h"

#define uint unsigned int
#define uchar unsigned char




void mDelay(uint Delay)  ;										//延迟函数
void LCD1602Write_data(uint i) ;   //写数据
void LCD1602Write_com(uint i) ;   //写命令
void LCD1602Init(void) ;                //初始化
void LCD_Write_Number(unsigned char x,unsigned char y,double num,uchar bit);
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s);
#endif
