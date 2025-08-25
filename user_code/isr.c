/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          isr
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.10.2
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#include "zf_libraries_headfile.h"

// 对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用 interrupt_global_enable(0); 来开启中断嵌套
// 简单点说实际上进入中断后TC系列的硬件自动调用了 interrupt_global_disable(); 来拒绝响应任何的中断，因此需要我们自己手动调用 interrupt_global_enable(0); 来开启中断的响应。
int8 index_Motor20ms = 0;
int8 Motor_20msINTFlag = 0;
int8 index_Servo = 0;
int8 Isp_20msINTFlag = 0;
int8 index_Isp20ms = 0;
int8 BLTFlag_500ms = 0;
int8 BLT_500ms = 0;
int8 subs_flag=0;
int8 subs_index;
double gnss_angle,error_gps_angle;
//int16 encoder1;
int8 motor_go=0;//启动标志位，置1启动
int16 count_distance,str_go_index=0,encoder_count;
int8 stright_go=1;//舵机控制标志位，置1开启舵机控制，置0直行
int8 sub2_ctrl_flag=0,sub1_ctrl_flag,sub3_ctrl_flag;
float yaw_relative,encoder_dis_rpm,encoder_rpm,encoder_rpm1;
uint8 target_point1=1;
uint8 subject;
uint32 time_flag=0;
uint16 phase_time;
void pit_handler1(uint32 event, void *ptr)//5MS
{
	(void)event;
	*(uint8 *)ptr = ZF_TRUE;
	getimu_value();//陀螺仪更新中断
}
void pit_handler2(uint32 event, void *ptr)//10MS
{
	(void)event;
	*(uint8 *)ptr = ZF_TRUE;
    if(subs_ctrl==0&&esp_ctrl==0)
    {
        gps_angle1();
        subject1();
    }



}
void pit_handler3(uint32 event, void *ptr)//10MS
{
	(void)event;
	*(uint8 *)ptr = ZF_TRUE;

    if(motor_go) time_flag++;
   if(motor_go==0)
	   {
	   	   index_Isp20ms++;//屏幕20ms中断
	   	BLT_500ms++;
	   	if(BLT_500ms>=10)
	   		{
	   			BLTFlag_500ms=1;
	   			BLT_500ms=0;

	   		}
	   }

     if(index_Isp20ms == 2)//20ms处理按键进程
     {
         Isp_20msINTFlag = 1;
         Key_press(1, KEY1);
         Key_press(2, KEY2);
         Key_press(3, KEY3);
         Key_press(4, KEY4);
         key_events();
         index_Isp20ms = 0;
     }
   subs_flag=1;

   zf_encoder_get_count(ENCODER_TIM5,&encoder_count);//读取编码器
   zf_encoder_clear_count(ENCODER_TIM5);
   encoder_rpm=(float)encoder_count/10.0f*0.537;//编码器数值转换为dm/s
}
void pit_handler4(uint32 event, void *ptr)
{
	(void)event;
	*(uint8 *)ptr = ZF_TRUE;

}
uint8 rx_num,rx_data[30],rx_buff,i,k,para_choose,data_check,rx_data2[30],rx_num2,data_check2,yinhao_flag,NFC[30],NFC_NUM;
int16 esp_para[10],esp_speed,esp_servo;
float final_data;
void uart_handler (uint32 event, void *ptr)
{
	//zf_fifo_obj_struct *fifo_ptr = (zf_fifo_obj_struct *)ptr;
	 (void)ptr;
    if(UART_INTERRUPT_STATE_RX & event)
    {
    	rx_buff=0;
        zf_uart_query_byte(UART_3, &rx_buff);

        rx_data[rx_num]=rx_buff;
        rx_num++;
        if (rx_data[0]!=0x4B)
        {
        	rx_num=0;
        	memset(rx_data,0,10);

        }
        if(rx_data[rx_num-1]==0x21)
        {
        	k=0;
        	for(i=2;i<rx_num;i++)
        	{
        		if(rx_data[i]>=0x30&&rx_data[i]<=0x39&&k==0)
        		{
        			final_data=final_data*10+rx_data[i]-0x30;
        		}
        		else if(rx_data[i]>=0x30&&rx_data[i]<=0x39&&k)
				{
        			final_data=final_data+(float)(rx_data[i]-0x30)/pow(10,k);
        			k++;
				}
        		else if(rx_data[i]==0x2e)
        		{
        			k=1;
        		}
        	}
        	if(rx_data[1]==0x50) Kp_SPEED=final_data;
        	else if(rx_data[1]==0x49) Ki_SPEED=final_data;
        	else Kd_SPEED=final_data;
        	final_data=0;
        	rx_num=0;
        	memset(rx_data,0,10);

        }

    }







}




