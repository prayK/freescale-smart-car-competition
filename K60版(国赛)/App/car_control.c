#include "include.h"
#include "stdio.h"

uint8 back_flag=0;
uint8 run_flag=0;
uint16 center;
uint16 last_error,dir;
int16 dir_out, current_error;
Site_t site = {24, 0};



//////////////////////////////////////////菜单起跑/////////////////////////////////////////////////
void dir_control(void);

void run(void)
{      
         image_processing();
         dir_control(); 
         run_flag = 1;
} 



////////////////////////////////////////菜单控制舵机功能//////////////////////////////////////////////
/*舵机参数调节菜单*/
float dir_kp1 = 36.5;
float dir_kp2 = 20;
float dir_kd = 100;
float RightRingKP1 = 30;
float LeftRingKP1 = 36;
float OutRightRingKP1 = 34;
float OutLeftRingKP1 = 34;
float last_dir;
char dir_str[8][10]=  {
                          {"KP1 :  . "},
                          {"KP2 :    "},
                          {"KD  :    "},
                          {"ILRP:  . "},
                          {"IRRP:  . "},
                          {"OLRP:  . "},
                          {"ORRP:  . "},
                          {"CT  :    "},
                       };
float *change_string[8]; 
float dir_key_change[8]={0.2, 1, 1, 0.2, 0.2, 0.2, 0.2, 10};

void dir_change_fun() 
{ 
          static uint8 tab=0;
          while(back_flag==0) 
          { 
                    dir_str[0][5]=(int16)(dir_kp1*10)/100+'0';
                    dir_str[0][6]=(int16)(dir_kp1*10)%100/10+'0';
                    dir_str[0][8]=(int16)(dir_kp1*10)%100%10+'0';
 
                    dir_str[1][5]=(uint16)dir_kp2/100+'0';
                    dir_str[1][6]=(uint16)dir_kp2%100/10+'0';
                    dir_str[1][7]=(uint16)dir_kp2%100%10+'0';
 
                    dir_str[2][5]=(uint16)dir_kd/100+'0';
                    dir_str[2][6]=(uint16)dir_kd%100/10+'0';
                    dir_str[2][7]=(uint16)dir_kd%100%10+'0';
                    
                    dir_str[3][5]=(int16)(LeftRingKP1*10)/100+'0';
                    dir_str[3][6]=(int16)(LeftRingKP1*10)%100/10+'0';
                    dir_str[3][8]=(int16)(LeftRingKP1*10)%100%10+'0';
                    
                    dir_str[4][5]=(int16)(RightRingKP1*10)/100+'0';
                    dir_str[4][6]=(int16)(RightRingKP1*10)%100/10+'0';
                    dir_str[4][8]=(int16)(RightRingKP1*10)%100%10+'0';
                    
                    dir_str[5][5]=(int16)(OutLeftRingKP1*10)/100+'0';
                    dir_str[5][6]=(int16)(OutLeftRingKP1*10)%100/10+'0';
                    dir_str[5][8]=(int16)(OutLeftRingKP1*10)%100%10+'0';
                    
                    dir_str[6][5]=(int16)(OutRightRingKP1*10)/100+'0';
                    dir_str[6][6]=(int16)(OutRightRingKP1*10)%100/10+'0';
                    dir_str[6][8]=(int16)(OutRightRingKP1*10)%100%10+'0';
 
                    dir_str[7][5]=(uint16)dir_zhongzhi/1000+'0';
                    dir_str[7][6]=(uint16)dir_zhongzhi%1000/100+'0';
                    dir_str[7][7]=(uint16)dir_zhongzhi%100/10+'0';
                    dir_str[7][8]=(uint16)dir_zhongzhi%10+'0';
 
                    change_string[0] = &dir_kp1; 
                    change_string[1] = &dir_kp2; 
                    change_string[2] = &dir_kd; 
                    change_string[3] = &LeftRingKP1; 
                    change_string[4] = &RightRingKP1; 
                    change_string[5] = &OutLeftRingKP1; 
                    change_string[6] = &OutRightRingKP1; 
                    change_string[7] = &dir_zhongzhi;
                    
                    site.x=32; 
                    site.y=0; 
                    
                    back_flag = mymenu_deal(site, dir_str, change_string, tab, &tab, 8, dir_key_change);
          } 
} 






