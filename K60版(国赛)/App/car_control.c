#include "include.h"
#include "stdio.h"

uint8 back_flag=0;
uint8 run_flag=0;
uint16 center;
uint16 last_error,dir;
int16 dir_out, current_error;
Site_t site = {24, 0};



//////////////////////////////////////////�˵�����/////////////////////////////////////////////////
void dir_control(void);

void run(void)
{      
         image_processing();
         dir_control(); 
         run_flag = 1;
} 



////////////////////////////////////////�˵����ƶ������//////////////////////////////////////////////
/*����������ڲ˵�*/
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






//////////////////////////////////////////�˵������ٶȹ���////////////////////////////////////////
/*����������ڲ˵�*/
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



//////////////////////////////////////////�˵����ƻ�����������////////////////////////////////////////
/*�����������ڲ˵�*/
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




////////////////////////////////�˵����Ʋ��ֲ�����ʾ����////////////////////////////////////////
char qianzhan_str[4][10] =
                          {
                                {"END:    "},
                                {"TOP:    "},
                                {"YUV:    "},
                                {"Dst:    "},
                          };

float QZ_change[4]={1, 1, 1, 1}; 
float *QZchange_string[4];
float CNST_Value = 73;//����55//Ĭ����ֵ0x4f

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

//         image_processing();//ͼ����Ҫ���� 
//         
//         //��ʾ����ƫ�� 
//         site.x=0;site.y=16; LCD_str(site,"R20:",BLACK,WHITE);  //��20���кڵ��ұ�
//         site.x=0;site.y=32; LCD_num_BC(site,StreetCalWdith,4, BLACK,WHITE); 
// 
//         //��ʾ����ƫ�� 
//         site.x=0;site.y=48; LCD_str(site,"R30:",BLACK,WHITE);  //��30���кڵ��ұ�
//         site.x=0;site.y=64; LCD_num_BC(site,StreetCalWdith5,4, BLACK,WHITE); 
// 
//         //��ʾ����ƫ�� 
//         site.x=0;site.y=80; LCD_str(site,"R35:",BLACK,WHITE); //��35���кڵ��ұ�
//         site.x=0;site.y=96; LCD_num_BC(site,StreetCalWdith2,4, BLACK,WHITE); 
// 
//         //��ʾ����ƫ�� 
//         site.x=32;site.y=16; LCD_str(site,"R50:",BLACK,WHITE);//��50���кڵ��ұ�
//         site.x=32;site.y=32; LCD_num_BC(site,StreetCalWdith1,4, BLACK,WHITE); 
// 
//         //��ʾ����ƫ�� 
//         site.x=32;site.y=48; LCD_str(site,"R53:",BLACK,WHITE); //��53���кڵ��ұ�
//         site.x=32;site.y=64; LCD_num_BC(site,StreetCalWdith8,4, BLACK,WHITE); 
//         
//         site.x=64;site.y=16; LCD_str(site,"R12:",BLACK,WHITE);  //  
//         site.x=64;site.y=32; LCD_num_BC(site,StreetCalWdith12,4, BLACK,WHITE); 
//         
//         site.x=64;site.y=48; LCD_str(site,"R16:",BLACK,WHITE);  //  
//         site.x=64;site.y=64; LCD_num_BC(site,StreetCalWdith16,4, BLACK,WHITE); 
//         
//         site.x=64;site.y=80; LCD_str(site,"L50:",BLACK,WHITE);  //��20���кڵ���� 
//         site.x=64;site.y=96; LCD_num_BC(site,StreetCalLong50,4, BLACK,WHITE); 
         
         
//         //��ʾ����ƫ�� 
//         site.x=64;site.y=16; LCD_num_BC(site,bian_line[77],4, BLACK,WHITE); //38
//         site.x=64;site.y=32; LCD_num_BC(site,bian_line[83],4, BLACK,WHITE); //41
//         site.x=64;site.y=48; LCD_num_BC(site,bian_line[89],4, BLACK,WHITE); //44
//         site.x=64;site.y=64; LCD_num_BC(site,bian_line[95],4, BLACK,WHITE); //47
            
