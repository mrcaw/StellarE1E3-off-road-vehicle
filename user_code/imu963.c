
#include "zf_libraries_headfile.h"


struct icm att,att_2;  //�ṹ����ֵ

float g =  9.7949;
//*********************		������У׼		*****************************
float B[6] = {0.99999,0.00009,0.000089,0.99,-0.0001,1.00014};  //У��ֵ
float MagOffset[3] = {-0.00012,0.00011,0.000138};

float yaw=0.0,roll=0.0,pitch=0.0,Dir = 0.0;

float groy_roll = 0.0,groy_pitch= 0.0,groy_yaw = 0.0,acc_roll = 0.0,acc_pitch = 0.0;  //���ٶȻ�������ٶȼƼ���roll��pitch
float gyro_P = 0.9,acc_P = 0.1;  //�����Ǳ���,���ټƱ���

float norm = 0.0; //ʸ����ģ����Ԫ���ķ���
float Eorr = 0.35,yaw_last =0.0,yaw_u =0.0 ;

float angle_speed, yaw_speed[5] = {0.0,0.0,0.0,0.0,0.0};

//************************	һ�׻���ֵ		*******************************
float mag_ratio = 0.0;		//�شżƱ���
float gyro_ratio = 1.0;		//�����Ǳ���

float last_angle = 0.0,pitch_out;
uint8 first = 0;
float yaw_north,roll_out;
int16 imu_turns=0;


imu963ra_measurement_data_struct imu_gyro_data;
void getimu_value(void)
{

        float gyro_now;

            // ��ȡ���ٶȼ�����

        // ��ȡ����������
      imu963ra_get_gyro(&imu_gyro_data);

        att.icm_gz = -(((float)imu_gyro_data.z)- att_2.icm_gz ) /14.3;


    gyro_now = att.icm_gz * gyro_ratio;


		angle_speed =  gyro_now ;  //������ٶ�

		yaw  -= angle_speed* 0.005f;   //����Ƕ�

		if(yaw >360 )
        {
        yaw = yaw- 360;
        imu_turns++;
        }
		else if(yaw<0)
		{
			yaw = yaw + 360;
			imu_turns--;
		}
		last_angle = Dir;
		pitch_out=pitch*63;

}

void zero(void)
{
	int i = 0;

	att.icm_ax = 0;
	att.icm_ay = 0;
	att.icm_az = 0;

	att.icm_gx = 0;
	att.icm_gy = 0;
	att.icm_gz = 0;

	for(i=0;i<500;i++)
	{
      imu963ra_get_gyro(&imu_gyro_data);




		att.icm_gx = ((float)imu_gyro_data.x);
		att.icm_gy = ((float)imu_gyro_data.y);
		att.icm_gz = ((float)imu_gyro_data.z);

		att_2.icm_gx +=  att.icm_gx;
		att_2.icm_gy +=  att.icm_gy;
		att_2.icm_gz +=  att.icm_gz;

		zf_delay_ms(5);
	}
  att_2.icm_ax = att_2.icm_ax * 0.002;
  att_2.icm_ay = att_2.icm_ay * 0.002;
  att_2.icm_az = att_2.icm_az * 0.002;

	att_2.icm_gx = att_2.icm_gx * 0.002;
  att_2.icm_gy = att_2.icm_gy * 0.002;
  att_2.icm_gz = att_2.icm_gz * 0.002;

	att.icm_ax = 0;
	att.icm_ay = 0;
	att.icm_az = 0;
	att.icm_gx = 0;
	att.icm_gy = 0;
	att.icm_gz = 0;
}

