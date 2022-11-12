#include "common.h"
#include "include.h"
#include "UserInterface.h"

/***********************************主菜单相关***********************************/
#define  MAIN_MENU_STR(main_tab)       main_menu_info[main_tab].str
#define  MAIN_MENU_SITE(main_tab)      main_menu_info[main_tab].site
uint8   main_menu_new_tab = 0;

main_menu_info_t  main_menu_info[MAIN_MENU_MAX] =
{ 
      {"START_RUNING",  {15,  8}},
      {"SERVO_CHANGE",  {15, 29}},
      {"MOTOR_CHANGE",  {15, 50}},
      {"IMAGE_DISPLAY", {12, 71}},
};

//主菜单显示
void main_menu_display(uint8 main_menu_tab)
{
    uint8  i = 0;
    uint16 Color; 
    uint16 BKColor; 
    Site_t siteV = {8, 92};
    //Site_t siteVDis= {8, 111};  
    ASSERT((main_menu_new_tab < MAIN_MENU_MAX) && (main_menu_tab <= MAIN_MENU_MAX));

    if (main_menu_tab == MAIN_MENU_MAX)
    {
        i = MAIN_MENU_MAX - 1;
        main_menu_tab = 0;
    }

    do     
    {
        if (main_menu_tab == main_menu_new_tab) 
        { 
              Color   =  BLUE;
              BKColor =  WHITE;
        }
        else
        { 
              Color   =  BLACK;
              BKColor =  RED;
        }  
        lcd_str(MAIN_MENU_SITE(main_menu_tab), MAIN_MENU_STR(main_menu_tab), Color, BKColor);
        lcd_str(siteV, "BATTERY_VOLTGE:", BLACK, RED); 
        //lcd_str(siteVDis, "", BLUE, RED); //等待电压数据传入
        main_menu_tab++; 
    }
    while(i--);
} 

//主菜单项选择
static void main_menu_select(main_menu_var_e main_menu_ctrl)
{
       ASSERT(main_menu_new_tab < MAIN_MENU_MAX);
       uint8 main_menu_old_tab = main_menu_new_tab;
       switch (main_menu_ctrl) 
       {
              case MAIN_MENU_NEXT: main_menu_new_tab++;
              if (main_menu_new_tab >= (MAIN_MENU_MAX)) 
              { 
                     main_menu_new_tab = 0;
              } 
              break; 

              case MAIN_MENU_PREV: main_menu_new_tab--; 
              if (main_menu_new_tab >= (MAIN_MENU_MAX)) 
              { 
                    main_menu_new_tab = MAIN_MENU_MAX - 1;
              } 
              break;
              default: return;
       }
       main_menu_display(main_menu_old_tab);
       main_menu_display(main_menu_new_tab); 
}

/***********************************电机PID相关**********************************/
#define  MOTOR_STR(motor_tab)        motor_num_info[motor_tab].str
#define  MOTOR_MSITE(motor_tab)      motor_num_info[motor_tab].msite
#define  MOTOR_VALUE(motor_tab)      motor_num_info[motor_tab].val
#define  MOTOR_SITE(motor_tab)       motor_num_info[motor_tab].site
uint8   motor_menu_new_tab = 0; 

motor_menu_info_t  motor_num_info[MOTOR_VAR_MAX] = 
{ 
      {"MOTOR_P: ", {8, 24}, 0, {80, 24},},
      {"MOTOR_I: ", {8, 50}, 0, {80, 50},},
      {"MOTOR_D: ", {8, 76}, 0, {80, 76},},
};