//         image_processing();//ͼ����Ҫ���� 
//         
//         site.x=0;site.y=16; LCD_str(site,"L20:",BLACK,WHITE);  //��20���кڵ���� 
//         site.x=0;site.y=32; LCD_num_BC(site,StreetCalWdith0,4, BLACK,WHITE); 
// 
//         site.x=0;site.y=48; LCD_str(site,"L30:",BLACK,WHITE); //��30���кڵ����  
//         site.x=0;site.y=64; LCD_num_BC(site,StreetCalWdith7,4, BLACK,WHITE); 
// 
//         site.x=0;site.y=80; LCD_str(site,"L35:",BLACK,WHITE);//��35���кڵ����
//         site.x=0;site.y=96; LCD_num_BC(site,StreetCalWdith4,4, BLACK,WHITE); 
// 
//         site.x=32;site.y=16; LCD_str(site,"L45:",BLACK,WHITE); //��45���кڵ����  
//         site.x=32;site.y=32; LCD_num_BC(site,StreetCalWdith9,4, BLACK,WHITE); 
// 
//         site.x=32;site.y=48; LCD_str(site,"L50:",BLACK,WHITE); //��50���кڵ����
//         site.x=32;site.y=64; LCD_num_BC(site,StreetCalWdith3,4, BLACK,WHITE); 
// 
//         site.x=32;site.y=80; LCD_str(site,"L53:",BLACK,WHITE); //��53���кڵ����
//         site.x=32;site.y=96; LCD_num_BC(site,StreetCalWdith6,4, BLACK,WHITE); 
//         
//         site.x=64;site.y=16; LCD_str(site,"L16:",BLACK,WHITE); // ��16
//         site.x=64;site.y=32; LCD_num_BC(site,StreetCalWdithL16,4, BLACK,WHITE); 
// 
//         site.x=64;site.y=48; LCD_str(site,"L12:",BLACK,WHITE); // ��12
//         site.x=64;site.y=64; LCD_num_BC(site,StreetCalWdithL12,4, BLACK,WHITE); 
} 





///////////////////////////////////////////�˵�ͼ����ʾ/////////////////////////////////////////////
/*ͼ����ʾ��ر���*/
Site_t site4 = {0, 0};
Size_t size={CAMERA_W,60};
Size_t imgsize={CAMERA_W,60};

void image_watch_fun(void)
{ 
         image_processing();
         dir_control();
         //ͼ����ʾ
         LCD_Img_gray(site4,size,img[0]);
 
         //���ߺ�������ʾ
         LCD_points(center_line,60,BLACK);
         LCD_points(sit_R,60,RED);
         LCD_points(sit_L,60,RED);
 
         //��ɫ��ʾǰհ
         site.x=0;site.y=18; LCD_cross(site,160, RED);
         site.x=0;site.y=50; LCD_cross(site,160, RED);
         
         //��ɫ��ʾ������Ѱ��Χ
         site.x=0;site.y=25; LCD_cross(site,160, GREEN);
         site.x=0;site.y=55; LCD_cross(site,160, GREEN);
 
         
         
         
         //��ʾ�����ٶ�
         site.x=0;site.y=64; LCD_str(site,"GSpd:",BLACK,WHITE);
         site.x=0;site.y=80; LCD_num_BC(site,GoalSpeed,4, BLACK,WHITE); 
         //��ʾֱ������ 
         site.x=0;site.y=96; LCD_str(site,"Lng:",BLACK,WHITE);
         site.x=0;site.y=112; LCD_num_BC(site,StreetCalLong,4, BLACK,WHITE); 

         
     
         //��ʾassistr5
         site.x=38;site.y=64; LCD_str(site,"10:",BLACK,WHITE);
         site.x=38;site.y=80; LCD_num_BC(site,StreetCalWdith10,4, BLACK,WHITE);
         //��ʾassist5
         site.x=38;site.y=96; LCD_str(site,"6:",BLACK,WHITE);
         site.x=38;site.y=112; LCD_num_BC(site,StreetCalWdith6,4, BLACK,WHITE);  
 
         
         
         //��ʾ������־λ״̬ 
         site.x=80;site.y=0; LCD_str(site,"RFlag:",BLACK,WHITE);
         site.x=80;site.y=16; LCD_num_BC(site,Ring_Find_Flag,4, BLACK,WHITE); 
         //��ʾ�󻷵���־λ״̬ 
         site.x=80;site.y=32; LCD_str(site,"LRing:",BLACK,WHITE);
         site.x=80;site.y=48; LCD_num_BC(site,LeftRing_Find_Flag,4, BLACK,WHITE);
         //��ʾ�һ�����־λ״̬ 
         site.x=80;site.y=64; LCD_str(site,"RRing:",BLACK,WHITE);
         site.x=80;site.y=80; LCD_num_BC(site,RightRing_Find_Flag,4, BLACK,WHITE); 
         
         
         //��ʾ�ϰ���־λ״̬ 
         site.x=80;site.y=96; LCD_str(site,"A5:",BLACK,WHITE);
         site.x=80;site.y=112; LCD_num_BC(site,assist5,4, BLACK,WHITE); 
}




