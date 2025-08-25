/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          isr
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.10.2
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#ifndef _isr_h
#define _isr_h

#include "zf_libraries_headfile.h"

extern int8 motor_go,stright_go,sub2_ctrl_flag,sub1_ctrl_flag,sub3_ctrl_flag,index_Motor20ms,Motor_20msINTFlag,index_Servo,Isp_20msINTFlag,index_Isp20ms,BLTFlag_500ms,BLT_500ms,subs_flag,subs_index;

extern uint32 time_flag;


void pit_handler1(uint32 event, void *ptr);
void pit_handler2(uint32 event, void *ptr);
void pit_handler3(uint32 event, void *ptr);
void pit_handler4(uint32 event, void *ptr);
void uart_handler (uint32 event, void *ptr);
extern double gnss_angle,error_gps_angle;
extern int16 count_distance,str_go_index,encoder_count;
extern float yaw_relative,encoder_dis_rpm,encoder_rpm,encoder_rpm1;

extern uint8 target_point1,NFC[30],subject,hall_now,hall_last,esp_ctrl,esp_stop;

extern unsigned char switch_stateb,VL53_dis_buff[2];

extern uint16 subs_motor_ctrl,VL53_dis;
extern char text[50];
extern float gx_offset , gy_offset , gz_offset;  //x,y��Ľ��ٶ�ƫ����

extern float error_sy_angle,sub_speed;
extern int16 dir,pwm_out,esp_speed,esp_servo;
extern int8 subs_ctrl;
extern float encoder2,encoder_dis;










#endif