//电机参数页面显示
static void motor_menu_display(uint8 motor_menu_tab)
{
    uint8  i = 0;
    uint16 Color; 
    uint16 BKColor; 
    ASSERT((motor_menu_new_tab < MOTOR_VAR_MAX) && (motor_menu_tab <= MOTOR_VAR_MAX));

    if (motor_menu_tab == MOTOR_VAR_MAX)
    {
        i = MOTOR_VAR_MAX - 1;
        motor_menu_tab = 0;
    }

    do
    {
        if (motor_menu_tab == motor_menu_new_tab) 
        { 
              Color   =  BLUE;
              BKColor =  WHITE;
        }
        else
        { 
                Color   =  BLACK;
                BKColor =  RED;
        } 
        lcd_str(MOTOR_MSITE(motor_menu_tab), MOTOR_STR(motor_menu_tab), Color, BKColor);
        lcd_num_c(MOTOR_SITE(motor_menu_tab), MOTOR_VALUE(motor_menu_tab), Color, BKColor);
        motor_menu_tab++; 
    }
    while(i--);
} 

//对变量进行选择
static void motor_var_select(motor_menu_var_e motor_menu_ctrl)
{
    ASSERT(motor_menu_new_tab < MOTOR_VAR_MAX);
    uint8 motor_menu_old_tab = motor_menu_new_tab;
    switch (motor_menu_ctrl) 
    {
          case  MOTOR_VAR_NEXT:  motor_menu_new_tab++;
          if(motor_menu_new_tab >= (MOTOR_VAR_MAX) )
          {
              motor_menu_new_tab = 0;
          }
          break;

          case  MOTOR_VAR_PREV:  motor_menu_new_tab--;
          if (motor_menu_new_tab >= (MOTOR_VAR_MAX) )
          {
              motor_menu_new_tab = MOTOR_VAR_MAX - 1;
          }
          break;
          default: return;
    }
    motor_menu_display(motor_menu_old_tab);
    motor_menu_display(motor_menu_new_tab);
}

//对变量进行加减操作
static void motor_var_value (motor_menu_var_e ctrl)
{
    ASSERT(motor_menu_new_tab < MOTOR_VAR_MAX);
    switch (ctrl)
    {
           case  MOTOR_VAR_ADD:       MOTOR_VALUE(motor_menu_new_tab)++;                         break;
           case  MOTOR_VAR_SUB:       MOTOR_VALUE(motor_menu_new_tab)--;                         break;
           case  MOTOR_VAR_ADD_HOLD:  MOTOR_VALUE(motor_menu_new_tab) += VAR_VALUE_HOLE_OFFSET;  break;
           case  MOTOR_VAR_SUB_HOLD:  MOTOR_VALUE(motor_menu_new_tab) -= VAR_VALUE_HOLE_OFFSET;  break;
           default:  break;
    }
    motor_menu_display(motor_menu_new_tab);
}

/***********************************舵机PD相关***********************************/
uint8   servo_menu_new_tab = 0; 

#define  SERVO_STR(servo_tab)        servo_num_info[servo_tab].str
#define  SERVO_MSITE(servo_tab)      servo_num_info[servo_tab].msite 
#define  SERVO_VALUE(servo_tab)      servo_num_info[servo_tab].val
#define  SERVO_SITE(servo_tab)       servo_num_info[servo_tab].site

servo_menu_info_t  servo_num_info[SERVO_VAR_MAX] = 
{ 
      {"SERVO_P: ", {8, 46}, 0, {80,46},},
      {"SERVO_D: ", {8, 75}, 0, {80,75},},
};

//舵机参数页面显示
static void servo_menu_display(uint8 servo_menu_tab)
{
    uint8  i = 0;
    uint16 Color; 
    uint16 BKColor; 
    ASSERT((servo_menu_new_tab < SERVO_VAR_MAX) && (servo_menu_tab <= SERVO_VAR_MAX));

    if (servo_menu_tab == SERVO_VAR_MAX)
    {
        i = SERVO_VAR_MAX - 1;
        servo_menu_tab = 0;
    }

    do
    {
        if (servo_menu_tab == servo_menu_new_tab) 
        { 
              Color   =  BLUE;
              BKColor =  WHITE;
        }
        else
        { 
                Color   =  BLACK;
                BKColor =  RED;
        } 
        lcd_str(SERVO_MSITE(servo_menu_tab), SERVO_STR(servo_menu_tab), Color, BKColor);
        lcd_num_c(SERVO_SITE(servo_menu_tab), SERVO_VALUE(servo_menu_tab), Color, BKColor);
        servo_menu_tab++; 
    }
    while(i--);
} 