/*ģ������ϵͳ���� 
ʵ����룬δ����*/ 
float Fuzzy(float e, float ec) //e,ec����ʾ������������仯�� 
{ 
        float Kp_calcu;
        unsigned int num, pe, pec;//���뵽ģ�����ƫ���ƫ��仯�� 
        
        const float eRule[7] = {-5,-3,-1,0,1,3,5}; //���e��ģ������ 
        const float ecRule[7]= {-5,-3,-1,0,1,3,5}; //���仯��ec��ģ������ 
        
        float eFuzzy [2]={0.0, 0.0}; //ƫ��e�������� 
        float ecFuzzy[2]={0.0, 0.0}; //ƫ��仯��ec�������� 
       
        const float kpRule[4]={0, 400, 800, 1200};  //Kp��ģ���Ӽ� 
        float KpFuzzy[4]={0.0, 0.0, 0.0, 0.0};      //������Kp�������̶�
        const int KpRule[7][7] = {                  //Kp��ģ�����Ʊ� 
                                      3,3,3,3,3,3,3, 
                                      3,3,3,3,3,3,3, 
                                      2,2,1,1,1,2,2, 
                                      3,2,1,0,1,2,3, 
                                      2,2,1,1,1,2,2, 
                                      3,3,3,3,3,3,3, 
                                      3,3,3,3,3,3,3 
                                   };
        
        /*****���e������������*****/
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
 
 
        /*****���仯��EC������������*****/ 
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
        
        /*********��ѯģ�������*********/
        num = KpRule[pe][pec];                  /*����e,ec��ѯ*/
        KpFuzzy[num] += eFuzzy[0] * ecFuzzy[0]; /*��ˣ���(��֤KpFuzzy�����е��ĸ�����ӵ���һ��������֤�����ڼ�Ȩƽ������ģ��)*/
        num = KpRule[pe][pec+1]; 
        KpFuzzy[num] += eFuzzy[0] * ecFuzzy[1]; /*KpFuzzy�����е�����ռkpRule�����еı��أ�������һһ��Ӧ�Ĺ�ϵ*/
        num = KpRule[pe+1][pec]; 
        KpFuzzy[num] += eFuzzy[1] * ecFuzzy[0]; 
        num = KpRule[pe+1][pec+1]; 
        KpFuzzy[num] += eFuzzy[1] * ecFuzzy[1]; 
 
        /*********��Ȩƽ������ģ��*********/ 
        Kp_calcu = KpFuzzy[0]*kpRule[0] + KpFuzzy[1]*kpRule[1] + KpFuzzy[2]*kpRule[2]
                 + KpFuzzy[3]*kpRule[3];
        return(Kp_calcu);
} 

//����㷨������ 
void dir_control(void) 
{ 
        center=(uint16)dir_zhongzhi;
        current_error = ave_center - 40;
 
        if (BM3 == 1) 
        { 
                  if(LeftRing_Find_Flag == 1 && Ring_Find_Flag == 0 && assist3)  //����󻷵��ڲ��Ķ������
                  {dir_kp1 = LeftRingKP1;} 
                  if(RightRing_Find_Flag == 1 && Ring_Find_Flag == 0 && assistr3)//����һ����ڲ��Ķ������
                  {dir_kp1 = RightRingKP1;} 
                  if (assistr4)//���ڳ��һ�������,�ʼӴ�Kp1�������
                  {dir_kp1 = OutRightRingKP1;} 
                  if (assist4) //���ڳ��󻷵�����,�ʼӴ�Kp1�������
                  {dir_kp1 = OutLeftRingKP1;} 
        } 
        if(BM3 == 0)//���������£��㶨�����ٶ�����,��Ӧ��pid����
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
