/*
 * key.c
 *
 *  Created on: 2023��3��12��
 *      Author: ever.youthful
 */




#include "zf_libraries_headfile.h"




uint8 key_options=1,key_options1=1,key_options2=1,ramp_point=6,turn_point=5,bump_point=1,bridge_point=3;
unsigned char SWITCH_State=0;
Key_Mode  PIDadjust_p22[7];
Key_Mode  GPS_CollectionPoint_P22[2];
int8 flash_save=0,flash_read=0;
double rectify_long,rectify_lat;
int8 pid_ch=1;
 int8 long_pressFlag=0;
uint8 gps_index_save[20];//123��gps_index��4��׶Ͱ1��5��׶Ͱ2��6���µ�����7�Լ�֮���Ǹ��µ�λ��
uint8 key_function1 =8,key_function2=2;

void SwitchKey_State(void)
{
    SWITCH_State=zf_gpio_get_level(SWITCH1)+zf_gpio_get_level(SWITCH2)*2;
}



void key_events(void)//����Ӧ���棬������Ӧ�����Ĺ���
{
	  switch (SWITCH_State)
	  {
	    case 0:
	      {
	          if(PIDadjust_p22[1].Event==1)//��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	           {
	              key_options1++;
	              if(key_options1>key_function1) key_options1=1;
	           }

	          if(PIDadjust_p22[2].Event==1)//��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	          {
	              key_options1--;
	              if(key_options1<=0) key_options1=key_function1;
	          }
	          if(PIDadjust_p22[3].Event==1)//��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	           {
	              switch (key_options1)
	              {
	                  case 1://ȡ��
	                  {
	                      Flash_read_Point1();
	                      Flash_read_index();
	                      ips200_show_string(180,300,"read");
	                      gps_index1= gps_index_save[1];
	                  }break;
	                  case 2://���
	                  {
	                    Flash_Save_Point1();
	                    Flash_Save_index();
	                    ips200_show_string(180,300,"save");
	                  }break;
	                  case 3://���
	                  {
	                      ips200_show_string(180,300,"take");
	                      point1[gps_index1*2]=gnss_info.latitude;
	                      point1[gps_index1*2+1]=gnss_info.longitude;
	                      gps_index1++;
	                      gps_index_save[1]=gps_index1;
	                  }break;
	                  case 4://��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	                  {
	                   gps_index1++;
	                  }break;
	                  case 5:
	                  {

	                  }break;
	                  case 6://ѡ����µ�
	                  {
	                	  gps_index_save[2]++;
	                  }break;
	                  case 7:////ѡ����µ�
	                  {
	                	  gps_index_save[3]++;
	                  }break;
	                  case 8://������������������������������������������ҳ����
	                   {
	                	   if(motor_go==0)
						   {
							   motor_go=1;

							   yaw=0;//gnss_get_two_points_azimuth(gnss_info.latitude,gnss_info.longitude,point1[(target_point1-0)*2]+point1[0],point1[(target_point1-0)*2+1]+point1[1]);;
							   imu_turns=0;
						   }
						   else if(motor_go==1)  motor_go=0;

	                   }break;

	                  default:break;
	              }
	           }

	          if(PIDadjust_p22[4].Event==1)
	          {

	              switch (key_options1)
	              {


	                  case 4://��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	                  {
	                   gps_index1--;

	                  }break;


	                  case 6://������������������������������������������ҳ����
	                   {
	                       gps_index_save[2]--;



	                   }break;
	                   case 7://������������������������������������������ҳ����
	                   {
	                       gps_index_save[3]--;

	                   }break;



	                  default:break;
	              }

	          }
	      }break;
	       case 1:
	      {
	          if(PIDadjust_p22[1].Event==1)//��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	           {
	              key_options2++;
	              if(key_options2>key_function2) key_options2=1;
	           }

	          if(PIDadjust_p22[2].Event==1)//��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	          {
	              key_options2--;
	              if(key_options2<=0) key_options2=key_function2;
	          }
	          if(PIDadjust_p22[3].Event==1)//��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	           {
	              switch (key_options2)
	              {
	                  case 1:
	                  {
	                	  max_speed++;
	                  }break;
	                  case 2://��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	                  {
	                	  min_speed++;
	                  }break;

	                  default:break;
	              }
	           }

	          if(PIDadjust_p22[4].Event==1)
	          {

	              switch (key_options2)
	              {
	                  case 1://��һһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһһҳ����
	                  {

	                	  max_speed--;
	                  }break;


	                  case 2://������������������������������������������ҳ����
	                   {
	                	   min_speed--;
	                   }break;


	                  default:break;
	              }

	          }
	      }break;
	       default:break;
	  }



}


void Key_press(int i,zf_gpio_pin_enum pin)//��������
{

         PIDadjust_p22[i].Level = zf_gpio_get_level(pin);

         switch(PIDadjust_p22[i].State)
         {
             //״̬0��û�а�������
             case CHECK:
                 if(PIDadjust_p22[i].Level == 0)//�а�������
                 {
                     PIDadjust_p22[i].State = COMFIRM;//ת��״̬1
                     PIDadjust_p22[i].Event = 0;//���¼�
                 }
                 else
                 {
                     PIDadjust_p22[i].Event = 0;//���¼�
//                     Key_LongCount[i] = 0;
                 }
                 break;
             //״̬1����������ȷ��
             case COMFIRM:
                 if(PIDadjust_p22[i].Level == 0)//ȷ�Ϻ��ϴ���ͬ���� ���� ȷʵ����
                 {
                     PIDadjust_p22[i].State = 2;//ת��״̬2
                    // PIDadjust_p22[i].Event = 1;//�����¼�
                 }
                 else
                 {
                     PIDadjust_p22[i].State = CHECK;//ת��״̬0���� ��
                     PIDadjust_p22[i].Event = 0;//���¼�
                 }
                 break;
             //״̬2�������ɿ�
             case RELEASE:
                 if(PIDadjust_p22[i].Level == 1)//�����ͷţ��˿ڵ͵�ƽ
                 {
                     PIDadjust_p22[i].State = CHECK;//ת��״̬0
                     if(long_pressFlag>50)  PIDadjust_p22[i].Event = 2;
                     else  PIDadjust_p22[i].Event = 1;
                     long_pressFlag=0;
                 }
                 else if(PIDadjust_p22[i].Level == 0)
                 {
                     PIDadjust_p22[i].State = 2;//ά��״̬2
                      long_pressFlag++;
                 }
                 break;

         }//switch


}




