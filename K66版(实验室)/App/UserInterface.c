#include "common.h"
#include "include.h"
#include "UserInterface.h"

/***********************************���˵����***********************************/
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

//���˵���ʾ
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
        //lcd_str(siteVDis, "", BLUE, RED); //�ȴ���ѹ���ݴ���
        main_menu_tab++; 
    }
    while(i--);
} 

//���˵���ѡ��
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

/***********************************���PID���**********************************/
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

//�������ҳ����ʾ
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

//�Ա�������ѡ��
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

//�Ա������мӼ�����
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

/***********************************���PD���***********************************/
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

//�������ҳ����ʾ
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

//�Ա�������ѡ��
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

//�Ա������мӼ�����
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

/*********�����¼�����*********/
void Main_Menu_Deal()
{ 
     uint8 Flag_Assist = 0;
     KEY_MSG_t keymsg_MainMenu;
     while (get_key_msg(& keymsg_MainMenu)) 
     { 
            if (keymsg_MainMenu.status == KEY_DOWN)//��ȡÿ������״̬
            { 
                  switch (keymsg_MainMenu.key) //��ȡ���ĸ���������
                  { 
                          case KEY_L:  //��� ����ѡ���ѡ�� ��һ�� PTD11
                                switch (Flag_Left_Key) //���ݱ�־λ�ж����ĸ����水�� 
                                {
                                       case 0: Flag_MainMenu++; if (Flag_MainMenu > 3); Flag_MainMenu = 0; 
                                               main_menu_select(MAIN_MENU_PREV);           //�����水��
                                       case 1: motor_var_select(MOTOR_VAR_PREV); break; //���PID���ڽ��水��
                                       case 2: servo_var_select(SERVO_VAR_PREV); break; //���PD���ڽ��水�� 
                                       default : break; 
                                } break; 

                          case KEY_R: //�Ҽ� ����ѡ���ѡ�� ��һ�� PTD12
                                switch (Flag_Right_Key)//���ݱ�־λ�ж����ĸ����水�� 
                                {  
                                       case 0: Flag_MainMenu--; if (Flag_MainMenu < -3) Flag_MainMenu = 0; 
                                               main_menu_select(MAIN_MENU_NEXT); break;//�����水��
                                       case 1: motor_var_select(MOTOR_VAR_NEXT); break;//���PID���ڽ��水��
                                       case 2: servo_var_select(SERVO_VAR_NEXT); break;//���PD���ڽ��水�� 
                                       default : break; 
                                 } break;

                          case KEY_U: //�������ݵ��� �� PTD10
                                switch (Flag_Last_Key)//���ݱ�־λ�ж����ĸ����水�� 
                                { 
                                        case 1: motor_var_value(MOTOR_VAR_ADD); break;//���PD���ڽ��水�� 
                                        case 2: servo_var_value(SERVO_VAR_ADD); break;//���PD���ڽ��水�� 
                                        default : break; 
                                 } break; 

                          case KEY_D: //�������ݵ� �� PTD14
                                switch (Flag_Next_Key)//���ݱ�־λ�ж����ĸ����水�� 
                                { 
                                        case 1: motor_var_value(MOTOR_VAR_SUB); break;//���PD���ڽ��水�� 
                                        case 2: servo_var_value(SERVO_VAR_SUB); break;//���PD���ڽ��水�� 
                                        default : break; 
                                 } break; 

                          case KEY_B: Flag_Assist++; break; //�����жϱ�־λ ȷ���� PTD13

                          case KEY_A: Flag_Left_Key = 0; Flag_Right_Key = 0; //�������˵����� ��0������־λ ȡ���� PTD7
                                      Flag_Next_Key = 0; Flag_Last_Key = 0;
                                      lcd_clear(BLUE);  main_menu_display(MAIN_MENU_MAX); break;
                          default : break; 
                  } 
                  if (Flag_Assist != 0 )  //�жϸ�����־λ ȷ�����Ƿ��� ��������б�־λ��ֵ �ٽ�������Ӳ˵�������в���
                  { 
                          switch (Flag_MainMenu) //�����˵�ѡ���־λ����ѡ��
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
                                              } break; //��ʼ������

                                   case -3:  
                                              lcd_clear(BLUE);//��������
                                              while(1)
                                              { 
                                                    ImageWatching(); //TFT����ͼ����ʾ
                                                    if(key_check(KEY_A) == KEY_DOWN) break;
                                              } break; 
                                   case  1:  
                                              lcd_clear(BLUE);//��������
                                              while(1)
                                              { 
                                                    ImageWatching();//TFT����ͼ����ʾ
                                                    if(key_check(KEY_A) == KEY_DOWN) break;
                                              } break; 
                                   case -1: 
                                              Flag_Left_Key = 2;  //�Ա�־λ���и�ֵ�����������жϽ������
                                              Flag_Right_Key = 2; 
                                              Flag_Last_Key = 2;  
                                              Flag_Next_Key = 2;  
                                              lcd_clear (BLUE); 
                                              servo_menu_display(SERVO_VAR_MAX); break;  //�Ҽ�����һ����ʾ������ν��� 
                                   case -2: 
                                              Flag_Left_Key = 1; //�Ա�־λ���и�ֵ�����������жϽ������ 
                                              Flag_Right_Key = 1;
                                              Flag_Last_Key = 1; 
                                              Flag_Next_Key = 1; 
                                              lcd_clear (BLUE); 
                                               motor_menu_display(MOTOR_VAR_MAX); break;  //�Ҽ�����������ʾ������ν���

                                   case 2: Flag_Left_Key = 1;  //�Ա�־λ���и�ֵ�����������жϽ������
                                            Flag_Right_Key = 1; 
                                            Flag_Last_Key = 1; 
                                            Flag_Next_Key = 1; 
                                            lcd_clear (BLUE); 
                                            motor_menu_display(MOTOR_VAR_MAX); break;  //�������������ʾ������ν���

                                   case 3: Flag_Left_Key = 2;  //�Ա�־λ���и�ֵ�����������жϽ������
                                            Flag_Right_Key = 2; 
                                            Flag_Last_Key = 2;
                                            Flag_Next_Key = 2;
                                            lcd_clear (BLUE);
                                            servo_menu_display(SERVO_VAR_MAX); break; //�������������ʾ������ν���
                                   default :  break;
                           }
                           Flag_Assist = 0;
                     }
              }
      }
}

