#include  "common.h"
#include  "include.h"
#include  "common.h"
#include  "math.h"

/********************Ѱ�ߣ�ʶ��,���߱���*******************/
extern char Start_Gyro_Z_Flag;
extern Coord Angle;

uint8_t StartLineFind_Flag = 0; //��ʼ����������ʶ���־λ
uint8_t Ring_Find_Flag = 0; 
uint8_t LeftRing_Find_Flag = 0; 
uint8_t RightRing_Find_Flag = 0; 
uint8_t Ring_Line_Value = 0; //����ʶ���־λ 
uint8_t ErrorRecord = 0; 
uint8_t OutRingFind_Flag = 0U;
uint8_t LeftRingReadyIn = 0U;
uint8_t RightRingReadyIn = 0U;
uint8_t ReduceLeftRingSpeed = 0U;
uint8_t ReduceRightRingSpeed = 0U;

float InLeftRingValue;   //���󻷵�ת��ƫ��
float InRightRingValue;  //���һ���ת��ƫ��
float OutLeftRingValue;  //���󻷵�ת��ƫ��
float OutRightRingValue; //���һ���ת��ƫ��

float InLeftRingV = 20;   //���󻷵�ת��ƫ��
float InRightRingV = 60;  //���һ���ת��ƫ��
float OutLeftRingV = 10;  //���󻷵�ת��ƫ��
float OutRightRingV = 60; //���һ���ת��ƫ��

uint8_t assist0 = 0; 
uint8_t assist1 = 0; 
uint8_t assist2 = 0; 
uint8_t assist3 = 0; 
uint8_t assist4 = 0; 
uint8_t assist5 = 0; 
uint8_t assist6 = 0; 
uint8_t assist_ADD = 0;/////////�󻷵���־λ 
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
uint8_t assist_rADD = 0;/////////�һ�����־λ 
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
 
const uint8 distence[61] = {   //�����������Ͳ���ר������
                                0, 4, 4, 4, 5, 5, 5, 5, 5, 6,
                                6, 6, 7, 7, 7, 8, 8, 8, 9, 9,
                               10,10, 11,11,12,12,13,13,14,14,
                               15,15, 16,16,17,18,18,19,19,20,
                               20,21, 22,22,23,23,24,24,25,25,
                               26,27, 27,28,29,29,30,30,31,31,32
                            }; 
 
const uint8 distence2[61] = {   //��������ר������
                                  0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 
                                  4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 
                                  7, 8, 9, 10, 11, 11,12,12,13,13, 
                                 15,15, 16,16,17,18,18,19,19,20, 
                                 20,21, 22,22,23,23,24,24,25,25,
                                 26,27, 27,28,29,29,30,30,31,31,32
                             };

