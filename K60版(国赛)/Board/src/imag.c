#include  "common.h"
#include  "include.h"
#include  "common.h"
#include  "math.h"

/********************寻线，识别,补线变量*******************/
extern char Start_Gyro_Z_Flag;
extern Coord Angle;

uint8_t StartLineFind_Flag = 0; //开始进行起跑线识别标志位
uint8_t Ring_Find_Flag = 0; 
uint8_t LeftRing_Find_Flag = 0; 
uint8_t RightRing_Find_Flag = 0; 
uint8_t Ring_Line_Value = 0; //环岛识别标志位 
uint8_t ErrorRecord = 0; 
uint8_t OutRingFind_Flag = 0U;
uint8_t LeftRingReadyIn = 0U;
uint8_t RightRingReadyIn = 0U;
uint8_t ReduceLeftRingSpeed = 0U;
uint8_t ReduceRightRingSpeed = 0U;

float InLeftRingValue;   //进左环岛转向偏置
float InRightRingValue;  //进右环岛转向偏置
float OutLeftRingValue;  //出左环岛转向偏置
float OutRightRingValue; //出右环岛转向偏置

float InLeftRingV = 20;   //进左环岛转向偏置
float InRightRingV = 60;  //进右环岛转向偏置
float OutLeftRingV = 10;  //出左环岛转向偏置
float OutRightRingV = 60; //出右环岛转向偏置

uint8_t assist0 = 0; 
uint8_t assist1 = 0; 
uint8_t assist2 = 0; 
uint8_t assist3 = 0; 
uint8_t assist4 = 0; 
uint8_t assist5 = 0; 
uint8_t assist6 = 0; 
uint8_t assist_ADD = 0;/////////左环岛标志位 
uint8_t assist_ADD1 = 0U; 
uint8_t assist_ADD2 = 0U; 
uint8_t assist_ADD3 = 0U; 
uint8_t assist_ADDr2 = 0U;
uint8_t assist_ADDr1 = 0U;
uint8_t assist_ADDr3 = 0U;
uint8_t assistr0 = 0; 
uint8_t assistr1 = 0; 
uint8_t assistr2 = 0; 
uint8_t assistr3 = 0; 
uint8_t assistr4 = 0; 
uint8_t assistr5 = 0; 
uint8_t assistr6 = 0; 
uint8_t assist_rADD = 0;/////////右环岛标志位 
uint8_t H, W,i,j,l,P; 
uint8_t point = 40;
uint8_t num_ave = 0;
uint8_t ave_center = 40;
uint8_t left_lost = 0, right_lost = 0,h_left_lost = 0,h_right_lost = 0;
uint8_t za_flag_r = 0, za_flag_l = 0, za_flag = 0,zhangai = 0,shi_flag = 0; 
uint8_t tubian_num = 0, tubian_num_H = 0; 
uint8_t imgbuff[CAMERA_SIZE]; 
uint8_t img[60][CAMERA_W]; 
uint8_t bian_line[120]; 
uint32_t sum_center = 0; 

float QZ_End = 18;
float QZ_Top = 50;

float QZ_zuiqian;
float QZ_zuihou;

Site_t center_line[60]; 
Site_t sit_L[60]; 
Site_t sit_R[60]; 
 
const uint8 distence[61] = {   //其他赛道类型补线专用数组
                                0, 4, 4, 4, 5, 5, 5, 5, 5, 6,
                                6, 6, 7, 7, 7, 8, 8, 8, 9, 9,
                               10,10, 11,11,12,12,13,13,14,14,
                               15,15, 16,16,17,18,18,19,19,20,
                               20,21, 22,22,23,23,24,24,25,25,
                               26,27, 27,28,29,29,30,30,31,31,32
                            }; 
 
const uint8 distence2[61] = {   //环岛补线专用数组
                                  0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 
                                  4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 
                                  7, 8, 9, 10, 11, 11,12,12,13,13, 
                                 15,15, 16,16,17,18,18,19,19,20, 
                                 20,21, 22,22,23,23,24,24,25,25,
                                 26,27, 27,28,29,29,30,30,31,31,32
                             };

const uint8 NeedLine[60] = {   //用于图像处理的行专用数组
                                 20,  21,  22,  23,  24,  25,  26,  27,  28,  30, 
                                 32,  34,  36,  38,  40,  42,  44,  46,  48,  50,
                                 53,  56,  59,  62,  65,  68,  71,  74,  77,  80,
                                 84,  88,  92,  96, 100, 104, 108, 112, 116, 120,
                                125, 130, 135, 140, 145, 150, 155, 160, 165, 170,
                                176, 182, 188, 194, 200, 206, 212, 218, 224, 230
                            };

uint8_t X_Value, StreetCalLong; 
uint8_t X30_Value, StreetCalLong30; 
uint8_t X50_Value, StreetCalLong50; 

uint8_t Y_Value, StreetCalWdith; 
uint8_t Y0_Value, StreetCalWdith0; 
uint8_t Y1_Value, StreetCalWdith1; 
uint8_t Y2_Value, StreetCalWdith2; 
uint8_t Y3_Value, StreetCalWdith3; 
uint8_t Y4_Value, StreetCalWdith4; 
uint8_t Y5_Value, StreetCalWdith5;
uint8_t Y6_Value, StreetCalWdith6;
uint8_t Y7_Value, StreetCalWdith7;
uint8_t Y8_Value, StreetCalWdith8;
uint8_t Y9_Value, StreetCalWdith9;
uint8_t Y45_Value, StreetCalWdith45;

uint8_t Y16_Value, StreetCalWdith16;////消除左环岛误判
uint8_t Y12_Value, StreetCalWdith12;
uint8_t Y10_Value, StreetCalWdith10;////消除左环岛误判
uint8_t Y6_Value, StreetCalWdith6;


uint8_t YL16_Value, StreetCalWdithL16;////消除右环岛误判
uint8_t YL12_Value, StreetCalWdithL12;
uint8_t YL10_Value, StreetCalWdithL10;////消除右环岛误判
uint8_t YL6_Value, StreetCalWdithL6;



uint8_t LineValue = 0;
uint8_t width_x[60]; 
uint8_t StreetLong = 0;

uint8_t YValue, XValue;
uint8_t WidthRight[60];

uint8 speed_ave;
uint16 bianbi_num;
uint8 R_max,L_min;
float bian_bi,bian_ca;
uint8 line[60];
uint8 bian[120];
uint8 bianxin[60];
uint16 ave_center_s=40; //中线的加权平均值
uint16 ave_S_num,S_num;
Site_t center_line_F[60];
Site_t sit_L_F[60];
Site_t sit_R_F[60];

