/*
 *
 *
 *  Created on: 2023Äê3ÔÂ12ÈÕ
 *      Author: everyouthful
 */
#include "zf_libraries_headfile.h"
#ifndef MY_FLASH_H_
#define MY_FLASH_H_

#define point_num_max 40
extern  uint16 exposure_time_save[1];
extern double point1[point_num_max*2];

void Flash_Save_Point2(void);
void Flash_Save_Point1(void);
void Flash_Save_Point3(void);
void Flash_read_Point1(void);
void Flash_read_Point2(void);
void Flash_read_Point3(void);
void Flash_read_PID(void);
void Flash_Save_PID(void);
void Flash_Save_index(void);
void Flash_read_index(void);


#endif /* CODE_TRACK_H_ */
