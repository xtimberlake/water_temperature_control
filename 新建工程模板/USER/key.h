#ifndef __KEY
#define __KEY


#define INC_PRES 		1	//KEY INC����
#define DEC_PRES	  2	//KEY DEC����
#define SET_PRES   	3	//KEY SET����

#define KEY_INC  PAin(3)//��ȡ����INC
#define KEY_DEC  PAin(4)//��ȡ����DEC
#define KEY_SET  PAin(5)//��ȡ����SET

unsigned char scan(unsigned char mode); 
void KEY_Init(void);



#endif 
