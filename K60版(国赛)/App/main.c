#include "common.h"
#include "include.h"

extern volatile uint16_t GoalSpeed;
extern float dir_center;
extern int16  FTM_count;
extern uint8 run_flag;
extern float CNST_Value;
extern int32 AllFtmCount;
 
float Param = 10.0;//可以认为是10米
uint8_t flag_stopcar = 0;
uint8_t car_stop_flag = 0;

float dir_zhongzhi;
void pit1_hander(void); 

void main(void) 
{ 
        dir_zhongzhi=dir_center;                      //中值赋值
        init(); 
        key_init(KEY_MAX); 
        pit_init_ms(PIT1,10);                         //10ms 读取一次编码器的值 
        set_vector_handler(PIT1_VECTORn,pit1_hander); //设置中断服务函数到中断向量表里
        enable_irq(PIT1_IRQn);
        while(1) 
        { 
                main_menu_task(); 
        } 
}   
 
void pit1_hander(void) 
{
        if(PIT_TFLG(PIT1) == 1) 
        { 
                PIT_Flag_Clear(PIT1);
                if((User_Stop_Line_JianCe() == 1 && BM1 == 0)  
                 ||(BM2 == 0 && AllFtmCount >= Param * 5000))  
                { 
                        flag_stopcar = 1;
                } 
                if(flag_stopcar == 0)  
                { 
                        Encoder_Read();
                        Speed_Set();
                        if(run_flag == 1)
                        { 
                               SpeedControl();
                        } 
                } 
                else 
                { 
                        Encoder_Read();
                        if (((BM3 == 1) && (FTM_count > 10)) 
                         || ((BM3 == 0) && (FTM_count > 40)))
                        { 
                                GoalSpeed = 0; 
                                SpeedControl(); 
                        } 
                        else
                        { 
                                ftm_pwm_duty(FTM0, FTM_CH2, 0); 
                                ftm_pwm_duty(FTM0, FTM_CH3, 0); 
                        } 
                } 
                key_IRQHandler(); 
        } 
} 

