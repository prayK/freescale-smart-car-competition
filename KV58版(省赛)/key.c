#include "include.h" 

gpio_pin_config_t key_config = {kGPIO_DigitalInput, 0,};//硬件下拉,内部上拉,低电平触发

extern uint8_t StopFlag;
extern uint8_t bmp_buff[4800]; 
extern Site_t  center_line[60]; 
extern int16_t CurrentError; 
extern uint8_t LeftRing_Find_Flag; 
extern uint8_t RightRing_Find_Flag;
extern uint8_t Ring_Find_Flag;
extern float ServoPDValue[2];
extern uint8_t q,w,e,r,t,y,u,p;
extern uint8_t rq,rw,re,rr,rt,ry,ru,rp;
extern Site_t center_line[60];  
extern int16_t CurrentError; 
extern uint8_t Ring_Find_Flag ; 
extern uint8_t LeftRing_Find_Flag;  
extern uint8_t RightRing_Find_Flag;  
extern float ServoPDValue[2]; 
extern uint16_t ServoOutPut; 
extern uint16_t DutyGo;  
extern uint8_t StartLineFind_Flag; //开始进行起跑线识别标志位
extern uint8_t bian_line[120]; 
extern uint8_t StreetCalLong; 
extern volatile uint16_t GoalSpeed; 
extern uint8_t StreetCalWdith;
extern uint8_t StreetCalWdith0; 
extern uint8_t StreetCalWdith1;
extern uint8_t StreetCalWdith5;
extern uint8_t StreetCalWdith2;
extern uint8_t StreetCalWdith3; 
extern uint8_t StreetCalWdith4; 
extern uint8_t StreetCalWdith6;
extern uint8_t left_lost, right_lost, h_left_lost, h_right_lost; 
extern float ServoPDValue[2];
extern int16_t LastError; 
extern uint8_t StreetCalWdith7;
extern uint8_t StreetCalWdith8;
extern uint8_t assistr3;
extern uint8_t assistr4;
extern uint8_t assist_ADD3,assist_ADDr1;
extern uint8_t assistr5;
extern uint8_t OutRingFind_Flag;
uint8_t h_left_lost_Dis ,h_right_lost_Dis ,right_lost_Dis ,left_lost_Dis ;
extern uint8_t MidPointHis[10];//////////////历史的中线 
extern uint8_t Y9_Value, StreetCalWdith9;
extern uint8_t HighSpeed;
extern uint8_t BOMAControlStopFlag; 
extern uint8_t RingSpeed;////环岛速度
extern float D_P1, D_P, D_D;
uint8_t StartDelay=0;
extern float RingP;
extern float SpeedP;


void LostFlagDisplay(void) 
{ 
       if (h_left_lost == 1)  h_left_lost_Dis = 1;
       else  h_left_lost_Dis = 0;
 
       if (h_right_lost == 1)  h_right_lost_Dis = 1;
       else  h_right_lost_Dis = 0;
 
       if (left_lost == 1)  left_lost_Dis = 1;
       else  left_lost_Dis = 0;
 
       if (right_lost == 1)  right_lost_Dis = 1;
       else  right_lost_Dis = 0;
}

/*独立按键状态标志位*/ 
int StatusS1Flag = 0, StatusS2Flag = 0, StatusS3Flag = 0, StatusS4Flag = 0, 
    StatusS5Flag = 0, StatusS6Flag = 0, StatusS7Flag = 0, StatusS8Flag = 0; 
 
/*拨码开关状态标志位*/ 
int  StatusB1Flag = 0, StatusB2Flag = 0, StatusB3Flag = 0, StatusB4Flag = 0, 
     StatusB5Flag = 0, StatusB6Flag = 0, StatusB7Flag = 0, StatusB8Flag = 0; 
 
/*初始化独立按键(改参数)及拨码开关(调模式)*/ 
void KEY_Init(void) 
{ 
     /*独立按键初始化*/
     GPIO_PinInit(GPIOA, 24, &key_config); GPIO_PinInit(GPIOA, 25, &key_config);
     GPIO_PinInit(GPIOA, 27, &key_config); GPIO_PinInit(GPIOA, 29, &key_config);
     GPIO_PinInit(GPIOA, 28, &key_config); GPIO_PinInit(GPIOB,  5, &key_config);
     GPIO_PinInit(GPIOB,  5, &key_config); GPIO_PinInit(GPIOB,  7, &key_config);
     
     /*拨码初始化*/
     GPIO_PinInit(GPIOE,  6, &key_config); GPIO_PinInit(GPIOE,  7, &key_config);
     GPIO_PinInit(GPIOE,  8, &key_config); GPIO_PinInit(GPIOE,  9, &key_config);
     GPIO_PinInit(GPIOE, 10, &key_config); GPIO_PinInit(GPIOE, 12, &key_config);
     GPIO_PinInit(GPIOE, 16, &key_config); GPIO_PinInit(GPIOE, 17, &key_config);
}
 