//////////////////////////////////////////菜单控制速度功能////////////////////////////////////////
/*电机参数调节菜单*/
char speed_str[8][10]={ 
                          {"SpdS:    "},
                          {"SpdM:    "},
                          {"SpdH:    "},
                          {"RSpd:    "},
                          {"ISpd:    "}, 
                          {"OSpd:    "}, 
                          {"ZASp:    "},
                          {"Slow:    "},
                       };

float *Schange_string[8];
float speed_key_change[8]={2, 2, 2, 2, 2, 2, 2, 2};

void speed_change_fun()
{
        static uint8 tab=0;
        while(back_flag==0)
        { 
                  speed_str[0][5]=(uint16)Speed_S/100%10+'0'; 
                  speed_str[0][6]=(uint16)Speed_S/10%10+'0'; 
                  speed_str[0][7]=(uint16)Speed_S%10+'0'; 
     
                  speed_str[1][5]=(uint16)Speed_M/100%10+'0'; 
                  speed_str[1][6]=(uint16)Speed_M/10%10+'0'; 
                  speed_str[1][7]=(uint16)Speed_M%10+'0'; 
                  
                  speed_str[2][5]=(uint16)Speed_H/100%10+'0'; 
                  speed_str[2][6]=(uint16)Speed_H/10%10+'0'; 
                  speed_str[2][7]=(uint16)Speed_H%10+'0'; 
                 
                  speed_str[3][5]=(uint16)RingSpeed/100%10+'0'; 
                  speed_str[3][6]=(uint16)RingSpeed/10%10+'0'; 
                  speed_str[3][7]=(uint16)RingSpeed%10+'0'; 
     
                  speed_str[4][5]=(uint16)InRingSpeed/100%10+'0'; 
                  speed_str[4][6]=(uint16)InRingSpeed/10%10+'0'; 
                  speed_str[4][7]=(uint16)InRingSpeed%10+'0'; 
                  
                  speed_str[5][5]=(uint16)OutRingSpeed/100%10+'0'; 
                  speed_str[5][6]=(uint16)OutRingSpeed/10%10+'0'; 
                  speed_str[5][7]=(uint16)OutRingSpeed%10+'0';
                  
                  speed_str[6][5]=(uint16)PassObstructSpeed/100%10+'0'; 
                  speed_str[6][6]=(uint16)PassObstructSpeed/10%10+'0'; 
                  speed_str[6][7]=(uint16)PassObstructSpeed%10+'0'; 
                  
                  speed_str[7][5]=(uint16)TheMostSlowSpeed/100%10+'0'; 
                  speed_str[7][6]=(uint16)TheMostSlowSpeed/10%10+'0'; 
                  speed_str[7][7]=(uint16)TheMostSlowSpeed%10+'0'; 
                 
                  Schange_string[0] = &Speed_S;
                  Schange_string[1] = &Speed_M;
                  Schange_string[2] = &Speed_H;
                  Schange_string[3] = &RingSpeed;
                  Schange_string[4] = &InRingSpeed;
                  Schange_string[5] = &OutRingSpeed;
                  Schange_string[6] = &PassObstructSpeed;
                  Schange_string[7] = &TheMostSlowSpeed;
 
                  site.x=32;
                  site.y=0;
 
                  back_flag=mymenu_deal(site, speed_str, Schange_string, tab, &tab, 8, speed_key_change);
         }
}



//////////////////////////////////////////菜单控制环岛参数功能////////////////////////////////////////
/*环岛参数调节菜单*/
char Ring_str[4][10]={ 
                          {"ILRV:    "},
                          {"IRRV:    "}, 
                          {"OLRV:    "}, 
                          {"ORRV:  . "},
                       };

float *Rchange_string[4]; 
float Ring_key_change[4] = {1, 1, 1, 1};