//对变量进行选择
static void servo_var_select(servo_menu_var_e ctrl)
{
    ASSERT(servo_menu_new_tab < SERVO_VAR_MAX);
    uint8 servo_menu_old_tab = servo_menu_new_tab;
    switch (ctrl) 
    {
          case  SERVO_VAR_NEXT:  servo_menu_new_tab++;
          if (servo_menu_new_tab >= (SERVO_VAR_MAX) )
          {
                servo_menu_new_tab = 0;
          } 
          break;

          case  SERVO_VAR_PREV:  servo_menu_new_tab--;
          if (servo_menu_new_tab >= (SERVO_VAR_MAX) )
          {
                servo_menu_new_tab = SERVO_VAR_MAX - 1;
          }
          break;
          default: return;
    }
    servo_menu_display(servo_menu_old_tab);
    servo_menu_display(servo_menu_new_tab);
}

//对变量进行加减操作
static void servo_var_value (servo_menu_var_e ctrl)
{
    ASSERT(servo_menu_new_tab < SERVO_VAR_MAX);
    switch (ctrl)
    {
           case SERVO_VAR_ADD:       SERVO_VALUE(servo_menu_new_tab)++;                         break;
           case SERVO_VAR_SUB:       SERVO_VALUE(servo_menu_new_tab)--;                         break;
           case SERVO_VAR_ADD_HOLD:  SERVO_VALUE(servo_menu_new_tab) += VAR_VALUE_HOLE_OFFSET;  break;
           case SERVO_VAR_SUB_HOLD:  SERVO_VALUE(servo_menu_new_tab) -= VAR_VALUE_HOLE_OFFSET;  break;
           default:  break;
    }
    servo_menu_display(servo_menu_new_tab);
}

int8  Flag_MainMenu = 0;
uint8 Flag_Left_Key = 0; 
uint8 Flag_Right_Key = 0;
uint8 Flag_Last_Key = 0;
uint8 Flag_Next_Key = 0;