void Cammera_filtration(void);
/////注意0是黑色，非零是白色
void image_processing(void) 
{ 
                  camera_get_img();
                  j = 0; 
                  for(i = 0; i < 60; i++)  
                  { 
                          for(; j < 240; j++)  
                          { 
                                  if(j == (NeedLine[i]))
                                  { 
                                        img_extract(img[i], imgbuff + (NeedLine[i] - 1) * 10, 10);  
                                        break;
                                  } 
                          } 
                  } 
 
                  h_left_lost = 0; 
                  h_right_lost = 0; 
 
                  right_lost = 0; 
                  left_lost = 0; 
 
                  shi_flag = 0; 
 
                  za_flag_r = 0; 
                  za_flag_l = 0; 
                  za_flag = 0; 

                  tubian_num = 0; 
                  zhangai = 0; 
                  tubian_num_H = 0; 
                 
                  for(X_Value = 59; X_Value > 0; X_Value--) //第40列有黑点直道长度
                  { if (img[X_Value][40] == 0) break;} StreetCalLong = 59 - X_Value; 
                  
                  for(X30_Value = 59; X30_Value > 0; X30_Value--) //第30列有黑点直道长度
                  { if (img[X30_Value][30] == 0) break;} StreetCalLong30 = 59 - X30_Value; 
                  
                  for(X50_Value = 59; X50_Value > 0; X50_Value--) //第50列有黑点直道长度
                  { if (img[X50_Value][50] == 0) break;} StreetCalLong50 = 59 - X50_Value; 
 
                  for(Y_Value = 40; Y_Value < 80; Y_Value++) //第20行有黑点右边
                  { if (img[20][Y_Value] == 0) break;} StreetCalWdith = Y_Value - 40;
 
                  for(Y0_Value = 40; Y0_Value > 0 ; Y0_Value--) //第20行有黑点左边
                  { if (img[20][Y0_Value] == 0) break;} StreetCalWdith0 = 40 - Y0_Value;
                  
                  for(Y1_Value = 40; Y1_Value < 80; Y1_Value++) //第50行有黑点右边 
                  { if (img[50][Y1_Value] == 0) break;} StreetCalWdith1 = Y1_Value - 40;                   
                  
                  for(Y2_Value = 40; Y2_Value < 80; Y2_Value++)  //第35行有黑点右边 
                  { if (img[35][Y2_Value] == 0) break;} StreetCalWdith2 = Y2_Value - 40; 
 
                  for(Y3_Value = 40; Y3_Value > 0; Y3_Value--) //第50行有黑点左边
                  { if (img[50][Y3_Value] == 0) break;} StreetCalWdith3 = 40 - Y3_Value; 
 
                  for(Y4_Value = 40; Y4_Value  > 0; Y4_Value--) //第35行有黑点左边
                  { if (img[35][Y4_Value] == 0) break;} StreetCalWdith4 = 40 - Y4_Value;
                  
                  for(Y5_Value = 40; Y5_Value  < 80; Y5_Value++) //第30行有黑点右边
                  { if (img[30][Y5_Value] == 0) break;} StreetCalWdith5 = Y5_Value - 40;  
                  
                  for(Y6_Value = 40; Y6_Value  > 0; Y6_Value--) //第53行有黑点左边
                  { if (img[53][Y6_Value] == 0) break; } StreetCalWdith6 = 40 - Y6_Value; 
                  
                  for(Y7_Value = 40; Y7_Value  > 0; Y7_Value--) //第30行有黑点左边
                  { if (img[30][Y7_Value] == 0) break;} StreetCalWdith7 = 40 - Y7_Value;
                  
                  for(Y8_Value = 40; Y8_Value < 80; Y8_Value++) //第53行有黑点右边
                  { if (img[53][Y8_Value] == 0) break;} StreetCalWdith8 = Y8_Value - 40; 
                  
                  for(Y9_Value = 40; Y9_Value  > 0; Y9_Value--) //第45行有黑点左边
                  { if (img[45][Y9_Value] == 0) break;} StreetCalWdith9 = 40 - Y9_Value;

                  for(Y16_Value = 40; Y16_Value < 80; Y16_Value++) //第16行有黑点右边
                  { if (img[16][Y16_Value] == 0) break;} StreetCalWdith16 = Y16_Value - 40; 
                  
                  for(Y12_Value = 40; Y12_Value  < 80; Y12_Value++) //第12行有黑点右边
                  { if (img[12][Y12_Value] == 0) break;} StreetCalWdith12 = Y12_Value - 40;
                  
                  
                  
                  for(Y10_Value = 40; Y10_Value < 80; Y10_Value++) //第16行有黑点右边
                  { if (img[10][Y10_Value] == 0) break;} StreetCalWdith10 = Y10_Value - 40; 
                  
                  for(Y6_Value = 40; Y6_Value  < 80; Y6_Value++) //第12行有黑点右边
                  { if (img[6][Y6_Value] == 0) break;} StreetCalWdith6 = Y6_Value - 40;
                  
                  

                  for(YL16_Value = 40; YL16_Value  > 0; YL16_Value--) //第16行有黑点左边
                  { if (img[16][YL16_Value] == 0) break;} StreetCalWdithL16 = 40 - YL16_Value;
                  
                  for(YL12_Value = 40; YL12_Value  > 0; YL12_Value--) //第12行有黑点左边
                  { if (img[12][YL12_Value] == 0) break;} StreetCalWdithL12 = 40 - YL12_Value;
                  
                  
                  
                  for(YL10_Value = 40; YL10_Value  > 0; YL10_Value--) //第16行有黑点左边
                  { if (img[10][YL10_Value] == 0) break;} StreetCalWdithL10 = 40 - YL10_Value;
                  
                  for(YL6_Value = 40; YL6_Value  > 0; YL6_Value--) //第12行有黑点左边
                  { if (img[6][YL6_Value] == 0) break;} StreetCalWdithL6 = 40 - YL6_Value;
                  
                  
                  
                  
                  for(Y45_Value = 40; Y45_Value  < 80; Y45_Value++) //第45行有黑点右边
                  { if (img[45][Y45_Value] == 0) break;} StreetCalWdith45 = Y45_Value - 40;
                  
                  if (BM3 == 1)
                  { 
                            InLeftRingValue = InLeftRingV;   //进左环岛转向偏置
                            InRightRingValue = InRightRingV;  //进右环岛转向偏置
                            OutLeftRingValue = OutLeftRingV;  //出左环岛转向偏置
                            OutRightRingValue = OutRightRingV; //出右环岛转向偏置 
                  } 
                  else //慢速
                  { 
                            InLeftRingValue = 20;   //进左环岛转向偏置
                            InRightRingValue = 60;  //进右环岛转向偏置
                            OutLeftRingValue = 20;  //出左环岛转向偏置
                            OutRightRingValue = 60; //出右环岛转向偏置
                  } 
            
                  for(H = 59; H > 55; H--) 
                  { 
                             sit_R[H].y = H; 
                             sit_L[H].y = H; 
                             center_line[H].y = H;
 
                             for(W = 40; W < 80; W++) 
                             { 
                                          if((img[H][W] == 0) && (img[H][W - 1]) != 0) 
                                          { 
                                                      sit_R[H].x = W;
                                                      bian_line[H * 2 + 1] = W; 
                                                      break;
                                          } 
                                          else 
                                          { 
                                                      if((W == 79) && (img[H][W] != 0))
                                                      { 
                                                                sit_R[H].x = 79;
                                                                bian_line[H * 2 + 1] = sit_R[H].x;
                                                      } 
                                          } 
                            } 
 
                             for(W = 40; W > 0; W--) 
                             { 
                                          if((img[H][W] == 0) && (img[H][W + 1] != 0))
                                          { 
                                                      sit_L[H].x = W;
                                                      bian_line[H * 2] = W;
                                                      break;
                                          } 
                                          else
                                          { 
                                                      if((W == 1) && (img[H][W] != 0))
                                                      { 
                                                                sit_L[H].x = 0;
                                                                bian_line[H * 2] = sit_L[H].x;
                                                      } 
                                          } 
                             }
 
                             /*前四行中线单独计算法*/
                             if((bian_line[H * 2] < 1) || (bian_line[H*2+1]>78)) 
                             {
                                         if((bian_line[H * 2] < 1) && (bian_line[H * 2 + 1] > 78))
                                         {
                                                     if(H == 59)
                                                            center_line[H].x  = 40;
                                                     else
                                                            center_line[H].x = center_line[H + 1].x;
                                         }
                                         
                                         else if(bian_line[H * 2] < 1)
                                         {
                                                     h_left_lost = 1;
                                                     if(bian_line[H * 2 + 1] - distence[H] > 0)
                                                     {
                                                            center_line[H].x = (bian_line[H * 2 + 1] - distence[H]);
                                                     }
                                                     else
                                                     {
                                                           if(H == 59) 
                                                                  center_line[H].x = 1; 
                                                           else
                                                                  center_line[H].x = center_line[H + 1].x; 
                                                     }
                                         }
                                        
                                         else if(bian_line[H * 2 + 1] > 78)
                                         {
                                                   h_right_lost = 1; 
                                                   if((bian_line[H * 2] + distence[H]) < 79)
                                                   {
                                                             center_line[H].x = (bian_line[H * 2] + distence[H]);
                                                   }
                                                   else
                                                   {
                                                             if(H == 59)
                                                             center_line[H].x = 78;
                                                             else
                                                             center_line[H].x = center_line[H + 1].x;
                                                   }
                                          }
                             }
 
                             else
                             { 
                                         center_line[H].x = ((bian_line[H * 2] + bian_line[H * 2 + 1]) / 2);
                                         if((bian_line[H * 2 + 1] - bian_line[H * 2]) < 45)
                                         { 
                                                    zhangai = 1; 
                                         } 
                             } 
                  } 

                  point = center_line[56].x; 

                  for (H = 55; H > 0; H--) 
                  { 
                            sit_L[H].y = H; 
                            sit_R[H].y = H;
                            center_line[H].y = H; 
 
                            /*以下是防止卡死的操作(祖传操作，经检验没啥有)*/
                            if (point != 0) 
                            { 
                                      if(img[H][point] == 0)
                                      {
                                                if(H > 40)
                                                { 
                                                          point = center_line[H+2].x;
                                                } 
                                                else
                                                {
                                                          for(i = H; i > 0; i--)
                                                          {
                                                                  center_line[i].x = 0;
                                                                  bian_line[i * 2] = 0;
                                                                  bian_line[i * 2 + 1] = 79;
                                                                  sit_R[i].x = 79;
                                                                  sit_L[i].x = 0;
                                                           }
                                                           point = center_line[56].x;
                                                           break;
                                                 }
                                      }
                            }

                            /*以下是非十字处理*/
                            if (shi_flag == 0) 
                            {  
                                      if (right_lost == 0) //右边没丢线
                                      { 
                                                for (W = point; W < 80; W++) //向右扫描
                                                { 
                                                            if((img[H][W] == 0) && (img[H][W-1]) != 0) 
                                                            { 
                                                                      sit_R[H].x = W; 
                                                                      bian_line[H * 2 + 1] = W;
                                                                      break;
                                                             } 
                                                             else 
                                                            {
                                                                      if((W == 79) && (img[H][W] != 0)) 
                                                                      { 
                                                                              sit_R[H].x = 79;
                                                                              bian_line[H * 2 + 1] = sit_R[H].x;
                                                                              break;
                                                                       } 
                                                             } 
                                                } 
                                               
                                                if ((h_left_lost == 0) && (left_lost == 1) && (bian_line[H * 2 + 1] - bian_line[H * 2 + 3] > 0) )
                                                { 
                                                            sit_R[H].x = 79;
                                                            bian_line[H * 2 + 1] = sit_R[H].x;
                                                            shi_flag = 1;
                                                } 
                                      } 
                                      else
                                      {
                                                  sit_R[H].x = 79;
                                                  bian_line[H * 2 + 1] = sit_R[H].x; 
                                      }

                                      if (left_lost == 0)//左边没丢线
                                      {
                                                for (W = point; W > 0; W--)
                                                {
                                                            if((img[H][W] == 0) && (img[H][W + 1]) != 0)                                       
                                                            {  
                                                                      sit_L[H].x = W;
                                                                      bian_line[H * 2] = W;
                                                                      break;
                                                             }
                                                             else                                                                      
                                                            {
                                                                      if((W == 1) && (img[H][W] != 0))
                                                                      {
                                                                              sit_L[H].x = 0;
                                                                              bian_line[H * 2] = sit_L[H].x;
                                                                              break;
                                                                       }
                                                             }
                                                  }
                                                if ((right_lost == 1) && (bian_line[H * 2] - bian_line[H * 2 + 2] < 0) && (h_right_lost == 0))
                                                { 
                                                            sit_L[H].x = 0;
                                                            bian_line[H * 2] = sit_L[H].x;
                                                            shi_flag = 1;
                                                 }
                                       }
                                      else
                                      {
                                                  sit_L[H].x = 0;
                                                  bian_line[H * 2] = sit_L[H].x;
                                       }
                                      
                                      /*巡线结束*/
                                      if (shi_flag == 0) 
                                      {
                                                 //障碍突变处理
                                                 if (((bian_line[H * 2] - bian_line[H * 2 + 4]) > 10)
                                                   ||((bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) <-10))
                                                 {
                                                            if((h_left_lost == 0) || (h_right_lost == 0))
                                                            {
                                                                        if(((bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) < -10)
                                                                             && ((bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) > -40)
                                                                             && (bian_line[H * 2 + 5] != 79))
                                                                        {
                                                                                tubian_num = bian_line[H * 2 + 5] - bian_line[H * 2 + 1];
                                                                                tubian_num_H = H;
                                                                                za_flag_r = 1;
                                                                        }

                                                                        if(((bian_line[H * 2] - bian_line[H * 2 + 4]) > 10)
                                                                             &&((bian_line[H * 2] - bian_line[H * 2 + 4]) < 40)
                                                                             &&(bian_line[H * 2 + 4] != 0)) 
                                                                        {
                                                                                tubian_num = bian_line[H * 2] - bian_line[H * 2 + 4];
                                                                                tubian_num_H = H;
                                                                                za_flag_l = 1;
                                                                        }

                                                                        if(((bian_line[H * 2] - bian_line[H * 2 + 4]) > 8)
                                                                            &&((bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) < -8))
                                                                        { 
                                                                                za_flag_r = 0;
                                                                                za_flag_l = 0;
                                                                                tubian_num = 0;
                                                                                tubian_num_H = 0;
                                                                        }
                                                             }
                                                 }
                                                
                                                 //非十字处理线      
                                                 if(((bian_line[H * 2] - bian_line[H * 2 + 4]) < -6) 
                                                 || ((bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) > 6)) //有较大的边缘跳变处理
                                                 { 
                                                        if((bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) > 6)   
                                                        { 
                                                                  if((za_flag_r == 1) && (H > 15))   
                                                                  { 
                                                                          if(tubian_num - (bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) > 1)  //判断上次突变与这次的差距大小  
                                                                          { 
                                                                                 if(bian_line[H * 2 + 1] != 79) //判断跳变到的边不是边缘  
                                                                                 {  
                                                                                        if(tubian_num_H - H > 3) //确定突变行数  
                                                                                        { 
                                                                                              za_flag = 1; //确定找到障碍  
                                                                                        } 
                                                                                  } 
                                                                           } 
                                                                  } 
                                                                  if(H < 45)  //45行后做突变补线处理
                                                                  { 
                                                                          center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] + 2;
                                                                  } 
                                                                  else 
                                                                  { 
                                                                          center_line[H].x = center_line[H + 1].x; 
                                                                  } 
                                                                  if(zhangai == 0) 
                                                                  { 
                                                                          right_lost = 1; 
                                                                  } 
                                                        } 
                                                        
                                                        if((bian_line[H * 2] - bian_line[H * 2 + 4]) < -6)
                                                        {  
                                                                  if((za_flag_l == 1) && (H > 15))
                                                                  { 
                                                                          if(tubian_num - (bian_line[H * 2 + 4] - bian_line[H * 2]) > 1) 
                                                                          { 
                                                                                  if(bian_line[H * 2] != 0) 
                                                                                  { 
                                                                                          if(tubian_num_H - H > 3) 
                                                                                          { 
                                                                                                  za_flag = 1; 
                                                                                          } 
                                                                                  } 
                                                                            }
                                                                  } 
                                                                  if(H < 45) 
                                                                  {
                                                                            center_line[H].x = point + bian_line[H * 2 + 1] - bian_line[H * 2 + 3] - 2;
                                                                  }
                                                                  else
                                                                  {
                                                                            center_line[H].x = center_line[H + 1].x; 
                                                                  }
                                                                  if(zhangai == 0)
                                                                  {
                                                                             left_lost = 1;
                                                                  }
                                                       }
                                                        
                                                        if(((bian_line[H * 2] - bian_line[H * 2 + 4]) < -5) 
                                                        && ((bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) > 5))
                                                            center_line[H].x = center_line[H + 1].x; //防起跑线误判
                                                 }
                                              
                                                 //正常边线处理
                                                 else 
                                                 {
                                                              if(((bian_line[H * 2] < 1) && (bian_line[H * 2 + 1] < 79)) 
                                                              || ((bian_line[H * 2] > 0) && (bian_line[H * 2 + 1] > 78)))
                                                              { 
                                                                         if(bian_line[H * 2] < 1) 
                                                                         { 
                                                                                    if((bian_line[H * 2 + 1] - bian_line[H * 2 + 3]) > 1) 
                                                                                    { 
                                                                                              if(H < 45) 
                                                                                              { 
                                                                                                        shi_flag = 1;
                                                                                                        for(l = 0; l < 5; l++) 
                                                                                                        { 
                                                                                                                center_line[H + l].x = 0; 
                                                                                                        } 
                                                                                              } 
                                                                                              else
                                                                                                    center_line[H].x = center_line[H + 1].x ;   
                                                                                    } 
                                                                                    else 
                                                                                    { 
                                                                                              if(H > 50)   
                                                                                              {
                                                                                                       if(h_left_lost == 1) 
                                                                                                       { 
                                                                                                              center_line[H].x = bian_line[H * 2 + 1] - (bian_line[H * 2 + 3] - point) + distence[H + 1]- distence[H];  
                                                                                                       } 
                                                                                                         else  
                                                                                                              center_line[H].x = bian_line[H * 2 + 1] - (bian_line[H * 2 + 3] - point) - distence[H + 1] + distence[H];
                                                                                              }
                                                                                              else
                                                                                                   center_line[H].x = bian_line[H * 2 + 1] - (bian_line[H * 2 + 3] - point) - distence[H + 1] + distence[H];  
                                                                                     } 
                                                                         }

                                                                         if(bian_line[H * 2 + 1] > 78)
                                                                         { 
                                                                                  if((bian_line[H * 2] - bian_line[H * 2 + 2]) < -1)
                                                                                  { 
                                                                                          if(H < 45) 
                                                                                          { 
                                                                                                  shi_flag = 1;
                                                                                                  for(l = 0; l < 5; l++)
                                                                                                  {
                                                                                                          center_line[H + l].x = 0;
                                                                                                  } 
                                                                                          }
                                                                                        
                                                                                          else
                                                                                               center_line[H].x = center_line[H + 1].x ;
                                                                                  }
                                                                                  else 
                                                                                  { 
                                                                                           if(H > 50) 
                                                                                           {
                                                                                                   if(h_right_lost == 1)
                                                                                                   {
                                                                                                            center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] + distence[H] - distence[H + 1];  
                                                                                                   }
                                                                                                   else
                                                                                                   center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] - distence[H] + distence[H + 1];  
                                                                                           }
                                                                                          
                                                                                           else
                                                                                                center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] - distence[H] + distence[H + 1]; 
                                                                                  } 
                                                                         } 
                                                              }
                                                              else  
                                                              { 
                                                                          if((bian_line[H * 2] > 0) && (bian_line[H * 2 + 1] < 79)) 
                                                                          {
                                                                                     center_line[H].x = (bian_line[H * 2] + bian_line[H * 2 + 1]) / 2;
                                                                          }
                                                                          else
                                                                          {
                                                                                     if((bian_line[H * 2] < 1) && (bian_line[H * 2 + 1] > 78))
                                                                                     {
                                                                                               shi_flag = 1;
                                                                                               for(l = 0; l < 5; l++)
                                                                                               {
                                                                                                        center_line[H+l].x = 0;
                                                                                               } 
                                                                                               center_line[H].x = center_line[H + 1].x;
                                                                                     }
                                                                                     else
                                                                                               center_line[H].x = center_line[H + 1].x;  
                                                                                     }
                                                              } 
                                                 } 
                                           
                                                 if((left_lost == 1) && (right_lost == 1))
                                                 {
                                                            shi_flag = 1; 
                                                            for(l = 0; l < 5; l++)
                                                            { 
                                                                    center_line[H + l].x = 0;
                                                            }  
                                                 } 

                                                 point = center_line[H].x;
 
                                                 if(shi_flag == 1) 
                                                 {
                                                          if(H == 55)
                                                                    point = 40; 
                                                          else
                                                                    point = center_line[H + 5].x; 
                                                 }
                                      } 
                                     
                                      else 
                                      {
                                              point = center_line[H + 3].x;
                                              for(l = 0;l < 6;l ++) 
                                              {
                                                      center_line[H + l].x = 0;
                                              }  
                                       } 
                             } 

                            /*以下是确定是十字后的处理*/
                            else if (shi_flag == 1) 
                            { 
                                      for(W = point; W < 80; W++) 
                                      { 
                                                 sit_R[H].y = H; 
                                                 if((img[H][W] == 0) && (img[H][W - 1]) != 0) 
                                                 {  
                                                            sit_R[H].x = W;  
                                                            bian_line[H * 2 + 1] = W;
                                                            break;
                                                 }
                                                 else                                                                      
                                                 {
                                                            if((W == 79) && (img[H][W] != 0))
                                                            {
                                                                       sit_R[H].x = 79;
                                                                       bian_line[H * 2 + 1] = sit_R[H].x;
                                                                       break;
                                                             }
                                                  }
                                       }
                                      
                                      for(W = point; W > 0; W--)
                                      {
                                                sit_L[H].y=H;
                                                if((img[H][W] == 0) && (img[H][W + 1]) != 0)                                       
                                                {  
                                                          sit_L[H].x = W;
                                                          bian_line[H * 2] = W;
                                                          break;
                                                }
                                                else                                                                      
                                                {
                                                           if((W == 1) && (img[H][W] != 0))
                                                           {
                                                                    sit_L[H].x = 0;
                                                                    bian_line[H * 2] = sit_L[H].x;
                                                                    break;
                                                           }
                                                 }
                                       }
                                     
                                      if((bian_line[H * 2] > 1) && (bian_line[H * 2 + 1] < 79))
                                      {
                                                 if((bian_line[H * 2 + 1] - bian_line[H * 2] - distence[H] * 2) < 10)
                                                 {
                                                              center_line[H].x = (bian_line[H * 2 + 1] + bian_line[H * 2]) / 2;
                                                              right_lost = 0; 
                                                              left_lost = 0; 
                                                              shi_flag = 0;
                                                  }
                                       }
                             }

                            /*以下是障碍处理*/
                            if (za_flag == 1) 
                            { 
                                      for(i = H + 4; i > (H - 4); i--) 
                                      {
                                                if(za_flag_r == 1) 
                                                { 
                                                          center_line[i].x = (uint8)(center_line[i + 1].x - 1);
                                                          if(center_line[i].x < 1)
                                                          { 
                                                                    center_line[i].x = 1;
                                                          } 
                                                } 
                                                if(za_flag_l == 1) 
                                                { 
                                                          center_line[i].x = (uint8)(center_line[i + 1].x + 1); 
                                                          if(center_line[i].x > 78)
                                                          { 
                                                                    center_line[i].x = 78; 
                                                          } 
                                                 } 
                                                 bian_line[i * 2] = 0;
                                                 bian_line[i * 2 + 1] = 79;
                                                 sit_R[i].x = 79; 
                                                 sit_L[i].x = 0; 
                                      } 
                                      
                                      for(i = (H - 4); i > 0; i--) 
                                      { 
                                                center_line[i].x = 0; 
                                                bian_line[i * 2] = 0; 
                                                bian_line[i * 2 + 1] = 79; 
                                                sit_R[i].x = 79; 
                                                sit_L[i].x = 0; 
                                      } 
                                        
                                      point = center_line[56].x;
                                      break; 
                             }
                            
                            /*以下确定是环岛后的进环处理*/  
                            if (Ring_Find_Flag == 1) 
                            { 
                                       /*环岛在左边的情况*/ 
                                       if (LeftRing_Find_Flag == 1) 
                                       { 
                                                  /*以下是进环操作*/
                                                  if (h_left_lost == 0 && h_right_lost == 0 && assist0 == 1) 
                                                  { 
                                                              assist_ADD = 1;
                                                              for (W = point; W < 80; W++) 
                                                              { 
                                                                        sit_R[H].y = H; 
                                                                        if((img[H][W] == 0) && (img[H][W - 1]) != 0)                                       
                                                                        { 
                                                                                sit_R[H].x = W; 
                                                                                bian_line[H * 2 + 1] = W; 
                                                                                break; 
                                                                        } 
                                                                        else 
                                                                        { 
                                                                                 if((W == 79) && (img[H][W] != 0)) 
                                                                                 { 
                                                                                        sit_R[H].x = 79; 
                                                                                        bian_line[H * 2 + 1] = sit_R[H].x; 
                                                                                        break; 
                                                                                 } 
                                                                        } 
                                                              } 
                                                              center_line[H].x = bian_line[H * 2 + 1] - distence2[H] - 1; 
                                                  } 

                                                  if (assist_ADD == 1 && h_left_lost == 1 && h_right_lost == 0 ) 
                                                  { 
                                                              assist1 = 1; 
                                                              assist0 = 0;
                                                              ReduceLeftRingSpeed = 1;
                                                              for (W = point; W < 80; W++) 
                                                              { 
                                                                          sit_R[H].y = H;
                                                                          if((img[H][W] == 0) && (img[H][W - 1]) != 0) 
                                                                          { 
                                                                                      sit_R[H].x = W; 
                                                                                      bian_line[H * 2 + 1] = W; 
                                                                                      break; 
                                                                           } 
                                                                           else 
                                                                           {
                                                                                      if((W == 79) && (img[H][W] != 0)) 
                                                                                      { 
                                                                                                   sit_R[H].x = 79; 
                                                                                                   bian_line[H * 2 + 1] = sit_R[H].x; 
                                                                                                   break; 
                                                                                       } 
                                                                           } 
                                                                } 
                                                              center_line[H].x = bian_line[H * 2 + 1] - distence2[H] - 2;  
                                                   }

                                                  if (LeftRingReadyIn) 
                                                  { 
                                                              assist_ADD = 0;
                                                              ReduceLeftRingSpeed = 0;
                                                              for(W = point; W > 0; W--) 
                                                              { 
                                                                          sit_L[H].y = H; 
                                                                          if((img[H][W] == 0) && (img[H][W + 1] != 0))
                                                                          { 
                                                                                    sit_L[H].x = W;
                                                                                    bian_line[H * 2] = W;
                                                                                    break;
                                                                           } 
                                                                           else
                                                                           {
                                                                                     if((W == 1) && (img[H][W] != 0))
                                                                                     {
                                                                                               sit_L[H].x = 0;
                                                                                               bian_line[H * 2] = sit_L[H].x;
                                                                                     } 
                                                                            } 
                                                               } 

                                                              if(bian_line[H * 2] > 1)
                                                                   center_line[H].x = bian_line[H * 2] + distence2[H] - 5;  
                                                              else 
                                                                   center_line[H].x = (uint8_t)InLeftRingValue; 
                                                              if (h_left_lost == 0 && h_right_lost == 1) //这里加这一个辅助判断条件是不是多此一举
                                                              {assist2 = 1;}  
                                                  } 

                                       } 
                                       /*环岛在右边的情况*/ 
                                       if (RightRing_Find_Flag == 1) 
                                       { 
                                                  /*以下是进环操作*/
                                                  if (h_right_lost == 0 && h_left_lost == 0 && assistr0 == 1) 
                                                  { 
                                                              assist_rADD = 1;
                                                              for(W = point; W > 0; W--) //向左扫描
                                                              { 
                                                                          sit_L[H].y = H; 
                                                                          if((img[H][W] == 0) && (img[H][W + 1] != 0))
                                                                          { 
                                                                                    sit_L[H].x = W;
                                                                                    bian_line[H * 2] = W;
                                                                                    break;
                                                                           } 
                                                                           else
                                                                           {
                                                                                     if((W == 1) && (img[H][W] != 0))
                                                                                     {
                                                                                               sit_L[H].x = 0;
                                                                                               bian_line[H * 2] = sit_L[H].x;
                                                                                     } 
                                                                            } 
                                                               } 
                                                              center_line[H].x = bian_line[H * 2] + distence2[H] + 1; 
                                                  } 
                                      
                                                  if (assist_rADD == 1 && h_right_lost == 1 && h_left_lost == 0 ) 
                                                  { 
                                                              assistr1 = 1; 
                                                              assistr0 = 0;
                                                              ReduceRightRingSpeed = 1;
                                                              for(W = point; W > 0; W--) //向左扫描
                                                              { 
                                                                          sit_L[H].y = H; 
                                                                          if((img[H][W] == 0) && (img[H][W + 1] != 0))
                                                                          { 
                                                                                    sit_L[H].x = W;
                                                                                    bian_line[H * 2] = W;
                                                                                    break;
                                                                           } 
                                                                           else
                                                                           {
                                                                                     if((W == 1) && (img[H][W] != 0))
                                                                                     {
                                                                                               sit_L[H].x = 0;
                                                                                               bian_line[H * 2] = sit_L[H].x;
                                                                                     } 
                                                                            } 
                                                               } 
                                                               center_line[H].x = bian_line[H * 2] + distence2[H] + 1; 
                                                  }

                                                  if (RightRingReadyIn) 
                                                  { 
                                                              assist_rADD = 0;
                                                              ReduceRightRingSpeed = 0;
                                                              for (W = point; W < 80; W++) //向右扫描
                                                              { 
                                                                        sit_R[H].y = H; 
                                                                        if((img[H][W] == 0) && (img[H][W - 1]) != 0)                                       
                                                                        { 
                                                                                sit_R[H].x = W; 
                                                                                bian_line[H * 2 + 1] = W; 
                                                                                break; 
                                                                        } 
                                                                        else 
                                                                        { 
                                                                                 if((W == 79) && (img[H][W] != 0)) 
                                                                                 { 
                                                                                        sit_R[H].x = 79; 
                                                                                        bian_line[H * 2 + 1] = sit_R[H].x; 
                                                                                        break; 
                                                                                 } 
                                                                        } 
                                                              } 
                                                              
                                                              if(bian_line[H * 2 + 1] < 79)
                                                                   center_line[H].x = bian_line[H * 2 + 1] - distence2[H] - 3; 
                                                              else                                                                                                                                                                         
                                                                   center_line[H].x = (uint8_t)InRightRingValue;  
                                                              
                                                              if (h_right_lost == 0 && h_left_lost == 1)//这里加这一个辅助判断条件是不是多此一举
                                                              {assistr2 = 1;} 
                                                  } 
                                       } 
                            } 
  