void ring_set_fun() 
{ 
            static uint8 tab=0;
            while(back_flag==0)
            { 
                    Ring_str[0][5]=(uint16)InLeftRingV/100%10+'0'; 
                    Ring_str[0][6]=(uint16)InLeftRingV/10%10+'0'; 
                    Ring_str[0][7]=(uint16)InLeftRingV%10+'0'; 
 
                    Ring_str[1][5]=(uint16)InRightRingV/100%10+'0'; 
                    Ring_str[1][6]=(uint16)InRightRingV/10%10+'0'; 
                    Ring_str[1][7]=(uint16)InRightRingV%10+'0'; 
 
                    Ring_str[2][5]=(uint16)OutLeftRingV/100%10+'0'; 
                    Ring_str[2][6]=(uint16)OutLeftRingV/10%10+'0'; 
                    Ring_str[2][7]=(uint16)OutLeftRingV%10+'0';
 
                    Ring_str[3][5]=(uint16)OutRightRingV/100%10+'0'; 
                    Ring_str[3][6]=(uint16)OutRightRingV/10%10+'0'; 
                    Ring_str[3][7]=(uint16)OutRightRingV%10+'0';
 
                    Rchange_string[0] = &InLeftRingV;
                    Rchange_string[1] = &InRightRingV; 
                    Rchange_string[2] = &OutLeftRingV; 
                    Rchange_string[3] = &OutRightRingV; 
                    
                    site.x=32;
                    site.y=0;
 
                    back_flag=mymenu_deal(site, Ring_str, Rchange_string, tab, &tab, 4, Ring_key_change);
            } 
} 




////////////////////////////////菜单控制部分参数显示功能////////////////////////////////////////
char qianzhan_str[4][10] =
                          {
                                {"END:    "},
                                {"TOP:    "},
                                {"YUV:    "},
                                {"Dst:    "},
                          };

float QZ_change[4]={1, 1, 1, 1}; 
float *QZchange_string[4];
float CNST_Value = 73;//现在55//默认阈值0x4f

void ParameterWatching_fun(void) 
{ 
            static uint8 tab=0;
            while(back_flag==0)
            {
                    qianzhan_str[0][4]=(int)QZ_End/10+'0';
                    qianzhan_str[0][5]=(int)QZ_End%10+'0';
 
                    qianzhan_str[1][4]=(int)QZ_Top/10+'0';
                    qianzhan_str[1][5]=(int)QZ_Top%10+'0';
 
                    qianzhan_str[2][4]=(int)CNST_Value/10+'0';
                    qianzhan_str[2][5]=(int)CNST_Value%10+'0';
 
                    qianzhan_str[3][4]=(int)Param/10+'0';
                    qianzhan_str[3][5]=(int)Param%10+'0';
 
                    QZchange_string[0] = &QZ_End; 
                    QZchange_string[1] = &QZ_Top; 
                    QZchange_string[2] = &CNST_Value; 
                    QZchange_string[3] = &Param; 
 
                    site.x = 32;
                    site.y = 32;
 
                    SCCB_WriteByte(OV7725_CNST,CNST_Value);
                    back_flag=mymenu_deal(site, qianzhan_str, QZchange_string, tab, &tab, 4, QZ_change);
            }

//         image_processing();//图像处理要运行 
//         
//         //显示中线偏差 
//         site.x=0;site.y=16; LCD_str(site,"R20:",BLACK,WHITE);  //第20行有黑点右边
//         site.x=0;site.y=32; LCD_num_BC(site,StreetCalWdith,4, BLACK,WHITE); 
// 
//         //显示中线偏差 
//         site.x=0;site.y=48; LCD_str(site,"R30:",BLACK,WHITE);  //第30行有黑点右边
//         site.x=0;site.y=64; LCD_num_BC(site,StreetCalWdith5,4, BLACK,WHITE); 
// 
//         //显示中线偏差 
//         site.x=0;site.y=80; LCD_str(site,"R35:",BLACK,WHITE); //第35行有黑点右边
//         site.x=0;site.y=96; LCD_num_BC(site,StreetCalWdith2,4, BLACK,WHITE); 
// 
//         //显示中线偏差 
//         site.x=32;site.y=16; LCD_str(site,"R50:",BLACK,WHITE);//第50行有黑点右边
//         site.x=32;site.y=32; LCD_num_BC(site,StreetCalWdith1,4, BLACK,WHITE); 
// 
//         //显示中线偏差 
//         site.x=32;site.y=48; LCD_str(site,"R53:",BLACK,WHITE); //第53行有黑点右边
//         site.x=32;site.y=64; LCD_num_BC(site,StreetCalWdith8,4, BLACK,WHITE); 
//         
//         site.x=64;site.y=16; LCD_str(site,"R12:",BLACK,WHITE);  //  
//         site.x=64;site.y=32; LCD_num_BC(site,StreetCalWdith12,4, BLACK,WHITE); 
//         
//         site.x=64;site.y=48; LCD_str(site,"R16:",BLACK,WHITE);  //  
//         site.x=64;site.y=64; LCD_num_BC(site,StreetCalWdith16,4, BLACK,WHITE); 
//         
//         site.x=64;site.y=80; LCD_str(site,"L50:",BLACK,WHITE);  //第20行有黑点左边 
//         site.x=64;site.y=96; LCD_num_BC(site,StreetCalLong50,4, BLACK,WHITE); 
         
         
//         //显示中线偏差 
//         site.x=64;site.y=16; LCD_num_BC(site,bian_line[77],4, BLACK,WHITE); //38
//         site.x=64;site.y=32; LCD_num_BC(site,bian_line[83],4, BLACK,WHITE); //41
//         site.x=64;site.y=48; LCD_num_BC(site,bian_line[89],4, BLACK,WHITE); //44
//         site.x=64;site.y=64; LCD_num_BC(site,bian_line[95],4, BLACK,WHITE); //47
            
//         image_processing();//图像处理要运行 
//         
//         site.x=0;site.y=16; LCD_str(site,"L20:",BLACK,WHITE);  //第20行有黑点左边 
//         site.x=0;site.y=32; LCD_num_BC(site,StreetCalWdith0,4, BLACK,WHITE); 
// 
//         site.x=0;site.y=48; LCD_str(site,"L30:",BLACK,WHITE); //第30行有黑点左边  
//         site.x=0;site.y=64; LCD_num_BC(site,StreetCalWdith7,4, BLACK,WHITE); 
// 
//         site.x=0;site.y=80; LCD_str(site,"L35:",BLACK,WHITE);//第35行有黑点左边
//         site.x=0;site.y=96; LCD_num_BC(site,StreetCalWdith4,4, BLACK,WHITE); 
// 
//         site.x=32;site.y=16; LCD_str(site,"L45:",BLACK,WHITE); //第45行有黑点左边  
//         site.x=32;site.y=32; LCD_num_BC(site,StreetCalWdith9,4, BLACK,WHITE); 
// 
//         site.x=32;site.y=48; LCD_str(site,"L50:",BLACK,WHITE); //第50行有黑点左边
//         site.x=32;site.y=64; LCD_num_BC(site,StreetCalWdith3,4, BLACK,WHITE); 
// 
//         site.x=32;site.y=80; LCD_str(site,"L53:",BLACK,WHITE); //第53行有黑点左边
//         site.x=32;site.y=96; LCD_num_BC(site,StreetCalWdith6,4, BLACK,WHITE); 
//         
//         site.x=64;site.y=16; LCD_str(site,"L16:",BLACK,WHITE); // 左16
//         site.x=64;site.y=32; LCD_num_BC(site,StreetCalWdithL16,4, BLACK,WHITE); 
// 
//         site.x=64;site.y=48; LCD_str(site,"L12:",BLACK,WHITE); // 左12
//         site.x=64;site.y=64; LCD_num_BC(site,StreetCalWdithL12,4, BLACK,WHITE); 
} 





