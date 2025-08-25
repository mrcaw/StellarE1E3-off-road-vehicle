/*
 * my_flash.c
 *
 *  Created on: 2025年1月9日
 *      Author: ever.youthful
 */
#include "zf_libraries_headfile.h"
double point1[point_num_max*2];

 uint16 exposure_time_save[1];

void Flash_Save_Point1(void)
{
   if (zf_flash_check_page(0, 0) == 1)
    {
	   zf_flash_erase_page(0, 0);
    }

   zf_flash_write_page(0, 0, (uint32*)point1,400); //从第2页中写入数据

}

void Flash_read_Point1(void)
{

   zf_flash_read_page(0, 0,(uint32*) point1,400); //从第二页中读取数据
}


void Flash_Save_index(void)
{

     if (zf_flash_check_page(0,1) == 1)
    {
    	 zf_flash_erase_page(0, 1);
    }

     zf_flash_write_page(0,1,(uint32*)gps_index_save, 20);

}
void Flash_read_index(void)
{

	zf_flash_read_page(0, 1,(uint32*) gps_index_save, 20);
}