/////////////////////////////////////////////出左环岛检测 
                            if((assist3==1 && OutRingFind_Flag==1 && center_line[33].x == 0))
                            { 
                                        assist3 = 0; 
                                        assist4 = 1; 
                                        OutRingFind_Flag=0;
                            } 
/////////////////////////////////////////////完全进左环岛检测 

                                                        
/////////////////////////////////////////////出右环岛检测 
                            if((assistr3==1 && OutRingFind_Flag==1 && center_line[33].x == 0))// && StreetCalLong > 30))
                            { 
                                        assistr3 = 0; 
                                        assistr4 = 1; 
                                        OutRingFind_Flag = 0;
                            } 
/////////////////////////////////////////////完全进右环岛检测 

 
/////////////////////////////////////////////开始出左环岛 
                            if (assist4 == 1) 
                            { 
                                      shi_flag = 0; 
                                      for(W = point; W > 0; W--) 
                                      { 
                                                    sit_L[H].y = H; 
                                                    if((img[H][W] == 0) && (img[H][W + 1] != 0))
                                                    { 
                                                            sit_L[H].x = W;
                                                            bian_line[H * 2] = W;
                                                            break;
                                                    } 
                                                    else
                                                    {
                                                            if((W == 1) && (img[H][W] != 0))
                                                            {
                                                                      sit_L[H].x = 0;
                                                                      bian_line[H * 2] = sit_L[H].x;
                                                            } 
                                                    } 
                                      } 
                                      if(bian_line[H * 2] < 78) 
                                           center_line[H].x = bian_line[H * 2] + distence2[H] - 5;
                                      else  
                                           center_line[H].x = (uint8_t)OutLeftRingValue;
                            } 