///////////////////////////////////////////菜单图像显示/////////////////////////////////////////////
/*图像显示相关变量*/
Site_t site4 = {0, 0};
Size_t size={CAMERA_W,60};
Size_t imgsize={CAMERA_W,60};

void image_watch_fun(void)
{ 
         image_processing();
         dir_control();
         //图像显示
         LCD_Img_gray(site4,size,img[0]);
 
         //边线和中线显示
         LCD_points(center_line,60,BLACK);
         LCD_points(sit_R,60,RED);
         LCD_points(sit_L,60,RED);
 
         //红色显示前瞻
         site.x=0;site.y=18; LCD_cross(site,160, RED);
         site.x=0;site.y=50; LCD_cross(site,160, RED);
         
         //绿色显示环岛搜寻范围
         site.x=0;site.y=25; LCD_cross(site,160, GREEN);
         site.x=0;site.y=55; LCD_cross(site,160, GREEN);
 
         
         
         
         //显示期望速度
         site.x=0;site.y=64; LCD_str(site,"GSpd:",BLACK,WHITE);
         site.x=0;site.y=80; LCD_num_BC(site,GoalSpeed,4, BLACK,WHITE); 
         //显示直道长度 
         site.x=0;site.y=96; LCD_str(site,"Lng:",BLACK,WHITE);
         site.x=0;site.y=112; LCD_num_BC(site,StreetCalLong,4, BLACK,WHITE); 

         
     
         //显示assistr5
         site.x=38;site.y=64; LCD_str(site,"10:",BLACK,WHITE);
         site.x=38;site.y=80; LCD_num_BC(site,StreetCalWdith10,4, BLACK,WHITE);
         //显示assist5
         site.x=38;site.y=96; LCD_str(site,"6:",BLACK,WHITE);
         site.x=38;site.y=112; LCD_num_BC(site,StreetCalWdith6,4, BLACK,WHITE);  
 
         
         
         //显示环岛标志位状态 
         site.x=80;site.y=0; LCD_str(site,"RFlag:",BLACK,WHITE);
         site.x=80;site.y=16; LCD_num_BC(site,Ring_Find_Flag,4, BLACK,WHITE); 
         //显示左环岛标志位状态 
         site.x=80;site.y=32; LCD_str(site,"LRing:",BLACK,WHITE);
         site.x=80;site.y=48; LCD_num_BC(site,LeftRing_Find_Flag,4, BLACK,WHITE);
         //显示右环岛标志位状态 
         site.x=80;site.y=64; LCD_str(site,"RRing:",BLACK,WHITE);
         site.x=80;site.y=80; LCD_num_BC(site,RightRing_Find_Flag,4, BLACK,WHITE); 
         
         
         //显示障碍标志位状态 
         site.x=80;site.y=96; LCD_str(site,"A5:",BLACK,WHITE);
         site.x=80;site.y=112; LCD_num_BC(site,assist5,4, BLACK,WHITE); 
}




