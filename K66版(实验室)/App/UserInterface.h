#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#define VAR_VALUE_HOLE_OFFSET   10

/*********主菜单相关********/
//主菜单显示
typedef struct
{ 
      char   *str;
      Site_t  site;
} main_menu_info_t;

//主菜单五个变量
typedef enum
{
      MAIN_MENU1,
      MAIN_MENU2,
      MAIN_MENU3,
      MAIN_MENU4,
      MAIN_MENU_MAX,
} main_menu_tab_e;

//主菜单项选择
typedef enum
{
      MAIN_MENU_NEXT,
      MAIN_MENU_PREV,
      MAIN_MENU_EVENT_MAX, 
} main_menu_var_e;

/**********电机相关**********/
//电机参数详情页显示
typedef struct
{ 
      char   *str; 
      Site_t  msite;
      uint8   val;
      Site_t  site;
} motor_menu_info_t;

//电机PID三个参数
typedef enum 
{
      MOTOR_VAR1,
      MOTOR_VAR2,
      MOTOR_VAR3,
      MOTOR_VAR_MAX,
} motor_menu_tab_e;

//电机三个参数选择
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

/**********舵机相关**********/
//舵机参数详情页显示
typedef struct
{ 
      char   *str; 
      Site_t  msite;
      uint8   val;
      Site_t  site;
} servo_menu_info_t;

//舵机PD两个参数
typedef enum
{
      SERVO_VAR1,
      SERVO_VAR2,
      SERVO_VAR_MAX,
} servo_menu_tab_e;

//舵机PD两个参数选择
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