/////////////////////////////////////////////开始出左环岛 
 
 
/////////////////////////////////////////////开始出右环岛 
                            if (assistr4 == 1) 
                            { 
                                      shi_flag = 0; 
                                      for (W = point; W < 80; W++) 
                                      { 
                                                    sit_R[H].y = H; 
                                                    if((img[H][W] == 0) && (img[H][W - 1]) != 0)                                       
                                                    { 
                                                                 sit_R[H].x = W; 
                                                                 bian_line[H * 2 + 1] = W; 
                                                                 break; 
                                                    } 
                                                    else 
                                                    { 
                                                                 if((W == 79) && (img[H][W] != 0)) 
                                                                 { 
                                                                       sit_R[H].x = 79; 
                                                                       bian_line[H * 2 + 1] = sit_R[H].x; 
                                                                       break; 
                                                                 } 
                                                    } 
                                      } 
                                      if (bian_line[H * 2 + 1] < 78)
                                           center_line[H].x = bian_line[H * 2 + 1] - distence2[H] + 5;
                                      else 
                                           center_line[H].x = (uint8_t)OutRightRingValue;
                            } 
 
/////////////////////////////////////////////开始出右环岛 

 
/////////////////////////////////////////////出左环岛识别到出环口就靠右边补直线出去 
                            if (assist5 == 1) 
                            { 
                                          for (W = point; W < 80; W++) 
                                          { 
                                                    sit_R[H].y = H; 
                                                    if((img[H][W] == 0) && (img[H][W - 1]) != 0)                                       
                                                    { 
                                                                 sit_R[H].x = W; 
                                                                 bian_line[H * 2 + 1] = W; 
                                                                 break; 
                                                    } 
                                                    else 
                                                    { 
                                                                 if((W == 79) && (img[H][W] != 0)) 
                                                                 { 
                                                                       sit_R[H].x = 79; 
                                                                       bian_line[H * 2 + 1] = sit_R[H].x; 
                                                                       break; 
                                                                 } 
                                                    } 
                                          } 
                                          if(bian_line[H * 2 + 1] < 78)
                                              center_line[H].x = bian_line[H * 2 + 1] - distence2[H];
                                          else 
                                              center_line[H].x = 79;
                            } 
