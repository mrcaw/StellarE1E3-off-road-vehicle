/*
 * gps.c
 *
 *  Created on: 2023锟斤拷3锟斤拷13锟斤拷
 *      Author: ever.youthful
 */


#include "zf_libraries_headfile.h"
#include "math.h"
int j;
uint8_t gps_index_last=1,change_gps_index;


void gps_zero(void)
{

    for( j=0;j<=point_num_max*2;j++)
    {

        point1[j]=1.0;

    }
    point1[0]=0.0;
    point1[1]=0.0;
    gps_index_save[4]=4;
    gps_index_save[5]=8;
    gps_index_save[6]=0;
    gps_index_save[7]=1;
    gps_index_save[8]=1;
}
void gps_angle1(void)//陀螺仪与点位方位比较得到error，error为正负180
{
    gnss_angle= gnss_get_two_points_azimuth(gnss_info.latitude,gnss_info.longitude,point1[(target_point1-0)*2]+rectify_lat,point1[(target_point1-0)*2+1]+rectify_long);
    distance =gnss_get_two_points_distance(gnss_info.latitude,gnss_info.longitude,point1[(target_point1-0)*2]+rectify_lat,point1[(target_point1-0)*2+1]+rectify_long);
    error_gps_angle=yaw-gnss_angle;
      if(error_gps_angle>180)
      {
        error_gps_angle=error_gps_angle-360;
      }
      if(error_gps_angle<-180)
      {
        error_gps_angle=error_gps_angle+360;
      }
}


