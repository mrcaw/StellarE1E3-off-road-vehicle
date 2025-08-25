/*
 * pid.c
 *
 *  Created on: 2025年1月9日
 *      Author: ever.youthful
 */
#include "zf_libraries_headfile.h"

uint8 rapm_flag,run_before=1;
void subject1(void)///////主要运行处理函数
{

    if(point1[(target_point1-0)*2]==0&&point1[(target_point1-0)*2+1]==0)  motor_go=0;//检测是否运行到最后一个点了
             if(motor_go==0)//停车/////
             {
            	 zf_pwm_set_duty(BLDC_AP, 0);
            	 zf_gpio_set_level(BLDC_AI,1);
             }
             else if(motor_go==1)/////
            {
            	  if(target_point1==1)//利用第一个点拟合航向角
				 {
            		   if(distance<=stop_dis)//减速条件
						{
						   speed_target=min_speed;
						}

            		        else if(distance>stop_dis)
            		        {
            		        	speed_target=max_speed;
                                	//speed_up(max_speed);
            		        }
            		   PID_speed11( speed_target,encoder_rpm);
					 servo_ctrl(yaw+imu_turns*360);
					 if(distance<1.3)//达成换点条件
				   {
						 if(target_point1==gps_index_save[2]||target_point1==gps_index_save[3]) rapm_flag=1;//飞坡标志位

						 target_point1++;//换点
						yaw= gnss_info.direction;//陀螺仪赋值航向角
					   imu_turns=0;
						  // direct_run_dis=get_two_points_distance(point2[target_point2*2],point2[target_point2*2+1],point2[(target_point2-1)*2],point2[(target_point2-1)*2+1]);
				   }
				 }

				 else
				 {

					    if(fabs(error_gps_angle)>30) speed_target=min_speed; //车身偏移减速
					    else  if(distance<=stop_dis)
						{
						  speed_target=min_speed;
						}
						else if(distance>stop_dis)
						{
							 speed_up(max_speed);
							 speed_target=max_speed;
						}
					    if(rapm_flag)  speed_target=45;//飞坡速度
					    PID_speed11( speed_target,encoder_rpm);
			            servo_ctrl(error_gps_angle);
						if(distance<=1.4)
						{
							if(target_point1==gps_index_save[2]||target_point1==gps_index_save[3]) rapm_flag=1;
							else rapm_flag=0;
							target_point1++;

						}
				 }
            }
}
void my_subs(void)
{
    if(subs_flag)//遥控器控制函数
    {
        subs_flag=0;

        if(esp_ctrl==1&&subs_ctrl==0)
		  {
			   if(esp_stop)
			   {
				   pwm_out=0;
				   zf_pwm_set_duty(SERVO_MOTOR_PWM , servo_mid+esp_servo);

			   }
			   else
			   {
				   zf_pwm_set_duty(SERVO_MOTOR_PWM , servo_mid+esp_servo);
				   pwm_out=esp_speed;
			   }
		  }
        if(1 == uart_receiver.finsh_flag)                            // 帧完成标志判断
        {
            if(1 == uart_receiver.state)                             // 遥控器失控状态判断
            {


                if(subs_motor_ctrl==0) subs_motor_ctrl=uart_receiver.channel[2];
                if(subs_motor_ctrl!=uart_receiver.channel[2])
                {
                    subs_motor_ctrl=uart_receiver.channel[2];
                    motor_go=!motor_go;
                    yaw=0;
                    imu_turns=0;
                  //  point1[0]=gnss_info.latitude;
                  //  point1[1]=gnss_info.longitude;
                }
                if(uart_receiver.channel[3]>1600)
                {
                    subs_ctrl=1;
                    motor_go=0;
                }
                else if(uart_receiver.channel[3]<500)  subs_ctrl=0;

                if(subs_ctrl)
                {
                    dir=(uart_receiver.channel[0]-1000)*servo_max/800;
                    if(dir>servo_max)  dir=servo_max;//限幅
                    if(dir<-servo_max)  dir=-servo_max;
                    zf_pwm_set_duty(SERVO_MOTOR_PWM , servo_mid+dir);

//                    pwm_out=(-uart_receiver.channel[1]+992)*SPEED_MAX/800;
//                               if(pwm_out>SPEED_MAX)  pwm_out=SPEED_MAX;//限幅
//                               if(pwm_out<-SPEED_MAX)  pwm_out=-SPEED_MAX;
//                                PID_speed11( pwm_out,encoder_rpm);
                    pwm_out=(-uart_receiver.channel[1]+992)*PWM_MAX/800;
                    if(pwm_out>=0)
                     {
                        zf_gpio_set_level(BLDC_AI,1);
                        zf_pwm_set_duty(BLDC_AP, pwm_out);
                     }
                     else
                     {
                         zf_pwm_set_duty(BLDC_AP, -pwm_out);
                         zf_gpio_set_level(BLDC_AI, 0);
                     }

                }


             }
         }


    }
}