/////////////////////////////////////////////出左环岛识别到出环口就靠右边补直线出去 

 
/////////////////////////////////////////////出右环岛识别到出环口就靠左边补直线出去 
                            if (assistr5 == 1)
                            { 
                                          for(W = point; W > 0; W--) 
                                          { 
                                                    sit_L[H].y = H; 
                                                    if((img[H][W] == 0) && (img[H][W + 1] != 0))
                                                    { 
                                                            sit_L[H].x = W;
                                                            bian_line[H * 2] = W;
                                                            break;
                                                    } 
                                                    else
                                                    {
                                                            if((W == 1) && (img[H][W] != 0))
                                                            {
                                                                      sit_L[H].x = 0;
                                                                      bian_line[H * 2] = sit_L[H].x;
                                                            } 
                                                    } 
                                          } 
                                          if (bian_line[H * 2] > 1)
                                              center_line[H].x = bian_line[H * 2] + distence2[H];
                                          else
                                              center_line[H].x = 0;
                            } 
/////////////////////////////////////////////出右环岛识别到出环口就靠左边补直线出去 

                            if (H == 1) 
                            { point = center_line[56].x; } 

                            /*中线限幅*/
                            if ((center_line[H].x < 0) || (center_line[H].x > 79)) //此处警告不要修改,如若不然后果自负
                            { 
                                        for(i = H; i > 0; i--)
                                        {
                                                    center_line[i].x = 0;
                                                    bian_line[i * 2] = 0;
                                                    bian_line[i * 2 + 1] = 79;
                                                    sit_R[i].x = 79;
                                                    sit_L[i].x = 0;
                                        }
                                        point = center_line[56].x;
                                        break;
                           }
                  } 
 
