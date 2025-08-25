/*
 *
 *
 *  Created on: 2023年3月12日
 *      Author: everyouthful
 */

#ifndef _PID1_H
#define _PID1_H
#include "zf_libraries_headfile.h"
#define BLDC_AP PWM_TIM3_CH1_E4//IfxGtm_ATOM0_6_TOUT42_P23_1_OUT
#define BLDC_AI D14//P21_4
extern int16 out_increment ,out,speed_get,output,output_last;
extern int16 speed_far,speed_mid,speed_close,speed_turn;//mid2000,close1700
extern int8 yaw_45en,imu_turn_dir,turn_round_flag;//0右转，1左转
extern uint8 ctrl_flag,ctrl_en,gps_index1,gps_index2,gps_index3,pile_num,pile_cnt;
extern float min_speed,max_speed,stop_dis,err_last,err_last_last,err_all,yaw_Overall,yaw_turn,pile_dis,car_pile_dis,direct_run_dis,speed_target;
extern double add_angle, distance;;
extern float paramenter[10],Kd_SPEED,Ki_SPEED,Kp_SPEED;
#define max_output 6800 // 输出限幅（如PWM最大值）
void dianji(void);
void PID_speed11( int16 target,int16 feedback);
void gps_servo_ctrl(double err);
void gps_part1(void);
void gps_part2(void);
void gps_part3(void);
void motor_speed(int16 tar_speed);
void gps_sim_ctrl(float err);
void gps_sub2_ctrl(float err);
void dianji1(void);
void gps_sim_ctrl2(float err);
void dianji2(void);
void servo_ctrl(double err);
void speed_up(uint max_speed);

typedef struct
{
    float kp;   // P
    float ki;   // I
    float kd;   // D
    float imax; // 积分限幅

    float out_p; // KP输出
    float out_i; // KI输出
    float out_d; // KD输出
    float out;   // pid输出

    float integrator;      //< 积分值
    float last_error;      //< 上次误差
    float last_derivative; //< 上次误差与上上次误差之差
    unsigned long last_t;  //< 上次时间
} pid_param_t;

void Brush_Motor_Pid(float err);




#endif