/*模糊控制系统函数 
实验代码，未测试*/ 
float Fuzzy(float e, float ec) //e,ec，表示输入的误差和误差变化率 
{ 
        float Kp_calcu;
        unsigned int num, pe, pec;//输入到模糊里的偏差和偏差变化量 
        
        const float eRule[7] = {-5,-3,-1,0,1,3,5}; //误差e的模糊论域 
        const float ecRule[7]= {-5,-3,-1,0,1,3,5}; //误差变化率ec的模糊论域 
        
        float eFuzzy [2]={0.0, 0.0}; //偏差e的隶属度 
        float ecFuzzy[2]={0.0, 0.0}; //偏差变化率ec的隶属度 
       
        const float kpRule[4]={0, 400, 800, 1200};  //Kp的模糊子集 
        float KpFuzzy[4]={0.0, 0.0, 0.0, 0.0};      //隶属于Kp的隶属程度
        const int KpRule[7][7] = {                  //Kp的模糊控制表 
                                      3,3,3,3,3,3,3, 
                                      3,3,3,3,3,3,3, 
                                      2,2,1,1,1,2,2, 
                                      3,2,1,0,1,2,3, 
                                      2,2,1,1,1,2,2, 
                                      3,3,3,3,3,3,3, 
                                      3,3,3,3,3,3,3 
                                   };
        
        /*****误差e隶属函数描述*****/
        if(e<eRule[0]) {eFuzzy[0] =1.0; pe = 0;} 
        else if(eRule[0]<=e && e<eRule[1]) 
        {eFuzzy[0] = (eRule[1]-e) / (eRule[1]-eRule[0]); pe = 0;} 
        else if(eRule[1]<=e && e<eRule[2]) 
        {eFuzzy[0] = (eRule[2]-e) / (eRule[2]-eRule[1]); pe = 1;} 
        else if(eRule[2]<=e && e<eRule[3]) 
        {eFuzzy[0] = (eRule[3]-e) / (eRule[3]-eRule[2]); pe = 2;}
        else if(eRule[3]<=e && e<eRule[4]) 
        {eFuzzy[0] = (eRule[4]-e) / (eRule[4]-eRule[3]); pe = 3;}
        else if(eRule[4]<=e && e<eRule[5])
        {eFuzzy[0] = (eRule[5]-e) / (eRule[5]-eRule[4]); pe = 4;}
        else if(eRule[5]<=e && e<eRule[6])
        {eFuzzy[0] = (eRule[6]-e) / (eRule[6]-eRule[5]); pe = 5;}
        else{eFuzzy[0] =0.0; pe =5;}
 
        eFuzzy[1] =1.0 - eFuzzy[0]; 
 
 
        /*****误差变化率EC隶属函数描述*****/ 
        if(ec<ecRule[0]){ecFuzzy[0] =1.0;pec = 0;}
        else if(ecRule[0]<=ec && ec<ecRule[1])
        {ecFuzzy[0] = (ecRule[1]-ec) / (ecRule[1]-ecRule[0]); pec = 0;}
        else if(ecRule[1]<=ec && ec<ecRule[2])
        {ecFuzzy[0] = (ecRule[2]-ec) / (ecRule[2]-ecRule[1]); pec = 1;}
        else if(ecRule[2]<=ec && ec<ecRule[3])
        {ecFuzzy[0] = (ecRule[3]-ec) / (ecRule[3]-ecRule[2]); pec = 2;}
        else if(ecRule[3]<=ec && ec<ecRule[4])
        {ecFuzzy[0] = (ecRule[4]-ec) / (ecRule[4]-ecRule[3]); pec = 3;}
        else if(ecRule[4]<=ec && ec<ecRule[5])
        {ecFuzzy[0] = (ecRule[5]-ec) / (ecRule[5]-ecRule[4]); pec = 4;}
        else if(ecRule[5]<=ec && ec<ecRule[6])
        {ecFuzzy[0] = (ecRule[6]-ec) / (ecRule[6]-ecRule[5]); pec = 5;}
        else{ecFuzzy[0] =0.0;pec = 5;}
 
        ecFuzzy[1] = 1.0 - ecFuzzy[0];
        
        /*********查询模糊规则表*********/
        num = KpRule[pe][pec];                  /*根据e,ec查询*/
        KpFuzzy[num] += eFuzzy[0] * ecFuzzy[0]; /*相乘？？(保证KpFuzzy数组中的四个数相加等于一，可以验证，用于加权平均法解模糊)*/
        num = KpRule[pe][pec+1]; 
        KpFuzzy[num] += eFuzzy[0] * ecFuzzy[1]; /*KpFuzzy数组中的数是占kpRule数组中的比重，他们是一一对应的关系*/
        num = KpRule[pe+1][pec]; 
        KpFuzzy[num] += eFuzzy[1] * ecFuzzy[0]; 
        num = KpRule[pe+1][pec+1]; 
        KpFuzzy[num] += eFuzzy[1] * ecFuzzy[1]; 
 
        /*********加权平均法解模糊*********/ 
        Kp_calcu = KpFuzzy[0]*kpRule[0] + KpFuzzy[1]*kpRule[1] + KpFuzzy[2]*kpRule[2]
                 + KpFuzzy[3]*kpRule[3];
        return(Kp_calcu);
} 