/*独立按键(改参数)及拨码开关(调模式)信息读取*/ 
void Key_Scan(void) 
{ 
        /**************独立按键*****************/ 
        if(statusS1 == 0) ///按键控制延时发车
        { 
              DelayMs(5); 
              if(statusS1 == 0) StatusS1Flag = 1; 
        } else StatusS1Flag = 0; 
 
//        if(statusS2 == 0) //速度P加
//        { 
//              DelayMs(5); 
//              if(statusS2 == 0) SpeedP += 0.1; 
//        } //else StatusS2Flag = 0; 
// 
//        if(statusS3 == 0) //速度P减
//        {   
//              DelayMs(5); 
//              if(statusS3 == 0) SpeedP -= 0.1; 
//        } //else StatusS3Flag = 0; 
 
        if(statusS4 == 0) //舵机P加
        { 
              DelayMs(70); 
              if(statusS4 == 0) D_P += 0.1; 
        } //else StatusS4Flag = 0; 
        
        if(statusS5 == 0) //舵机P减
        { 
              DelayMs(70); 
              if(statusS5 == 0) D_P -= 0.1;
        } //else StatusS5Flag = 0; 
        
        if(statusS6 == 0) 
        { 
              DelayMs(70); 
              if(statusS6 == 0) SpeedP += 0.1; 
        } else StatusS6Flag = 0; 
 
//        if(statusS7 == 0) //舵机D减
//        { 
//              DelayMs(70); 
//              if(statusS7 == 0) D_D -= 1; 
//        } //else StatusS7Flag = 0; 
        
        if(statusS8 == 0) 
        { 
              DelayMs(70); 
              if(statusS8 == 0) SpeedP -= 0.1; 
        } //else StatusS8Flag = 0; 
 
        /*****************拨码开关**************/
        if(statusB1 == 0) StatusB1Flag = 1;
        else StatusB1Flag = 0;

        if(statusB2 == 0) StatusB2Flag = 1;
        else StatusB2Flag = 0; 
        
         if(statusB3 == 0) StatusB3Flag = 1;
        else StatusB3Flag = 0;
 
         if(statusB4 == 0) StatusB4Flag = 1;
        else StatusB4Flag = 0;
 
         if(statusB5 == 0) StatusB5Flag = 1;
        else StatusB5Flag = 0;
 
         if(statusB6 == 0) StatusB6Flag = 1;
        else StatusB6Flag = 0;
 
         if(statusB7 == 0) StatusB7Flag = 1;
        else StatusB7Flag = 0;
 
         if(statusB8 == 0) StatusB8Flag = 1;
        else StatusB8Flag = 0;
} 

void MainShow(void) 
{ 
        Draw_BMP(0,0,79,7,bmp_buff);              //OLED图像显示 
 
        oled_display_6x8str(92,0,"RF:");          //OLED显示环岛标志位状态 
        if(Ring_Find_Flag == 1) oled_display_6x8str(108, 0, "YS"); 
        if(Ring_Find_Flag == 0) oled_display_6x8str(108, 0, "NO"); 
 
        oled_display_6x8str(92,1,"LR:");          //OLED显示左环岛标志位状态 
        if(LeftRing_Find_Flag == 1) oled_display_6x8str(108, 1, "YS"); 
        if(LeftRing_Find_Flag == 0) oled_display_6x8str(108, 1, "NO");
 
        oled_display_6x8str(92,2,"RR:");          //OLED显示右环岛标志位状态 
        if(RightRing_Find_Flag == 1) oled_display_6x8str(108, 2, "YS"); 
        if(RightRing_Find_Flag == 0) oled_display_6x8str(108, 2, "NO"); 
        
        oled_print_short(92, 3, CurrentError);   //当前偏差
        oled_print_short(92, 4, HighSpeed);      //期望速度
        oled_print_short(92, 5, RingSpeed);      //环岛速度
        oled_print_short(92, 6, D_P*10);         //舵机P
        oled_print_short(92, 7, D_D);            //舵机D
} 
 