/*********按键事件处理*********/
void Main_Menu_Deal()
{ 
     uint8 Flag_Assist = 0;
     KEY_MSG_t keymsg_MainMenu;
     while (get_key_msg(& keymsg_MainMenu)) 
     { 
            if (keymsg_MainMenu.status == KEY_DOWN)//获取每个按键状态
            { 
                  switch (keymsg_MainMenu.key) //获取是哪个按键按下
                  { 
                          case KEY_L:  //左键 用于选项的选择 上一个 PTD11
                                switch (Flag_Left_Key) //根据标志位判断在哪个界面按下 
                                {
                                       case 0: Flag_MainMenu++; if (Flag_MainMenu > 3); Flag_MainMenu = 0; 
                                               main_menu_select(MAIN_MENU_PREV);           //主界面按下
                                       case 1: motor_var_select(MOTOR_VAR_PREV); break; //电机PID调节界面按下
                                       case 2: servo_var_select(SERVO_VAR_PREV); break; //舵机PD调节界面按下 
                                       default : break; 
                                } break; 

                          case KEY_R: //右键 用于选项的选择 下一个 PTD12
                                switch (Flag_Right_Key)//根据标志位判断在哪个界面按下 
                                {  
                                       case 0: Flag_MainMenu--; if (Flag_MainMenu < -3) Flag_MainMenu = 0; 
                                               main_menu_select(MAIN_MENU_NEXT); break;//主界面按下
                                       case 1: motor_var_select(MOTOR_VAR_NEXT); break;//电机PID调节界面按下
                                       case 2: servo_var_select(SERVO_VAR_NEXT); break;//舵机PD调节界面按下 
                                       default : break; 
                                 } break;

                          case KEY_U: //用于数据调节 加 PTD10
                                switch (Flag_Last_Key)//根据标志位判断在哪个界面按下 
                                { 
                                        case 1: motor_var_value(MOTOR_VAR_ADD); break;//舵机PD调节界面按下 
                                        case 2: servo_var_value(SERVO_VAR_ADD); break;//舵机PD调节界面按下 
                                        default : break; 
                                 } break; 

                          case KEY_D: //用于数据的 减 PTD14
                                switch (Flag_Next_Key)//根据标志位判断在哪个界面按下 
                                { 
                                        case 1: motor_var_value(MOTOR_VAR_SUB); break;//舵机PD调节界面按下 
                                        case 2: servo_var_value(SERVO_VAR_SUB); break;//舵机PD调节界面按下 
                                        default : break; 
                                 } break; 

                          case KEY_B: Flag_Assist++; break; //辅助判断标志位 确定键 PTD13

                          case KEY_A: Flag_Left_Key = 0; Flag_Right_Key = 0; //返回主菜单按键 清0各个标志位 取消键 PTD7
                                      Flag_Next_Key = 0; Flag_Last_Key = 0;
                                      lcd_clear(BLUE);  main_menu_display(MAIN_MENU_MAX); break;
                          default : break; 
                  } 
                  if (Flag_Assist != 0 )  //判断辅助标志位 确定键是否按下 按下则进行标志位赋值 再进入各个子菜单界面进行操作
                  { 
                          switch (Flag_MainMenu) //对主菜单选项标志位进行选择
                          { 
                                   case  0: 
                                              while(1)
                                              {   
                                                    ImageWatching();
                                                    IncrementalServoControl();
                                                    ftm_pwm_duty(FTM0, FTM_CH2, 10);
                                                    ftm_pwm_duty(FTM0, FTM_CH3,  0);
                                                    if(key_check(KEY_A) == KEY_DOWN)
                                                        {
                                                              ftm_pwm_duty(FTM0, FTM_CH2,0);
                                                              ftm_pwm_duty(FTM0, FTM_CH3,0);
                                                              break;
                                                        } 
                                              } break; //开始起跑啦

                                   case -3:  
                                              lcd_clear(BLUE);//清屏操作
                                              while(1)
                                              { 
                                                    ImageWatching(); //TFT进行图像显示
                                                    if(key_check(KEY_A) == KEY_DOWN) break;
                                              } break; 
                                   case  1:  
                                              lcd_clear(BLUE);//清屏操作
                                              while(1)
                                              { 
                                                    ImageWatching();//TFT进行图像显示
                                                    if(key_check(KEY_A) == KEY_DOWN) break;
                                              } break; 
                                   case -1: 
                                              Flag_Left_Key = 2;  //对标志位进行赋值操作，利于判断界面操作
                                              Flag_Right_Key = 2; 
                                              Flag_Last_Key = 2;  
                                              Flag_Next_Key = 2;  
                                              lcd_clear (BLUE); 
                                              servo_menu_display(SERVO_VAR_MAX); break;  //右键按下一次显示舵机调参界面 
                                   case -2: 
                                              Flag_Left_Key = 1; //对标志位进行赋值操作，利于判断界面操作 
                                              Flag_Right_Key = 1;
                                              Flag_Last_Key = 1; 
                                              Flag_Next_Key = 1; 
                                              lcd_clear (BLUE); 
                                               motor_menu_display(MOTOR_VAR_MAX); break;  //右键按下两次显示电机调参界面

                                   case 2: Flag_Left_Key = 1;  //对标志位进行赋值操作，利于判断界面操作
                                            Flag_Right_Key = 1; 
                                            Flag_Last_Key = 1; 
                                            Flag_Next_Key = 1; 
                                            lcd_clear (BLUE); 
                                            motor_menu_display(MOTOR_VAR_MAX); break;  //左键按下两次显示电机调参界面

                                   case 3: Flag_Left_Key = 2;  //对标志位进行赋值操作，利于判断界面操作
                                            Flag_Right_Key = 2; 
                                            Flag_Last_Key = 2;
                                            Flag_Next_Key = 2;
                                            lcd_clear (BLUE);
                                            servo_menu_display(SERVO_VAR_MAX); break; //左键按下三次显示舵机调参界面
                                   default :  break;
                           }
                           Flag_Assist = 0;
                     }
              }
      }
}

