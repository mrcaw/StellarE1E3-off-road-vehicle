/*********************************************************************************************************************
* Stellar-SR5E1E3 Opensource Library 即（Stellar-SR5E1E3 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 Stellar-SR5E1E3 开源库的一部分
*
* Stellar-SR5E1E3 开源库 是免费软件
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
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          StellarStudio 7.0.0
* 适用平台          Stellar-SR5E1E3
* 店铺链接          https://www.seekfree.cn/
********************************************************************************************************************/

#include "zf_libraries_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭所有打开的文件
// 第二步 project->clean  等待下方进度条走完


// *************************** 例程硬件连接说明 ***************************
// 使用 Type-C 连接开发板供电 再使用 StellarLINK 连接调试接口即可
// 使用 Type-C 连接开发板供电 再使用 StellarLINK 连接调试接口即可
// 使用 Type-C 连接开发板供电 再使用 StellarLINK 连接调试接口即可


// *************************** 例程测试说明 ***************************
// 1.正常连接供电后 编译本示例程序 然后按照调试说明手册步骤进行烧录调试
//
// 2.同时使用逐飞助手或其他串口助手打开 StellarLINK 的 COM 虚拟串口 波特率设置为 460800
//
// 3.运行本示例程序 可以在逐飞助手或其他串口助手看到串口传输的消息：
//      gnss demo.
//
// 4.同时可以看到 RGB 的蓝色 LED 呈呼吸灯闪烁
//
// 5.可以在串口助手上看到如下串口信息：
//      now time:......
//
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查

uint8 hall_now,pit_flag,hall_last;
unsigned char switch_stateb=0,VL53_dis_buff[2];
uint16 subs_motor_ctrl,VL53_dis;
char text[50];
float gx_offset = 0, gy_offset = 0, gz_offset = 0;  //x,y轴的角速度偏移量
float error_sy_angle=0;
int16 dir,pwm_out;
int8 subs_ctrl;
float encoder2,encoder_dis,meter_out,sub_speed;

uint8   fifo_buffer[16],esp_ctrl,esp_stop;
zf_fifo_obj_struct uart_fifo;



int main (void)
{
     zf_system_clock_init(SYSTEM_CLOCK_300M);                                    // 初始化芯片时钟 工作频率为 300MHz
    //debug_init();                                                               // 初始化默认 Debug UART
    //zf_soft_iic_init(SOFT_IIC_1, 5, VL53_IIC_SCL_PIN, VL53_IIC_SDA_PIN);
    zf_fifo_init(&uart_fifo, FIFO_DATA_8BIT, fifo_buffer, sizeof(fifo_buffer));
    zf_uart_init(UART_3, 115200, UART3_TX_G15, UART3_RX_G14);
    zf_uart_set_interrupt_callback(UART_3, uart_handler, &uart_fifo);
    zf_uart_set_interrupt_config(UART_3, UART_INTERRUPT_CONFIG_RX_ENABLE);

    imu660rb_init();
    zf_delay_ms(500);
    zf_gpio_init(KEY1,  GPI_PULL_UP,GPIO_HIGH);
    zf_gpio_init(KEY2,  GPI_PULL_UP,GPIO_HIGH);
    zf_gpio_init(KEY3,  GPI_PULL_UP,GPIO_HIGH);
    zf_gpio_init(KEY4,  GPI_PULL_UP,GPIO_HIGH);
    zf_gpio_init(SWITCH1,  GPI_PULL_UP,GPIO_HIGH);
    zf_gpio_init(SWITCH2,  GPI_PULL_UP,GPIO_HIGH);
	ips200_init(IPS200_TYPE_SPI);

	zf_pwm_module_init(PWM_TIM3, PWM_ALIGNMENT_EDGE, 17000);//有刷初始化
	zf_pwm_channel_init(BLDC_AP, 0);
	zf_gpio_init(BLDC_AI,  GPO_PUSH_PULL,GPIO_LOW);


	zf_pwm_module_init(servo_tim, PWM_ALIGNMENT_EDGE, SERVO_FREQ);//舵机初始化
	zf_pwm_channel_init(SERVO_MOTOR_PWM , servo_mid);
	zf_encoder_init(ENCODER_TIM5, ENCODER_MODE_DIR, ENCODER_TIM5_A_PLUS_I1 , ENCODER_TIM5_B_DIR_I3 );//编码器初始化
	uart_receiver_init();
	gnss_init(GNSS_TYPE_GN43RFA);
	//gps_zero();
	zero();//陀螺仪采样
	//isp_manu1();
	//VL53_Write_Byte(VL53ADDR, VL53L0X_REG_SYSRANGE_START, VL53_STAR);
	zf_pit_ms_init(PIT_TIM1, 5 , pit_handler1, &pit_flag);
	zf_pit_ms_init(PIT_TIM2, 10, pit_handler2, &pit_flag);
	zf_pit_ms_init(PIT_TIM16, 10, pit_handler3, &pit_flag);
	//zf_pit_us_init(PIT_TIM4, 100, pit_handler4, &pit_flag);

    for( ; ; )
    {

               if(Isp_20msINTFlag)//20ms中断刷新屏幕
               {
                   SwitchKey_State();
                   if(switch_stateb!=SWITCH_State)
                   {
                      ips200_clear();
                      switch_stateb=SWITCH_State;
                   }
            	   ips_displaymenu();

                   Isp_20msINTFlag=0;
               }

               my_subs();//遥控器处理函数
               if(BLTFlag_500ms)
               {
            	   BLTFlag_500ms=0;
            	//   printf("%f\n\r",encoder_rpm);
               }




        // 此处编写需要循环执行的代码
    }
    }