void SecondShow(void) 
{ 
        oled_display_6x8str(0,0,"HL:");            //OLED显示左环岛标志位状态 
        if(h_left_lost == 1) oled_display_6x8str(20, 0, "YS"); 
        if(h_left_lost == 0) oled_display_6x8str(20, 0, "NO"); 
 
        oled_display_6x8str(0,1,"HR:");            //OLED显示右环岛标志位状态 
        if(h_right_lost == 1) oled_display_6x8str(20, 1, "YS"); 
        if(h_right_lost == 0) oled_display_6x8str(20, 1, "NO"); 
        
        oled_display_6x8str(0,2,"L:");            //OLED显示右环岛标志位状态 
        if(left_lost == 1) oled_display_6x8str(20, 2, "YS"); 
        if(left_lost == 0) oled_display_6x8str(20, 2, "NO"); 
        
        oled_display_6x8str(0,3,"R:");            //OLED显示右环岛标志位状态 
        if(right_lost == 1) oled_display_6x8str(20, 3, "YS"); 
        if(right_lost == 0) oled_display_6x8str(20, 3, "NO"); 
        
//        oled_display_6x8str(40,2,"ZD:");    oled_print_short(80, 0, StreetCalLong);    //直道长度
        oled_display_6x8str(40,3,"R35:");   oled_print_short(80, 1, StreetCalWdith3);  //第50行有黑点 
        oled_display_6x8str(40,4,"L35:");   oled_print_short(80, 2, StreetCalWdith6);  //第35行有黑点左边 
        oled_display_6x8str(40,5,"L30:");   oled_print_short(80, 3, StreetCalWdith3);  //第30行有黑点右边
        oled_display_6x8str(40,6,"L50:");   oled_print_short(80, 4, StreetCalWdith4);  //第35行有黑点左边 
        oled_display_6x8str(40,7,"L53:");   oled_print_short(80, 5, StreetCalWdith5);  //第53行有黑点左边 
        
//        oled_display_6x8str(70,0,"32:");  oled_print_short(90,0,center_line[32].x); 
//        oled_display_6x8str(70,1,"35:");  oled_print_short(90,1,center_line[35].x); 
//        oled_display_6x8str(70,2,"38:");  oled_print_short(90,2,center_line[38].x); 
//        oled_display_6x8str(70,3,"41:");  oled_print_short(90,3,center_line[41].x); 
//        oled_display_6x8str(70,4,"44:");  oled_print_short(90,4,center_line[44].x); 
//        oled_display_6x8str(70,5,"47:");  oled_print_short(90,5,center_line[47].x); 
//        oled_display_6x8str(70,6,"50:");  oled_print_short(90,6,center_line[50].x); 
//        oled_display_6x8str(70,7,"53:");  oled_print_short(90,7,center_line[53].x); 

} 

void ThirdShow(void) 
{
        oled_print_short(0,0,bian_line[59]); 
        oled_print_short(0,1,bian_line[61]); 
        oled_print_short(0,2,bian_line[63]); 
        oled_print_short(0,3,bian_line[65]); 
        oled_print_short(0,4,bian_line[67]); 
        oled_print_short(0,5,bian_line[69]); 
        oled_print_short(0,6,bian_line[71]); 
        oled_print_short(0,7,bian_line[73]); 
        
        oled_print_short(50,0,bian_line[75]); 
        oled_print_short(50,1,bian_line[77]); 
        oled_print_short(50,2,bian_line[79]); 
        oled_print_short(50,3,bian_line[81]); 
        oled_print_short(50,4,bian_line[83]); 
        oled_print_short(50,5,bian_line[85]); 
        oled_print_short(50,6,bian_line[87]); 
        oled_print_short(50,7,bian_line[89]); 
 
        oled_print_short(90,0,bian_line[91]); 
        oled_print_short(90,1,bian_line[93]); 
        oled_print_short(90,2,bian_line[95]); 
        oled_print_short(90,3,bian_line[97]); 
        oled_print_short(90,4,bian_line[99]); 
        oled_print_short(90,5,bian_line[101]); 
        oled_print_short(90,6,bian_line[103]); 
        oled_print_short(90,7,bian_line[105]); 
        
//        oled_print_short(90,0,bian_line[57]); 
//        oled_print_short(90,1,bian_line[55]); 
//        oled_print_short(90,2,bian_line[53]); 
//        oled_print_short(90,3,bian_line[51]); 
//        oled_print_short(90,4,bian_line[49]); 
//        oled_print_short(90,5,bian_line[47]); 
//        oled_print_short(90,6,bian_line[45]); 
//        oled_print_short(90,7,bian_line[43]); 
}