/////////////////////////////////////////////进左环岛补线标志位
                  if (h_left_lost == 0 && assist1 == 1) 
                  {LeftRingReadyIn = 1;}
/////////////////////////////////////////////进左环岛补线标志位
 
 
/////////////////////////////////////////////进右环岛补线标志位
                  if (h_right_lost == 0 && assistr1 == 1) 
                  {RightRingReadyIn = 1;}
/////////////////////////////////////////////进右环岛补线标志位

                  
////////////////////////////////////////////左环岛assist3准确置一法 
                  if (assist2 == 1 && StreetCalWdith1 > 39) //50行右边点
                  { assist_ADD2 = 1;} 
                  if (assist2 == 1 && assist_ADD2 ==1 && StreetCalWdith1 < 38)//50行右边点
                  { 
                            assist3 = 1; 
                            assist1 = 0; 
                            assist_ADD2 = 0; 
                            assist2 = 0; 
                            Ring_Find_Flag = 0;
                            LeftRingReadyIn = 0;
                  } 
////////////////////////////////////////////左环岛assist3准确置一法 
 
 
 
////////////////////////////////////////////右环岛assistr3准确置一法 
                  if (assistr2 == 1 && StreetCalWdith6 > 39) //53行左边点
                  { assist_ADDr2 = 1; } 
                  if (assistr2 == 1 && assist_ADDr2 == 1 && StreetCalWdith6 < 38)//53行左边点
                  { 
                            assistr3 = 1; 
                            assistr1 = 0; 
                            assist_ADDr2 = 0; 
                            assistr2 = 0; 
                            Ring_Find_Flag = 0;
                            RightRingReadyIn = 0;
                  } 
