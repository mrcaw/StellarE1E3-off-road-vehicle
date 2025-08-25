/*
 * isp2.0.h
 *
 *  Created on: 2023Äê3ÔÂ12ÈÕ
 *      Author: everyouthful
 */

#ifndef CODE_ISP2_0_H_
#define CODE_ISP2_0_H_

#include "zf_libraries_headfile.h"


extern int Motor_PWM_Adjust ;
extern unsigned char Read_Flash_index;
extern float draw_point_x,draw_point_y;
void Isp_init(void);
void Isp_menu_display(void);
void draw_point(uint16 x, uint16 y, const uint16 color);
void isp_display(float data1);
void isp_line1(void);
void isp_line2(void);
void isp_manu1(void);
void isp_manu4(void);
void isp_manu2(void);
void isp_manu3(void);
void ips_displaymenu(void);
void manu1(void);
void manu2(void);
#endif /* CODE_ISP2_0_H_ */
