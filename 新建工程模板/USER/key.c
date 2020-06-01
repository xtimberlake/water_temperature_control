#include "key.h"
#include  "sys.h"
#include "delay.h"

void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_5;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE5,4,3
	

}


unsigned char scan(unsigned char mode)
{
		static unsigned char key_up=1;
		if(mode) key_up=1;
		if(key_up&&(KEY_SET==0||KEY_INC==0||KEY_DEC==0))
		{
		delay_ms(10); 
		key_up=0;
		if(KEY_SET==0)return SET_PRES;
		else if(KEY_INC==0)return INC_PRES;
		else if(KEY_DEC==0)return DEC_PRES;
		}
		else if(KEY_SET==1&&KEY_INC==1&&KEY_DEC==1)key_up=1;
		return 0;
}


