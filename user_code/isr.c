/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          isr
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.10.2
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#include "zf_libraries_headfile.h"

// ����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ�� interrupt_global_enable(0); �������ж�Ƕ��
// �򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ������� interrupt_global_disable(); ���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ����� interrupt_global_enable(0); �������жϵ���Ӧ��
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
int8 motor_go=0;//������־λ����1����
int16 count_distance,str_go_index=0,encoder_count;
int8 stright_go=1;//������Ʊ�־λ����1����������ƣ���0ֱ��
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
	getimu_value();//�����Ǹ����ж�
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
	   	   index_Isp20ms++;//��Ļ20ms�ж�
	   	BLT_500ms++;
	   	if(BLT_500ms>=10)
	   		{
	   			BLTFlag_500ms=1;
	   			BLT_500ms=0;

	   		}
	   }

     if(index_Isp20ms == 2)//20ms����������
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

   zf_encoder_get_count(ENCODER_TIM5,&encoder_count);//��ȡ������
   zf_encoder_clear_count(ENCODER_TIM5);
   encoder_rpm=(float)encoder_count/10.0f*0.537;//��������ֵת��Ϊdm/s
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




