#ifndef __KEY
#define __KEY


#define INC_PRES 		1	//KEY INC按下
#define DEC_PRES	  2	//KEY DEC按下
#define SET_PRES   	3	//KEY SET按下

#define KEY_INC  PAin(3)//读取按键INC
#define KEY_DEC  PAin(4)//读取按键DEC
#define KEY_SET  PAin(5)//读取按键SET

unsigned char scan(unsigned char mode); 
void KEY_Init(void);



#endif 