const uint8 NeedLine[60] = {   //����ͼ�������ר������
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

uint8_t Y16_Value, StreetCalWdith16;////�����󻷵�����
uint8_t Y12_Value, StreetCalWdith12;
uint8_t Y10_Value, StreetCalWdith10;////�����󻷵�����
uint8_t Y6_Value, StreetCalWdith6;


uint8_t YL16_Value, StreetCalWdithL16;////�����һ�������
uint8_t YL12_Value, StreetCalWdithL12;
uint8_t YL10_Value, StreetCalWdithL10;////�����һ�������
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
uint16 ave_center_s=40; //���ߵļ�Ȩƽ��ֵ
uint16 ave_S_num,S_num;
Site_t center_line_F[60];
Site_t sit_L_F[60];
Site_t sit_R_F[60];

void Cammera_filtration(void);
/////ע��0�Ǻ�ɫ�������ǰ�ɫ
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
                 
                  for(X_Value = 59; X_Value > 0; X_Value--) //��40���кڵ�ֱ������
                  { if (img[X_Value][40] == 0) break;} StreetCalLong = 59 - X_Value; 
                  
                  for(X30_Value = 59; X30_Value > 0; X30_Value--) //��30���кڵ�ֱ������
                  { if (img[X30_Value][30] == 0) break;} StreetCalLong30 = 59 - X30_Value; 
                  
                  for(X50_Value = 59; X50_Value > 0; X50_Value--) //��50���кڵ�ֱ������
                  { if (img[X50_Value][50] == 0) break;} StreetCalLong50 = 59 - X50_Value; 
 
                  for(Y_Value = 40; Y_Value < 80; Y_Value++) //��20���кڵ��ұ�
                  { if (img[20][Y_Value] == 0) break;} StreetCalWdith = Y_Value - 40;
 
                  for(Y0_Value = 40; Y0_Value > 0 ; Y0_Value--) //��20���кڵ����
                  { if (img[20][Y0_Value] == 0) break;} StreetCalWdith0 = 40 - Y0_Value;
                  
                  for(Y1_Value = 40; Y1_Value < 80; Y1_Value++) //��50���кڵ��ұ� 
                  { if (img[50][Y1_Value] == 0) break;} StreetCalWdith1 = Y1_Value - 40;                   
                  
                  for(Y2_Value = 40; Y2_Value < 80; Y2_Value++)  //��35���кڵ��ұ� 
                  { if (img[35][Y2_Value] == 0) break;} StreetCalWdith2 = Y2_Value - 40; 
 
                  for(Y3_Value = 40; Y3_Value > 0; Y3_Value--) //��50���кڵ����
                  { if (img[50][Y3_Value] == 0) break;} StreetCalWdith3 = 40 - Y3_Value; 
 
                  for(Y4_Value = 40; Y4_Value  > 0; Y4_Value--) //��35���кڵ����
                  { if (img[35][Y4_Value] == 0) break;} StreetCalWdith4 = 40 - Y4_Value;
                  
                  for(Y5_Value = 40; Y5_Value  < 80; Y5_Value++) //��30���кڵ��ұ�
                  { if (img[30][Y5_Value] == 0) break;} StreetCalWdith5 = Y5_Value - 40;  
                  
                  for(Y6_Value = 40; Y6_Value  > 0; Y6_Value--) //��53���кڵ����
                  { if (img[53][Y6_Value] == 0) break; } StreetCalWdith6 = 40 - Y6_Value; 
                  
                  for(Y7_Value = 40; Y7_Value  > 0; Y7_Value--) //��30���кڵ����
                  { if (img[30][Y7_Value] == 0) break;} StreetCalWdith7 = 40 - Y7_Value;
                  
                  for(Y8_Value = 40; Y8_Value < 80; Y8_Value++) //��53���кڵ��ұ�
                  { if (img[53][Y8_Value] == 0) break;} StreetCalWdith8 = Y8_Value - 40; 
                  
                  for(Y9_Value = 40; Y9_Value  > 0; Y9_Value--) //��45���кڵ����
                  { if (img[45][Y9_Value] == 0) break;} StreetCalWdith9 = 40 - Y9_Value;

                  for(Y16_Value = 40; Y16_Value < 80; Y16_Value++) //��16���кڵ��ұ�
                  { if (img[16][Y16_Value] == 0) break;} StreetCalWdith16 = Y16_Value - 40; 
                  
                  for(Y12_Value = 40; Y12_Value  < 80; Y12_Value++) //��12���кڵ��ұ�
                  { if (img[12][Y12_Value] == 0) break;} StreetCalWdith12 = Y12_Value - 40;
                  
                  
                  
                  for(Y10_Value = 40; Y10_Value < 80; Y10_Value++) //��16���кڵ��ұ�
                  { if (img[10][Y10_Value] == 0) break;} StreetCalWdith10 = Y10_Value - 40; 
                  
                  for(Y6_Value = 40; Y6_Value  < 80; Y6_Value++) //��12���кڵ��ұ�
                  { if (img[6][Y6_Value] == 0) break;} StreetCalWdith6 = Y6_Value - 40;
                  
                  

                  for(YL16_Value = 40; YL16_Value  > 0; YL16_Value--) //��16���кڵ����
                  { if (img[16][YL16_Value] == 0) break;} StreetCalWdithL16 = 40 - YL16_Value;
                  
                  for(YL12_Value = 40; YL12_Value  > 0; YL12_Value--) //��12���кڵ����
                  { if (img[12][YL12_Value] == 0) break;} StreetCalWdithL12 = 40 - YL12_Value;
                  
                  
                  
                  for(YL10_Value = 40; YL10_Value  > 0; YL10_Value--) //��16���кڵ����
                  { if (img[10][YL10_Value] == 0) break;} StreetCalWdithL10 = 40 - YL10_Value;
                  
                  for(YL6_Value = 40; YL6_Value  > 0; YL6_Value--) //��12���кڵ����
                  { if (img[6][YL6_Value] == 0) break;} StreetCalWdithL6 = 40 - YL6_Value;
                  
                  
                  
                  
                  for(Y45_Value = 40; Y45_Value  < 80; Y45_Value++) //��45���кڵ��ұ�
                  { if (img[45][Y45_Value] == 0) break;} StreetCalWdith45 = Y45_Value - 40;
                  
                  if (BM3 == 1)
                  { 
                            InLeftRingValue = InLeftRingV;   //���󻷵�ת��ƫ��
                            InRightRingValue = InRightRingV;  //���һ���ת��ƫ��
                            OutLeftRingValue = OutLeftRingV;  //���󻷵�ת��ƫ��
                            OutRightRingValue = OutRightRingV; //���һ���ת��ƫ�� 
                  } 
                  else //����
                  { 
                            InLeftRingValue = 20;   //���󻷵�ת��ƫ��
                            InRightRingValue = 60;  //���һ���ת��ƫ��
                            OutLeftRingValue = 20;  //���󻷵�ת��ƫ��
                            OutRightRingValue = 60; //���һ���ת��ƫ��
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
 
                             /*ǰ�������ߵ������㷨*/
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
 
                            /*�����Ƿ�ֹ�����Ĳ���(�洫������������ûɶ��)*/
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

                            /*�����Ƿ�ʮ�ִ���*/
                            if (shi_flag == 0) 
                            {  
                                      if (right_lost == 0) //�ұ�û����
                                      { 
                                                for (W = point; W < 80; W++) //����ɨ��
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

                                      if (left_lost == 0)//���û����
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
                                      
                                      /*Ѳ�߽���*/
                                      if (shi_flag == 0) 
                                      {
                                                 //�ϰ�ͻ�䴦��
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
                                                
                                                 //��ʮ�ִ�����      
                                                 if(((bian_line[H * 2] - bian_line[H * 2 + 4]) < -6) 
                                                 || ((bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) > 6)) //�нϴ�ı�Ե���䴦��
                                                 { 
                                                        if((bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) > 6)   
                                                        { 
                                                                  if((za_flag_r == 1) && (H > 15))   
                                                                  { 
                                                                          if(tubian_num - (bian_line[H * 2 + 1] - bian_line[H * 2 + 5]) > 1)  //�ж��ϴ�ͻ������εĲ���С  
                                                                          { 
                                                                                 if(bian_line[H * 2 + 1] != 79) //�ж����䵽�ı߲��Ǳ�Ե  
                                                                                 {  
                                                                                        if(tubian_num_H - H > 3) //ȷ��ͻ������  
                                                                                        { 
                                                                                              za_flag = 1; //ȷ���ҵ��ϰ�  
                                                                                        } 
                                                                                  } 
                                                                           } 
                                                                  } 
                                                                  if(H < 45)  //45�к���ͻ�䲹�ߴ���
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
                                                            center_line[H].x = center_line[H + 1].x; //������������
                                                 }
                                              
                                                 //�������ߴ���
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

                            /*������ȷ����ʮ�ֺ�Ĵ���*/
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

                            /*�������ϰ�����*/
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
                            
                            /*����ȷ���ǻ�����Ľ�������*/  
                            if (Ring_Find_Flag == 1) 
                            { 
                                       /*��������ߵ����*/ 
                                       if (LeftRing_Find_Flag == 1) 
                                       { 
                                                  /*�����ǽ�������*/
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
                                                              if (h_left_lost == 0 && h_right_lost == 1) //�������һ�������ж������ǲ��Ƕ��һ��
                                                              {assist2 = 1;}  
                                                  } 

                                       } 
                                       /*�������ұߵ����*/ 
                                       if (RightRing_Find_Flag == 1) 
                                       { 
                                                  /*�����ǽ�������*/
                                                  if (h_right_lost == 0 && h_left_lost == 0 && assistr0 == 1) 
                                                  { 
                                                              assist_rADD = 1;
                                                              for(W = point; W > 0; W--) //����ɨ��
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
                                                              for(W = point; W > 0; W--) //����ɨ��
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
                                                              for (W = point; W < 80; W++) //����ɨ��
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
                                                              
                                                              if (h_right_lost == 0 && h_left_lost == 1)//�������һ�������ж������ǲ��Ƕ��һ��
                                                              {assistr2 = 1;} 
                                                  } 
                                       } 
                            } 
  
/////////////////////////////////////////////���󻷵���� 
                            if((assist3==1 && OutRingFind_Flag==1 && center_line[33].x == 0))
                            { 
                                        assist3 = 0; 
                                        assist4 = 1; 
                                        OutRingFind_Flag=0;
                            } 
/////////////////////////////////////////////��ȫ���󻷵���� 

                                                        
/////////////////////////////////////////////���һ������ 
                            if((assistr3==1 && OutRingFind_Flag==1 && center_line[33].x == 0))// && StreetCalLong > 30))
                            { 
                                        assistr3 = 0; 
                                        assistr4 = 1; 
                                        OutRingFind_Flag = 0;
                            } 
/////////////////////////////////////////////��ȫ���һ������ 

 
/////////////////////////////////////////////��ʼ���󻷵� 
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
/////////////////////////////////////////////��ʼ���󻷵� 
 
 
/////////////////////////////////////////////��ʼ���һ��� 
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
 
/////////////////////////////////////////////��ʼ���һ��� 

 
/////////////////////////////////////////////���󻷵�ʶ�𵽳����ھͿ��ұ߲�ֱ�߳�ȥ 
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
/////////////////////////////////////////////���󻷵�ʶ�𵽳����ھͿ��ұ߲�ֱ�߳�ȥ 

 
/////////////////////////////////////////////���һ���ʶ�𵽳����ھͿ���߲�ֱ�߳�ȥ 
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
/////////////////////////////////////////////���һ���ʶ�𵽳����ھͿ���߲�ֱ�߳�ȥ 

                            if (H == 1) 
                            { point = center_line[56].x; } 

                            /*�����޷�*/
                            if ((center_line[H].x < 0) || (center_line[H].x > 79)) //�˴����治Ҫ�޸�,������Ȼ����Ը�
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
 
/////////////////////////////////////////////���󻷵����߱�־λ
                  if (h_left_lost == 0 && assist1 == 1) 
                  {LeftRingReadyIn = 1;}
/////////////////////////////////////////////���󻷵����߱�־λ
 
 
/////////////////////////////////////////////���һ������߱�־λ
                  if (h_right_lost == 0 && assistr1 == 1) 
                  {RightRingReadyIn = 1;}
/////////////////////////////////////////////���һ������߱�־λ

                  
////////////////////////////////////////////�󻷵�assist3׼ȷ��һ�� 
                  if (assist2 == 1 && StreetCalWdith1 > 39) //50���ұߵ�
                  { assist_ADD2 = 1;} 
                  if (assist2 == 1 && assist_ADD2 ==1 && StreetCalWdith1 < 38)//50���ұߵ�
                  { 
                            assist3 = 1; 
                            assist1 = 0; 
                            assist_ADD2 = 0; 
                            assist2 = 0; 
                            Ring_Find_Flag = 0;
                            LeftRingReadyIn = 0;
                  } 
////////////////////////////////////////////�󻷵�assist3׼ȷ��һ�� 
 
 
 
////////////////////////////////////////////�һ���assistr3׼ȷ��һ�� 
                  if (assistr2 == 1 && StreetCalWdith6 > 39) //53����ߵ�
                  { assist_ADDr2 = 1; } 
                  if (assistr2 == 1 && assist_ADDr2 == 1 && StreetCalWdith6 < 38)//53����ߵ�
                  { 
                            assistr3 = 1; 
                            assistr1 = 0; 
                            assist_ADDr2 = 0; 
                            assistr2 = 0; 
                            Ring_Find_Flag = 0;
                            RightRingReadyIn = 0;
                  } 
////////////////////////////////////////////�һ���assistr3׼ȷ��һ�� 

 
////////////////////////////////////////////���󻷵���׼ȷʶ��
                  if ((StreetCalLong > 38 && assist3==1) 
                       || (center_line[32].x == 0 && center_line[35].x == 0 
                           && center_line[38].x == 0 && center_line[41].x == 0 
                           && center_line[44].x == 0 && assist3 == 1)) 
                  { 
                            OutRingFind_Flag = 1; 
                  } 
/////////////////////���󻷵���׼ȷʶ�� 
                  
                      
////////////////////////////////////////////���һ�����׼ȷʶ�� 
                  if ((StreetCalLong > 38 && assistr3 == 1) 
                       || (center_line[32].x == 0 && center_line[35].x == 0 
                           && center_line[38].x == 0 && center_line[41].x == 0
                           && center_line[44].x == 0 && assistr3 == 1)) 
                  { 
                            OutRingFind_Flag = 1; 
                  } 
////////////////////////////////////////////���һ�����׼ȷʶ�� 
                  
                     
                  
////////////////////////////////////////////�����ǳ��󻷵�Ҫ��ֱ�߳�ȥ��� 
                  if (assist4 == 1 && StreetCalWdith1 == 40)////50���ұ� 
                  { assist_ADD1 = 1; } 
 
                  if (assist_ADD1 == 1 && assist4 == 1 && StreetCalWdith1 < 38) 
                  { 
                                 assist5 = 1; 
                                 assist4 = 0; 
                                 assist_ADD1 = 0; 
                                 //Start_Gyro_Z_Flag = 1;//���������Ƕ�ֵ
                  } 
////////////////////////////////////////////�����ǳ��󻷵�Ҫ��ֱ�߳�ȥ��� 
 
 
 
 
////////////////////////////////////////////�����ǳ��һ���Ҫ��ֱ�߳�ȥ��� 
                  if (assistr4 == 1 && StreetCalWdith3 == 40)////50�����
                  { assist_ADDr1 = 1;} 
 
                  if (assist_ADDr1 == 1 && assistr4 == 1 && StreetCalWdith3 < 38)
                  { 
                                 assistr5 = 1; 
                                 assistr4 = 0; 
                                 assist_ADDr1 = 0; 
                  } 
////////////////////////////////////////////�����ǳ��һ���Ҫ��ֱ�߳�ȥ��� 
 
 
 
////////////////////////////////////////////�ڽ�Ҫ���󻷵�ʱ����־λ��� ��� 
                  if (StreetCalWdith6>39  && StreetCalWdith3>39 && assist5==1 && StreetCalLong > 40)//6��53���кڵ����,3��50���кڵ������
                  { assist_ADD3 = 1; } 
                  if ((StreetCalWdith6+StreetCalWdith8)<55 && (StreetCalWdith3+StreetCalWdith1)<55
                      && assist_ADD3==1 && assist5==1 && h_left_lost==0)//StreetCalLong > 40���ƻ����ڲ�����
                  { 
                           assist5 = 0; 
                           assist_ADD3 = 0; 
                           LeftRing_Find_Flag = 0; 
                  } 
////////////////////////////////////////////�ڽ�Ҫ���󻷵�ʱ����־λ��� ���
 
 
 
////////////////////////////////////////////�ڽ�Ҫ���һ���ʱ����־λ��� ���
                  if (StreetCalWdith8>39 && StreetCalWdith1>39 && assistr5==1 && StreetCalLong > 40) //8��53���кڵ��ұ�,1��50���ұ�
                  { assist_ADDr3 = 1; } //45��45���кڵ��ұ�
                  if ((StreetCalWdith6+StreetCalWdith8)<55 && (StreetCalWdith3+StreetCalWdith1)<55
                      && assist_ADDr3==1 && assistr5==1 && h_left_lost == 0)
                  { 
                           assistr5 = 0;
                           assist_ADDr3 = 0;
                           RightRing_Find_Flag = 0;
                  } 
////////////////////////////////////////////�ڽ�Ҫ���һ���ʱ����־λ��� ���
                   
                  
  
////////////////////////////////////////////�����ǻ������ 
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
                                                       && StreetCalLong > 35//ֱ������
                                                       && StreetCalWdith8 < 40 && StreetCalWdith1 < 40 && StreetCalWdith2 <40
                                                       && StreetCalWdith5 < 40 && StreetCalWdith < 40
                                                       && StreetCalWdith2 >= StreetCalWdith5 
                                                       && StreetCalWdith5 >= StreetCalWdith 
                                                       && StreetCalWdith >= StreetCalWdith16 
                                                       && StreetCalWdith16 >= StreetCalWdith12//��ʱ��Q����ʮ�������У�����������������
                                                       //&& abs(StreetCalWdith - StreetCalWdith5) < 8 //�����������пɼ��������
                                                       &&(StreetCalLong30>48||StreetCalLong50>48) //&& abs(ave_center - 40) < 10//���U���������
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
                                                       && StreetCalWdithL16 >= StreetCalWdithL12//��ʱ��Q����ʮ�������У�����������������
                                                       //&& abs(StreetCalWdith0 - StreetCalWdith7) < 8 //�����������пɼ��������
                                                       &&(StreetCalLong30>48||StreetCalLong50>48) //&& abs(ave_center - 40) < 10//���U���������
                                               ) 
                                             { 
                                                            assistr0 = 1; 
                                                            Ring_Find_Flag = 1; 
                                                            RightRing_Find_Flag = 1;                                                       
                                                            StartLineFind_Flag = 1; 
                                             } 
                              } 
                  }  
                  
                  /*���������߼�Ȩ����ó�ƫ����㷨*/ 
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
                  ave_center = sum_center / num_ave; //�����ave_centerӦ�ö���Ϊfloat����
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
 
//ͼ���˲�����
void Cammera_filtration(void)
{
  char x,y;
  
  for(y = 0; y < 68; y++)
  {
    for(x = 0; x < 78; x++)
    {
      if((img[y][x] == 0) && (img[y][x+1] != 0) && (img[y][x+2] == 0)) //�ڰ׺�
      {
        img[y][x+1] = 0;
      }
      else if((img[y][x] != 0) && (img[y][x+1] == 0) && (img[y][x+2] != 0)) //�׺ڰ�
      {
        img[y][x+1] = 1;
      }
      
      if((img[y][x] == 0) && (img[y+1][x] != 0) && (img[y+2][x] == 0))//�ڰ׺�
      {
        img[y+1][x] = 0;
      }
      else if((img[y][x] != 0) && (img[y+1][x] == 0) && (img[y+2][x] != 0)) //�׺ڰ�
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