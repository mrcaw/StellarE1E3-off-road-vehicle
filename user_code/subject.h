
/*
 *
 *
 *  Created on: 2023��3��12��
 *      Author: everyouthful
 */
#ifndef SUBJECT_H_
#define SUBJECT_H_

#include "zf_libraries_headfile.h"
void subject1(void);
void subject2(void);
void subject3(void);
void VL53_Read_nByte(unsigned char dev, unsigned char reg, unsigned char length, unsigned char* data);
void VL53_Write_Byte(unsigned char dev, unsigned char reg, unsigned char data);
void my_subs(void);

#endif /* CODE_DRV_H_ */


