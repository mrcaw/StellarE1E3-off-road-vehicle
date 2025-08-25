/*
 * gps.h
 *
 *  Created on: 2023Äê3ÔÂ12ÈÕ
 *      Author: everyouthful
 */

#ifndef CODE_GPS_H_
#define CODE_GPS_H_

#include "zf_common_typedef.h"
#include "zf_device_gnss.h"

#include "key.h"

#define EPSILON (1e-9)

#define my_EARTH_RADIUS  6378137

typedef struct
{
    double lat;
    double lon;
}gps_point;


typedef struct
{
    double x;
    double y;
}plane_point;

typedef struct
{
    double x;
    double y;
}screen_point;





extern unsigned char Flash_Index;
extern unsigned char SavePoint_Index;
extern unsigned char Tracing_Index;
extern unsigned char Turn_TracingFuction_Flag;

extern float Special_Distance1,Special_Distance2,Special_Distance3;
extern float Common_Distance2,Common_Distance5;
extern float Special_Azimuth0;
extern uint8_t gps_index_last,change_gps_index;


void gps_zero(void);

void gps_angle1(void);
void gps_angle2(void);
void gps_angle3(void);

#endif /* CODE_GPS_H_ */