void ForthShow(void) 
{
        oled_print_short(0,0,bian_line[118]); 
        oled_print_short(0,1,bian_line[116]); 
        oled_print_short(0,2,bian_line[114]); 
        oled_print_short(0,3,bian_line[112]); 
        oled_print_short(0,4,bian_line[110]); 
        oled_print_short(0,5,bian_line[108]); 
        oled_print_short(0,6,bian_line[106]); 
        oled_print_short(0,7,bian_line[104]); 
 
        oled_print_short(90,0,bian_line[102]); 
        oled_print_short(90,1,bian_line[100]); 
        oled_print_short(90,2,bian_line[98]); 
        oled_print_short(90,3,bian_line[96]); 
        oled_print_short(90,4,bian_line[94]); 
        oled_print_short(90,5,bian_line[92]); 
        oled_print_short(90,6,bian_line[90]); 
        oled_print_short(90,7,bian_line[88]); 
}

void FifthShow(void) 
{
           oled_print_short(90,0,StreetCalLong);     //OLED显示第18行值 
           oled_print_short(90,1,center_line[58].x); //OLED显示第28行值 
           oled_print_short(90,2,center_line[57].x); //OLED显示第38行值 
           oled_print_short(90,3,center_line[56].x); //OLED显示第48行值 
           oled_print_short(90,4,center_line[55].x); //OLED显示第58行值 
           oled_print_short(90,5,center_line[54].x); //OLED显示第38行值 
           oled_print_short(90,6,center_line[53].x); //OLED显示第48行值 
           oled_print_short(90,7,center_line[52].x); //OLED显示第58行值 
           
           oled_print_short(50,0,center_line[44].x); //OLED显示第18行值 
           oled_print_short(50,1,center_line[43].x); //OLED显示第28行值 
           oled_print_short(50,2,center_line[42].x); //OLED显示第38行值 
           oled_print_short(50,3,center_line[41].x); //OLED显示第48行值 
           oled_print_short(50,4,center_line[40].x); //OLED显示第58行值 
           oled_print_short(50,5,center_line[39].x); //OLED显示第38行值 
           oled_print_short(50,6,center_line[38].x); //OLED显示第48行值 
           oled_print_short(50,7,center_line[37].x); //OLED显示第58行值 
           
           oled_print_short(0,0,center_line[36].x); //OLED显示第18行值 
           oled_print_short(0,1,center_line[35].x); //OLED显示第28行值 
           oled_print_short(0,2,center_line[34].x); //OLED显示第38行值 
           oled_print_short(0,3,center_line[33].x); //OLED显示第48行值 
           oled_print_short(0,4,center_line[32].x); //OLED显示第58行值 
           oled_print_short(0,5,center_line[31].x); //OLED显示第38行值 
           oled_print_short(0,6,center_line[30].x); //OLED显示第48行值 
           oled_print_short(0,7,center_line[29].x); //OLED显示第58行值 
}

/*独立按键用于调参*/ 
void Switch_KeyEvenManage(void) 
{ 
          MainShow();//显示主界面
          if (StatusS1Flag == 1 && StartDelay == 0) 
          { 
                   DelayMs(800);///延时1秒发车////实际是2.5秒左右
                   StartDelay=1;
          } 
} 

/*拨码用于控制模式*/
void BOMA_KeyEvenManage(void) 
{ 
        if (StatusB1Flag == 1 && StatusB2Flag == 0 && StatusB3Flag == 0)//拨码1向下，2,3向上，高速模式 
        {HighSpeed = 71;} 
        if (StatusB1Flag == 0 && StatusB2Flag == 1 && StatusB3Flag == 0)//拨码2向下，1,3向上，中速模式 
        {HighSpeed = 69;} 
        if (StatusB1Flag == 0 && StatusB2Flag == 0 && StatusB3Flag == 1)//拨码3向下，1,2向上，低速模式 
        {HighSpeed = 67;} 
        if (StatusB4Flag == 1 && StatusB5Flag == 0 && StatusB6Flag == 0)//拨码4向下，5,6向上，环岛速度43 
        {RingSpeed = 45;} 
        if (StatusB4Flag == 0 && StatusB5Flag == 1 && StatusB6Flag == 0)//拨码5向下，5,6向上，环岛速度40 
        {RingSpeed = 40;} 
        if (StatusB4Flag == 0 && StatusB5Flag == 0 && StatusB6Flag == 1)//拨码6向下，4,5向上，环岛速度35 
        {RingSpeed = 35;} 
//        if (StatusB7Flag == 1)     //拨码7向下关闭检测停车 
//        {BOMAControlStopFlag = 0;} 
} 