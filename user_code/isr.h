/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          isr
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.10.2
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
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
extern float gx_offset , gy_offset , gz_offset;  //x,y轴的角速度偏移量

extern float error_sy_angle,sub_speed;
extern int16 dir,pwm_out,esp_speed,esp_servo;
extern int8 subs_ctrl;
extern float encoder2,encoder_dis;










#endif