////////////////////////////////////////////右环岛assistr3准确置一法 

 
////////////////////////////////////////////出左环岛口准确识别
                  if ((StreetCalLong > 38 && assist3==1) 
                       || (center_line[32].x == 0 && center_line[35].x == 0 
                           && center_line[38].x == 0 && center_line[41].x == 0 
                           && center_line[44].x == 0 && assist3 == 1)) 
                  { 
                            OutRingFind_Flag = 1; 
                  } 
/////////////////////出左环岛口准确识别 
                  
                      
////////////////////////////////////////////出右环岛口准确识别 
                  if ((StreetCalLong > 38 && assistr3 == 1) 
                       || (center_line[32].x == 0 && center_line[35].x == 0 
                           && center_line[38].x == 0 && center_line[41].x == 0
                           && center_line[44].x == 0 && assistr3 == 1)) 
                  { 
                            OutRingFind_Flag = 1; 
                  } 
////////////////////////////////////////////出右环岛口准确识别 
                  
                     
                  
////////////////////////////////////////////以下是出左环岛要补直线出去检测 
                  if (assist4 == 1 && StreetCalWdith1 == 40)////50行右边 
                  { assist_ADD1 = 1; } 
 
                  if (assist_ADD1 == 1 && assist4 == 1 && StreetCalWdith1 < 38) 
                  { 
                                 assist5 = 1; 
                                 assist4 = 0; 
                                 assist_ADD1 = 0; 
                                 //Start_Gyro_Z_Flag = 1;//开启陀螺仪读值
                  } 
////////////////////////////////////////////以下是出左环岛要补直线出去检测 
 
 
 
 
////////////////////////////////////////////以下是出右环岛要补直线出去检测 
                  if (assistr4 == 1 && StreetCalWdith3 == 40)////50行左边
                  { assist_ADDr1 = 1;} 
 
                  if (assist_ADDr1 == 1 && assistr4 == 1 && StreetCalWdith3 < 38)
                  { 
                                 assistr5 = 1; 
                                 assistr4 = 0; 
                                 assist_ADDr1 = 0; 
                  } 
////////////////////////////////////////////以下是出右环岛要补直线出去检测 
 
 
 
////////////////////////////////////////////在将要出左环岛时将标志位清除 清灯 
                  if (StreetCalWdith6>39  && StreetCalWdith3>39 && assist5==1 && StreetCalLong > 40)//6第53行有黑点左边,3第50行有黑点在左边
                  { assist_ADD3 = 1; } 
                  if ((StreetCalWdith6+StreetCalWdith8)<55 && (StreetCalWdith3+StreetCalWdith1)<55
                      && assist_ADD3==1 && assist5==1 && h_left_lost==0)//StreetCalLong > 40限制换到内部清了
                  { 
                           assist5 = 0; 
                           assist_ADD3 = 0; 
                           LeftRing_Find_Flag = 0; 
                  } 
////////////////////////////////////////////在将要出左环岛时将标志位清除 清灯
 
 
 
////////////////////////////////////////////在将要出右环岛时将标志位清除 清灯
                  if (StreetCalWdith8>39 && StreetCalWdith1>39 && assistr5==1 && StreetCalLong > 40) //8第53行有黑点右边,1第50行右边
                  { assist_ADDr3 = 1; } //45第45行有黑点右边
                  if ((StreetCalWdith6+StreetCalWdith8)<55 && (StreetCalWdith3+StreetCalWdith1)<55
                      && assist_ADDr3==1 && assistr5==1 && h_left_lost == 0)
                  { 
                           assistr5 = 0;
                           assist_ADDr3 = 0;
                           RightRing_Find_Flag = 0;
                  } 
////////////////////////////////////////////在将要出右环岛时将标志位清除 清灯
                   
                  
  
