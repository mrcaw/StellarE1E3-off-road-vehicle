#include "zf_libraries_headfile.h"
/*
 * pid.c
 *
 *  Created on: 2025年1月9日
 *      Author: ever.youthful
 */



double distance;

  float KP=1.08f;
float KI=0.0f;
float KD=0.2f;

    float Kp_SPEED = 5.0f;           // 比例系数
    float Ki_SPEED = 10.0f;           // 积分系数
    float Kd_SPEED = 0.4f;           // 微分系数
    int16_t prev_error; // 上次误差 e(k-1)
    int16_t prev2_error;// 上上次误差 e(k-2)


int16 out_increment =0,out=0,speed_get=0,output,output_last;
int16 speed_far=2000,speed_mid=600,speed_close=600,speed_turn=1000;//mid2000,close1700
int8 yaw_45en,imu_turn_dir,turn_round_flag;//0右转，1左转
uint8 ctrl_flag=1,ctrl_en=1,gps_index1,gps_index2,gps_index3,pile_num=4,pile_cnt=1;
float err_last=0,err_last_last=0,err_all = 0,yaw_Overall,yaw_turn,pile_dis=2,car_pile_dis=1,direct_run_dis,speed_target;
double add_angle;
float paramenter[10]={15,0.0,0.5,6,0.0,0};
float max_speed = 70;
float min_speed =30;
#define min_stop_dis   3
void PID_speed11( int16 target,int16 feedback)//速度环
{
    // 计算当前误差
    int16 current_error = target - feedback;

    // 计算增量项（Δu = Kp*(e(k)-e(k-1)) + Ki*e(k) + Kd*(e(k)-2e(k-1)+e(k-2))）
    float delta = Kp_SPEED * (current_error - prev_error)
                + Ki_SPEED * current_error
                + Kd_SPEED * (current_error - 2 * prev_error + prev2_error);

    // 输出限幅（防止积分饱和）
    output += delta;
    //output_last = output + 500;
    if (output > max_output) output = max_output;
    if (output < -max_output) output = -max_output;

    // 更新误差历史
   prev2_error = prev_error;
   prev_error = current_error;

   if(output>=0)
    {
       zf_gpio_set_level(BLDC_AI,1);
       zf_pwm_set_duty(BLDC_AP, output);
    }
    else
    {
        zf_gpio_set_level(BLDC_AI, 0);
        zf_pwm_set_duty(BLDC_AP, -output);

    }
}


float stop_dis=2.5;
void dianji2(void)
{

    if(fabs(error_gps_angle)>20) speed_target=min_speed; //;pwm_out=1000
    else  if(distance<=stop_dis)
            {
        speed_target=min_speed;
            }
        else if(distance>stop_dis)
        {
            speed_target=max_speed;
            //pwm_out=3500;
        }

    PID_speed11(speed_target, encoder_rpm);

}




void speed_up(uint max_speed)
{
     if(encoder_rpm<20)   speed_target=30;
    else if(encoder_rpm<30)   speed_target=40;
    else if(encoder_rpm<40)   speed_target=50;
    else if(encoder_rpm<50)   speed_target=60;
    else if(encoder_rpm<60)   speed_target=70;
    else if(encoder_rpm<70)   speed_target=80;
    else if(encoder_rpm<80)   speed_target=90;
    if(speed_target>max_speed)   speed_target=max_speed;


}



void servo_ctrl(double err)//负数右打，正数左打，转向环
{

    double integral = 0;
    int output_val;

    if(err>5||err<-5)
    {
        KP=40.0f;
        KI=0.1f;
        KD=0.05f;
    }
    else
    {
        KP=13.0f;
        KI=0.15f;
        KD=0.05f;
    }
    /*积分项*/
    integral += err;                //误差累积
    /*PID算法实现*/
    output_val = KP * err +KI * integral + KD * (err - err_last)+servo_mid; //位置式
    /*误差传递*/
    err_last = err;
    if(output_val<servo_mid-servo_max)
        output_val = servo_mid-servo_max;
    if(output_val>servo_mid+servo_max)
        output_val = servo_mid+servo_max;
    zf_pwm_set_duty(SERVO_MOTOR_PWM,output_val);
}



void speed_judge(float dis)
{
	  if(dis<4)
	    {
	        stop_dis=2;
	        max_speed=50;
	    }
	 else if(dis<6)
    {
        stop_dis=2.5;
        max_speed=70;
    }
    else if(dis<8)
    {
        stop_dis=2.5;
        max_speed=70;
    }
    else
    {
        stop_dis=3;
        max_speed=80;
    }
}










