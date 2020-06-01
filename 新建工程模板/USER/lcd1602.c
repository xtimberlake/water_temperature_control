#include "lcd1602.h"
#include  "sys.h"
#include "delay.h"
#include "math.h"
#define uint unsigned int
#define uchar unsigned char
#define RS  PBout(0)  //��� 
#define E   PBout(1)  


const char table[10] = {'0','1','2','3','4','5','6','7','8','9'};



void LCD1602Write_data(uint i)        //д����
{

        RS = 1;//����
        

			  GPIO_Write(GPIOB,(i<<8)|(GPIO_ReadOutputData(GPIOB)&0x0fff));
        E = 1;//����
        delay_ms(4);
        E = 0;
				
				delay_ms(1);
        GPIO_Write(GPIOB,(i<<12)|(GPIO_ReadOutputData(GPIOB)&0x0fff));
        E = 1;  //����д��

			  delay_ms(4);
        E = 0;    	
	
				
	

}
void LCD1602Write_com(uint i)        //д����
{
        RS = 0; //ָ��


			  GPIO_Write(GPIOB,(i<<8)|(GPIO_ReadOutputData(GPIOB)&0x0fff));
        E = 1;  //����д��

			  delay_ms(4);
        E = 0;     
	     delay_ms(1);
       GPIO_Write(GPIOB,(i <<12)|(GPIO_ReadOutputData(GPIOB)&0x0fff));
        E = 1;  //����д��

			  delay_ms(4);
        E = 0;    	
}
void LCD1602Init()                 //LCD1602
{

  //////////////
	//////////////	   	LCD
	//////////////
				 GPIO_InitTypeDef  GPIO_InitStructure;
					
				 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ�ܶ˿�ʱ��
					
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //�˿�����
				 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
				 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
				 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��
				 GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);						 //

				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	    // 
				 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				          //������� ��IO���ٶ�Ϊ50MHz
				 GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1); 						        //
				
				GPIO_Write(GPIOB,0x00ff&GPIO_ReadOutputData(GPIOB));delay_ms(500);

	      RS = 0; //ָ��


			  GPIO_Write(GPIOB,(38<<8)|(GPIO_ReadOutputData(GPIOB)&0x0fff));
        E = 1;  //����д��
//				mDelay(11);
			  delay_ms(4);
        E = 0;   
				
					LCD1602Write_com(0x28);	//	LCD1602Write_com(0x08);		
					LCD1602Write_com(0x01);  //����
          	
          LCD1602Write_com(0x0c);       			
          LCD1602Write_com(0x06);      
 
}

void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s)
		{
						if (y == 0)
				{
						LCD1602Write_com(0x80 + x); //first line
				}
						else
				{
						LCD1602Write_com(0xC0 + x); //second line
				}
				while (*s)
				{
						LCD1602Write_data( *s);
						s ++;
				}
		}
		
void LCD_Write_Number(unsigned char x,unsigned char y,double num,uchar bit)	  //display number
{
		uchar len=1;
  	uchar i;
    char s[16] ;	
	   long long  num_long  = 0;
	  num_long = (long long)num;
	   
	
	if (y == 0)
				{
						LCD1602Write_com(0x80 + x); //first line
				}
						else
				{
						LCD1602Write_com(0xC0 + x); //second line
				}
	
	  if(num_long<0){len++;num_long=-num_long;}
		while(num_long=num_long/10){len++;}
	  num_long = (long long)(num*pow(10,bit));
	  for(i=0;i<bit;i++)
    {
				 s[i] = 	table[num_long%10];
			 	num_long = num_long/10;
		}	
		s[i] = '.';
		for(i++;i<bit+len+1;i++)
    {
				 s[i] =	table[num_long%10];
				 num_long = num_long/10;
		}	;
		if(num_long<0) s[i] = '-';
		do{LCD1602Write_data(s[--i]);}while(i>0);
}