////////////////////////////////////////////以下是环岛检测 
                  if (Ring_Find_Flag == 0 && LeftRing_Find_Flag==0 && RightRing_Find_Flag == 0) 
                  { 
                              for(Ring_Line_Value = 55; Ring_Line_Value > 25; Ring_Line_Value-- ) 
                              { 
                                             if(       assist5 == 0 && shi_flag == 0 
                                                       && h_left_lost == 0 && h_right_lost == 0 
                                                       && left_lost == 1 && right_lost == 0 

                                                       && (bian_line[Ring_Line_Value * 2] < 2) 
                                                       && (bian_line[Ring_Line_Value * 2 + 6] >  2) 
 
                                                       && (bian_line[Ring_Line_Value * 2 - 3] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 - 5] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 - 7] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 + 1] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 + 7] < 78)
                                                       && StreetCalLong > 35//直道长度
                                                       && StreetCalWdith8 < 40 && StreetCalWdith1 < 40 && StreetCalWdith2 <40
                                                       && StreetCalWdith5 < 40 && StreetCalWdith < 40
                                                       && StreetCalWdith2 >= StreetCalWdith5 
                                                       && StreetCalWdith5 >= StreetCalWdith 
                                                       && StreetCalWdith >= StreetCalWdith16 
                                                       && StreetCalWdith16 >= StreetCalWdith12//有时候Q弯入十字有误判，加入此条件解决误判
                                                       //&& abs(StreetCalWdith - StreetCalWdith5) < 8 //弯道如果有误判可加入此条件
                                                       &&(StreetCalLong30>48||StreetCalLong50>48) //&& abs(ave_center - 40) < 10//解决U型弯道误判
                                                ) 
                                             { 
                                                            assist0 = 1; 
                                                            Ring_Find_Flag = 1; 
                                                            LeftRing_Find_Flag = 1; 
                                                            StartLineFind_Flag = 1; 
                                             } 
                                             if(       assistr5 == 0 && shi_flag == 0 
                                                       && h_right_lost == 0 && h_left_lost == 0 
                                                       && right_lost == 1 && left_lost == 0 
 
                                                       && (bian_line[Ring_Line_Value * 2 + 1] > 78) 
                                                       && (bian_line[Ring_Line_Value * 2 + 7] < 78) 
  
                                                       && (bian_line[Ring_Line_Value * 2 - 4] > 1) 
                                                       && (bian_line[Ring_Line_Value * 2 - 6] > 1) 
                                                       && (bian_line[Ring_Line_Value * 2 - 8] > 1) 
                                                       && (bian_line[Ring_Line_Value * 2] > 1) 
                                                       && (bian_line[Ring_Line_Value * 2 + 8] > 1) 
                                                       && StreetCalWdith0 < 38 && StreetCalWdith7 < 40 && StreetCalWdith4 < 40
                                                       && StreetCalWdith9 < 40 && StreetCalWdith3 < 40 && StreetCalWdith6 < 40
                                                       && (StreetCalLong > 35)
                                                       && StreetCalWdith4 >= StreetCalWdith7 
                                                       && StreetCalWdith7 >= StreetCalWdith0 
                                                       && StreetCalWdith0 >= StreetCalWdithL16 
                                                       && StreetCalWdithL16 >= StreetCalWdithL12//有时候Q弯入十字有误判，加入此条件解决误判
                                                       //&& abs(StreetCalWdith0 - StreetCalWdith7) < 8 //弯道如果有误判可加入此条件
                                                       &&(StreetCalLong30>48||StreetCalLong50>48) //&& abs(ave_center - 40) < 10//解决U型弯道误判
                                               ) 
                                             { 
                                                            assistr0 = 1; 
                                                            Ring_Find_Flag = 1; 
                                                            RightRing_Find_Flag = 1;                                                       
                                                            StartLineFind_Flag = 1; 
                                             } 
                              } 
                  }  
                  
                  /*以下是中线加权计算得出偏差的算法*/ 
                  for(i = 0; i < 60; i++) 
                  { 
                             if((center_line[i].x > 1) && (center_line[i].x < 78)) 
                             { 
                                            sum_center += center_line[i].x; 
                                            num_ave++; 
                                            if((i > (int)QZ_End) && (i < (int)QZ_Top)) 
                                            { 
                                                           sum_center += center_line[i].x * 3; 
                                                           num_ave += 3; 
                                            } 
                              } 
                  } 
                  ave_center = sum_center / num_ave; //这里的ave_center应该定义为float类型
                  sum_center = 0; 
                  num_ave = 0; 
                  bianbi_num = 0;
                  R_max = 40;
                  L_min = 40;
                  for(i=0; i<60; i++) 
                  {
                            if((center_line[i].x>0) && (center_line[i].x<79))  
                            {
                                      if(center_line[i].x>R_max)  
                                      {R_max=center_line[i].x;}
                                      if(center_line[i].x<L_min)  
                                      {L_min=center_line[i].x;}
                                   
                                      if(num_ave==0)
                                      {speed_ave=i; }
                                      sum_center+=center_line[i].x;
                                      num_ave++;
                                      if((i>speed_ave)&&(i<speed_ave+(60-speed_ave)/2)) 
                                      {
                                              sum_center+=center_line[i].x;
                                              sum_center+=center_line[i].x;
                                              num_ave+=2;
                                      }
                                      bianbi_num++;
                            } 
                  }
                  bian_bi=(float)bianbi_num/60.0;

                  if((1-(float)(R_max-L_min)/72.0)>0)
                  {bian_ca=1-((float)(R_max-L_min)/72.0);}
                  else bian_ca=0;
  
                  ave_center_s=sum_center/num_ave;
                  sum_center=0;
                  num_ave=0;
 
                  for(i=0;i<60;i++)
                  {line[i]=center_line[i].x;}
                  
                  for(i=0;i<120;i++)
                  {bian[i]=bian_line[i];} 
  
                  for(i=0;i<60;i++) 
                  {
                         sit_L_F[i].x=sit_L[i].x;
                         sit_R_F[i].x=sit_R[i].x;
                         center_line_F[i].x=center_line[i].x;
                         
                         sit_L_F[i].y=sit_L[i].y+68;
                         sit_R_F[i].y=sit_R[i].y+68;
                         center_line_F[i].y=center_line[i].y+68;
                  }
                  
                  for(i=0;i<60;i++)  
                  {bianxin[i]=(sit_R[i].x-sit_L[i].x)/2;}
                  S_num=0;
                  ave_S_num=0;
                  
                  for(i=59;i>40;i--) 
                  {S_num+=center_line[i].x;}
                  ave_S_num=S_num/19;
} 
 
//图像滤波函数
void Cammera_filtration(void)
{
  char x,y;
  
  for(y = 0; y < 68; y++)
  {
    for(x = 0; x < 78; x++)
    {
      if((img[y][x] == 0) && (img[y][x+1] != 0) && (img[y][x+2] == 0)) //黑白黑
      {
        img[y][x+1] = 0;
      }
      else if((img[y][x] != 0) && (img[y][x+1] == 0) && (img[y][x+2] != 0)) //白黑白
      {
        img[y][x+1] = 1;
      }
      
      if((img[y][x] == 0) && (img[y+1][x] != 0) && (img[y+2][x] == 0))//黑白黑
      {
        img[y+1][x] = 0;
      }
      else if((img[y][x] != 0) && (img[y+1][x] == 0) && (img[y+2][x] != 0)) //白黑白
      {
        img[y+1][x] = 1;
      }
    }  
  }
}


char User_Stop_Line_JianCe(void) 
{ 
      unsigned char x, y; 
      char i = 0; 
      if (StartLineFind_Flag == 1) 
      { 
            for(y = 44; y < 60; y++)
            {
                  for(x = 11; x < 72; x++ )
                  {
                        if((img[y][x]==0)&&(img[y][x+1]!=0))
                        { 
                              x+=3;
                              for(;x < 72; x++)
                              {
                                    if((img[y][x]!=0)&&(img[y][x+1]==0))   
                                    {
                                          for(;x < 72; x++)
                                          {
                                                if((img[y][x]==0)&&(img[y][x+1]!=0)) 
                                                {
                                                      x+=3;
                                                      for(;x < 72; x++)
                                                      {
                                                            if((img[y][x]!=0)&&(img[y][x+1]==0))
                                                            {
                                                                  for(;x < 72; x++)
                                                                  {
                                                                        if((img[y][x]==0)&&(img[y][x+1]!=0)) 
                                                                        {
                                                                              x+=3;
                                                                              for(;x < 72; x++)
                                                                              {                            
                                                                                    if((img[y][x]!=0)&&(img[y][x+1]==0))
                                                                                    {
                                                                                            i ++;
                                                                                            if(i >= 3)
                                                                                            {
                                                                                                    return 1;
                                                                                            }                            
                                                                                     }
                                                                               }
                                                                        } 
                                                                  } 
                                                            }
                                                      }
                                                } 
                                          }
                                    }
                              }
                        }        
                  }
            } 
      } 
      return 0;
} 