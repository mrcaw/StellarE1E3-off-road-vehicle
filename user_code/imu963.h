/*
 *
 *
 *  Created on: 2023��3��12��
 *      Author: everyouthful
 */

#ifndef _IMU963_H_
#define _IMU963_H_

#include "zf_libraries_headfile.h"



#define halfT 0.005f
#define Kp 37.048f    //�����Kp,Ki�����ڿ��Ƽ��ٶȼ����������ǻ�����̬���ٶ�
#define Ki 0.1970f
#define XO 0.001220509966  //PI/180/14.3f      0.0012205
#define ZO 0.0002442598   //4090�ĵ���
#define alpha  0.35   //һ�׵�ͨ�˲�ֵ

struct icm{
	float icm_ax;
  float icm_ay;
  float icm_az;

	float icm_gx;
	float icm_gy;
	float icm_gz;

	float mag_x;
	float mag_y;
	float mag_z;
};


 void getimu_value(void);
 extern void zero(void);
void gyroOffsetInit (void) ;
extern float angle_speed;
extern struct icm att,att_2;
extern float yaw,roll,pitch;
extern struct icm att,att_2;
extern float groy_roll, groy_pitch, groy_yaw,acc_roll ,acc_pitch ;  //���ٶȻ�������ٶȼƼ���roll��pitch
extern float Dir;
extern float last_angle ,roll_out,pitch_out;
extern uint8 first ;
extern float yaw_north,roll_out;
extern int16 imu_turns;





#endif


