/*
 * key.h
 *
 *  Created on: 2023年3月12日
 *      Author:everyouthful
 */

#ifndef CODE_KEY_H_
#define CODE_KEY_H_

#include "zf_libraries_headfile.h"


typedef enum
{
   CHECK=0,//0为按键检测状态
   COMFIRM = 1,//1为按键确认状态
   RELEASE = 2,//2为按键释放状态
}KEY_STATE;

typedef struct
{
   uint8 Level;//电平状态
   uint8 State;//0为按键检测状态；1为按键确认状态；2为按键释放状态
   uint8 Event;//相应的事件
}Key_Mode;

extern unsigned char Buzzer_Flag,Buzzer_Count;
extern unsigned char SWITCH_State;
extern Key_Mode  PIDadjust_p22[7];
extern unsigned char  Key_LongCount[6], SWITCH_State;
extern unsigned char Start_Turning_Flag;
extern Key_Mode  GPS_CollectionPoint_P22[2];
 extern uint8  key_function1 ,gps_index_save[20], key_options,key_options1,key_options2,key_options3,key_options4,ramp_point,turn_point,bump_point,bridge_point;
extern  int8 long_pressFlag,pid_ch,flash_save,flash_read;


extern double rectify_long,rectify_lat;








void Key_Init(void);
void SwitchKey_State(void);
void Key_Context_Processing(void);
void key_events(void);

void Key_press(int i,zf_gpio_pin_enum pin);
void Get_GPSPoint_Key(int i,Key_Mode *GPS_CollectionPoint_P22,zf_gpio_pin_enum pin);

void Beep_ON(void);
void Beep_OFF(void);

#endif /* CODE_KEY_H_ */