//舵机算法输出打角 
void dir_control(void) 
{ 
        center=(uint16)dir_zhongzhi;
        current_error = ave_center - 40;
 
        if (BM3 == 1) 
        { 
                  if(LeftRing_Find_Flag == 1 && Ring_Find_Flag == 0 && assist3)  //针对左环岛内部的舵机参数
                  {dir_kp1 = LeftRingKP1;} 
                  if(RightRing_Find_Flag == 1 && Ring_Find_Flag == 0 && assistr3)//针对右环岛内部的舵机参数
                  {dir_kp1 = RightRingKP1;} 
                  if (assistr4)//由于出右环岛切外,故加大Kp1的输出量
                  {dir_kp1 = OutRightRingKP1;} 
                  if (assist4) //由于出左环岛切外,故加大Kp1的输出量
                  {dir_kp1 = OutLeftRingKP1;} 
        } 
        if(BM3 == 0)//拨码三拨下，恒定最慢速度跑完,对应的pid常数
        { 
                   dir_kp1 = 25; 
                   dir_kp2 = 20; 
                   dir_kd = 30; 
        } 
        
//        if(BM3 == 1) 
//        { 
                   dir_out = (uint16)(  center 
                                      + (dir_kp2 * current_error * current_error / 1000 + dir_kp1) * current_error
                                      + (dir_kd * (current_error - last_error))
                                      ); 
//        } 

//        if(BM3 == 0) 
//        { 
//                  dir_out = (uint16)(  center 
//                                      + dir_kp1 * current_error
//                                      + dir_kd * (current_error - last_error))
//                                      ); 
//        } 
        
        if(dir_out < 0) dir_out = 0; 
        dir = dir_out; 
        if(dir > center + 1000) dir = (center + 1000); 
        if(dir < center - 1000) dir = (center - 1000); 
        last_error = current_error; 
        ftm_pwm_duty(FTM1, FTM_CH0, (uint16)dir); 
}
