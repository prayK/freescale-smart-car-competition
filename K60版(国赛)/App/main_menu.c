#include "main_menu.h"
#include "include.h"

extern uint8 back_flag;
extern uint8 flag_stopcar;
extern uint8 car_stop_flag;
extern uint8 img[60][CAMERA_W];
extern uint16 center;
extern float dir_center;
extern Site_t site;
Size_t size_m={80,128};
Size_t size_n={80,8};

void main_menu_task(void)  
{
          result_e result;
          KEY_MSG_t keymsg;
          MAIN_INIT:
          ftm_pwm_duty(FTM1, FTM_CH0, (uint16)dir_center);
          center = (uint16)dir_center ;           //舵机保持中值
          while(get_key_msg(&keymsg) == 1);      //清空按键消息
          LCD_clear(BCOLOUR);                     //清屏
          main_menu_init();                       //菜单初始化
          while(1) 
          { 
                    result = main_menu_deal();
                    if(result == RESULT_INIT )
                    { 
                              return;                       //直接退出后，会重新进来
                    } 
                    else if(result == RESULT_TO_MENU )
                    { 
                              goto MAIN_INIT;
                    } 
          } 
}

/***************************************************************************************************/
result_e run_start(void)
{
         KEY_MSG_t keymsg;
         while(get_key_msg(&keymsg) == 1);                   //清空按键消息 
         LCD_clear(BCOLOUR);                                 //清屏 
         systick_delay_ms(1500);                             //发车延时 
         car_stop_flag = 0; 
       
         while(1) 
         { 
                  run(); //标志已经发车
                  while((get_key_msg(&keymsg) == 1))               // 按键处理
                  {
                            if((keymsg.status == KEY_DOWN) && (keymsg.key == KEY_B )) //A键按下时退出
                            {
                                       flag_stopcar = 0;
                                       car_stop_flag = 0;
                                       return  RESULT_TO_MENU;
                            }       
                  } 
         }
}

/***************************************************************************************************/
result_e dir_change(void)
{ 
         KEY_MSG_t keymsg;
         while(get_key_msg(&keymsg) == 1);                   //清空按键消息
         LCD_clear(BCOLOUR);                                  //清屏
         while(1)
         {  
                  dir_change_fun();
                  back_flag=0;
                  return  RESULT_TO_MENU;
         } 
} 

/***************************************************************************************************/
result_e speed_change(void)
{
         KEY_MSG_t keymsg;
         while(get_key_msg(&keymsg) == 1);                   //清空按键消息
         LCD_clear(BCOLOUR);  
         while(1)
         { 
                  speed_change_fun();
                  back_flag=0;
                  return  RESULT_TO_MENU;
         } 
}

/***************************************************************************************************/
result_e ring_set(void)
{
         KEY_MSG_t keymsg;
         while(get_key_msg(&keymsg) == 1);                  //清空按键消息
         LCD_clear(BCOLOUR);  
         while(1)
         {
                  ring_set_fun();
                  back_flag=0;
                  return  RESULT_TO_MENU;
         }
}

/***************************************************************************************************/
result_e control_switch(void)
{
         KEY_MSG_t keymsg;
         while(get_key_msg(&keymsg) == 1);                      //清空按键消息
         LCD_clear(BCOLOUR);  
         while(1) 
         {
                  ParameterWatching_fun();
                  back_flag=0;
                  return  RESULT_TO_MENU;
//                  while(get_key_msg(&keymsg) == 1)               // 按键处理
//                  {
//                            if((keymsg.status == KEY_DOWN) && (keymsg.key == KEY_B )) //A 键 按下时退出
//                            { 
//                                      return  RESULT_TO_MENU;
//                            } 
//                  }
         }
}

/***************************************************************************************************/
result_e image_watch(void)
{
         Site_t site={0,0};
         Site_t site1={0,60};
         KEY_MSG_t keymsg;
         while(get_key_msg(&keymsg) == 1);                //清空按键消息
         LCD_clear(WHITE);                                 //清屏
         LCD_rectangle(site, size_m, WHITE);
         LCD_rectangle(site1, size_n, BLACK);
         while(1)
         {
                  image_watch_fun();
                  while(get_key_msg(&keymsg) == 1)               // 按键处理
                  {
                            if((keymsg.status == KEY_DOWN) && (keymsg.key == KEY_B )) //A 键 按下时退出
                            { 
                                      return  RESULT_TO_MENU;
                            } 
                  }
         }
}

