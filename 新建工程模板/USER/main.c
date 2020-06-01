#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "ds18b20.h"
#include "lcd1602.h"
#include "key.h"
#include "pid.h"
#include "timer.h"

extern int ticks;
double temperature;
static double temp_fdb;
static short temp_ref;
float relate_pwm;
double setting_temperture; 
pid_t pid_temp;
int GET_TEMP_SIGN=0;
int PID_CAL_SIGN=0;
int GET_KEY_SIGN=0;
		u8 key=0;
	  u16 times=0;
	  u8 start=0;
		
void init();           //��ʼ������
void PID_CALCULATE();  //PID�������
void Get_Temp();       //��ȡ��ǰ�¶�
void get_key();        //��ȡ����״̬


int main(void)
{		
		init(); //ϵͳ��ʼ������������ϵͳʱ�ӡ���ʱ����DS18B20��LCD1602����������GPIO��
		PID_struct_init(&pid_temp, POSITION_PID, 19999, 19999,
									700.0f,	1.50f,	1000.0f	); 		 	//PID�ṹ���ʼ��									
		setting_temperture=15;
		LCD_Write_Number(11,0,setting_temperture,1);	//�趨Ĭ��Ŀ���¶�
		start=0;	
	
		while(1)
    {

					if(start&&PID_CAL_SIGN) PID_CALCULATE(); //����PID���ı�ռ�ձ�
					else TIM_SetCompare2(TIM2,20000);
						
					if(GET_TEMP_SIGN)
					{
						Get_Temp();	 //��ȡ�¶�ֵ
					}
								 
					if(GET_KEY_SIGN)
					{
						get_key();	 //��ȡ�����������
					}
		}
	
}
void init()
{
		unsigned char s[]="Setting T:";
	  unsigned char s2[]="Current T:";
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
    delay_init();	    	 //��ʱ������ʼ��
    LED_Init();
		KEY_Init();
    DS18B20_Init();
		LCD1602Init();
		TIM3_Int_Init(9,7199);
		TIM2_PWM_Init(19999,7199);
		LCD_Write_String(1,0,s);
		LCD_Write_String(1,1,s2);
		TIM_SetCompare2(TIM2,20000);
}
void PID_CALCULATE()
{


			PID_CAL_SIGN=0;
			temp_ref=setting_temperture;
			pid_calc(&pid_temp,temp_fdb,temp_ref);
			
			if(pid_temp.pos_out<0) relate_pwm=0;
			else relate_pwm=pid_temp.pos_out;
			
			TIM_SetCompare2(TIM2,20000-relate_pwm);


}

void Get_Temp()
{

			GET_TEMP_SIGN=0;
			temp_fdb=DS18B20_Get_Temp()/10.0;
			LCD_Write_Number(11,0,setting_temperture,1);
			times++;
			if(times>=5) 
			{
				times=0;
				LCD_Write_Number(11,1,temp_fdb,1);
				LED0=!LED0;
			}



}
void get_key()
{
			GET_KEY_SIGN=0;
			key=scan(1);
		
		if(key==INC_PRES)
		{
			start=0;
			setting_temperture+=1;
			LCD_Write_Number(11,0,setting_temperture,1);
		}
		else if(key==DEC_PRES)
		{
			start=0;
			setting_temperture-=1;
			LCD_Write_Number(11,0,setting_temperture,1);
		}
		else if(key==SET_PRES)
		{
			temp_ref=setting_temperture;
			start=1;
		}

}
