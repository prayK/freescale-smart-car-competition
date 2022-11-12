#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#define VAR_VALUE_HOLE_OFFSET   10

/*********���˵����********/
//���˵���ʾ
typedef struct
{ 
      char   *str;
      Site_t  site;
} main_menu_info_t;

//���˵��������
typedef enum
{
      MAIN_MENU1,
      MAIN_MENU2,
      MAIN_MENU3,
      MAIN_MENU4,
      MAIN_MENU_MAX,
} main_menu_tab_e;

//���˵���ѡ��
typedef enum
{
      MAIN_MENU_NEXT,
      MAIN_MENU_PREV,
      MAIN_MENU_EVENT_MAX, 
} main_menu_var_e;

/**********������**********/
//�����������ҳ��ʾ
typedef struct
{ 
      char   *str; 
      Site_t  msite;
      uint8   val;
      Site_t  site;
} motor_menu_info_t;

//���PID��������
typedef enum 
{
      MOTOR_VAR1,
      MOTOR_VAR2,
      MOTOR_VAR3,
      MOTOR_VAR_MAX,
} motor_menu_tab_e;

//�����������ѡ��
typedef enum    
{
      MOTOR_VAR_NEXT,
      MOTOR_VAR_PREV,
      MOTOR_VAR_ADD,
      MOTOR_VAR_SUB,
      MOTOR_VAR_ADD_HOLD,
      MOTOR_VAR_SUB_HOLD,
      MOTOR_VAR_EVENT_MAX,
} motor_menu_var_e;

/**********������**********/
//�����������ҳ��ʾ
typedef struct
{ 
      char   *str; 
      Site_t  msite;
      uint8   val;
      Site_t  site;
} servo_menu_info_t;

//���PD��������
typedef enum
{
      SERVO_VAR1,
      SERVO_VAR2,
      SERVO_VAR_MAX,
} servo_menu_tab_e;

//���PD��������ѡ��
typedef enum    
{
      SERVO_VAR_NEXT,
      SERVO_VAR_PREV,
      SERVO_VAR_ADD,
      SERVO_VAR_SUB,
      SERVO_VAR_ADD_HOLD,
      SERVO_VAR_SUB_HOLD,
      SERVO_VAR_EVENT_MAX,
} servo_menu_var_e;

extern void Main_Menu_Deal(void);
extern void main_menu_display(uint8 main_menu_tab);
  
#endif 

