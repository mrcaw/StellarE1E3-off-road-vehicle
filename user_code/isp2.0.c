/*
 * isp2.0.c
 *

 *      Author: ever.youthful
 */
#include "zf_libraries_headfile.h"




#define IPS200_TYPE     (IPS200_TYPE_SPI)

//  motor  servo
//extern PID_TypeDef ServoPID_polish;
int Motor_PWM_Adjust = 6000;
unsigned char Read_Flash_index = 0;

float draw_point_x,draw_point_y;
void ips_displaymenu(void)
{
  switch (SWITCH_State)
  {
    case 0:
      {
         manu1();
      }break;
       case 1:
      {
        manu2();
      }break;
      default:break;
  }
}

void manu2(void)//按键调速菜单
{
	switch (key_options2)
	      {
	          case 1:
	          {
	              ips200_show_string(0, 0,  "max_s<-");
	              ips200_show_string(0, 20, "min_s  ");

	              //ips200_show_string(0,140, "ramp3  ");
	          }break;
	          case 2:
	          {
	              ips200_show_string(0, 0,  "max_s  ");
	              ips200_show_string(0, 20, "min_s<-");

	          }break;

	      }
    ips200_show_float(100,0, max_speed,2,1);
    ips200_show_float(100,20,min_speed,2,1);

    ips200_show_string(0, 40, "p");
    ips200_show_string(0, 60, "i");
    ips200_show_string(0, 80, "d");

    ips200_show_float(100,40, Kp_SPEED,2,1);
    ips200_show_float(100,60,Ki_SPEED,2,1);
    ips200_show_float(100,80,Kd_SPEED,2,1);
}
void manu1(void)//菜单
{
    switch (key_options1)
      {
          case 1:
          {
              ips200_show_string(0, 0,  "Read<-");
              ips200_show_string(0, 20, "Save  ");
              ips200_show_string(0, 40, "Take  ");
              ips200_show_string(0, 60, "Point  ");
              ips200_show_string(0, 100, "ramp1  ");
              ips200_show_string(0,120, "ramp2  ");
              ips200_show_string(0,140, "GO  ");
              //ips200_show_string(0,140, "ramp3  ");
          }break;
          case 2:
          {
              ips200_show_string(0, 0,  "Read  ");
              ips200_show_string(0, 20, "Save<-");
              ips200_show_string(0, 40, "Take  ");
              ips200_show_string(0, 60, "Point  ");

              ips200_show_string(0, 100, "ramp1  ");
              ips200_show_string(0,120, "ramp2  ");
              ips200_show_string(0,140, "GO  ");
          }break;
          case 3:
          {
              ips200_show_string(0, 0,  "Read  ");
              ips200_show_string(0, 20, "Save  ");
              ips200_show_string(0, 40, "Take<-");
              ips200_show_string(0, 60, "Point  ");

              ips200_show_string(0, 100, "ramp1  ");
              ips200_show_string(0,120, "ramp2  ");
              ips200_show_string(0,140, "GO  ");
          }break;
          case 4:
          {
              ips200_show_string(0, 0,  "Read  ");
              ips200_show_string(0, 20, "Save  ");
              ips200_show_string(0, 40, "Take  ");
              ips200_show_string(0, 60, "Point<-");

              ips200_show_string(0, 100, "ramp1  ");
              ips200_show_string(0,120, "ramp2  ");
              ips200_show_string(0,140, "GO  ");
          }break;
          case 5:
          {
              ips200_show_string(0, 0,  "Read  ");
              ips200_show_string(0, 20, "Save  ");
              ips200_show_string(0, 40, "Take  ");
              ips200_show_string(0, 60, "Point  ");

              ips200_show_string(0, 100, "ramp1  ");
              ips200_show_string(0,120, "ramp2  ");
              ips200_show_string(0,140, "GO  ");
          }break;
          case 6:
          {
              ips200_show_string(0, 0,  "Read  ");
              ips200_show_string(0, 20, "Save  ");
              ips200_show_string(0, 40, "Take  ");
              ips200_show_string(0, 60, "Point  ");

              ips200_show_string(0, 100, "ramp1<-");
              ips200_show_string(0,120, "ramp2  ");
              ips200_show_string(0,140, "GO  ");
          }break;
          case 7:
          {
              ips200_show_string(0, 0,  "Read  ");
              ips200_show_string(0, 20, "Save  ");
              ips200_show_string(0, 40, "Take  ");
              ips200_show_string(0, 60, "Point  ");

              ips200_show_string(0, 100, "ramp1  ");
              ips200_show_string(0,120, "ramp2<-");
              ips200_show_string(0,140, "GO  ");
          }break;
          case 8:
          {
              ips200_show_string(0, 0,  "Read  ");
              ips200_show_string(0, 20, "Save  ");
              ips200_show_string(0, 40, "Take  ");
              ips200_show_string(0, 60, "Point  ");

              ips200_show_string(0, 100, "ramp1  ");
              ips200_show_string(0,120, "ramp2  ");
              ips200_show_string(0,140, "GO<-");
          }break;
          default:break;
      }

    ips200_show_uint(120, 60, gps_index1, 3);
    ips200_show_uint(120, 100,  gps_index_save[2], 3);
    ips200_show_uint(120, 120, gps_index_save[3], 3);
    ips200_show_uint(120, 140, motor_go, 1);
    ips200_show_string(0,180,"r_d:");   ips200_show_float(40,180,encoder_rpm,2,1);

    ips200_show_float(40,200, point1[0],3,6);ips200_show_float(140,200,point1[1],3,6);
    //ips200_show_float(40,220, point1[2],3,6);ips200_show_float(140,220,point1[3],3,6);


    ips200_show_string(0,260,"time"); ips200_show_float(40,260,(float )time_flag/100,3,2);
    ips200_show_string(80,260,"hall"); ips200_show_uint(140,260,hall_now,2);
    ips200_show_string(0,280,"tar");  ips200_show_uint(60, 280, target_point1, 3);
    ips200_show_string(80,280,"y");    ips200_show_float(115,280,yaw,3,2);

    ips200_show_float(0,300,distance,3,1);
    ips200_show_string(110,300,"sate:");    ips200_show_uint(150,300,gnss_info.satellite_used,3);
}







void draw_point(uint16 x, uint16 y, const uint16 color)
{
    ips200_draw_point(x, y, color);
    ips200_draw_point(x-1, y-1, color);
    ips200_draw_point(x-1, y, color);
    ips200_draw_point(x, y-1, color);
}
