#include "include.h" 


/********************寻线，识别,补线变量*******************/
extern uint8_t ImageBuffer[60][80];
extern uint8_t gImageBuffer[OV7620_H * OV7620_W / 8];
uint8_t StartLineFind_Flag = 0U;
uint8_t OutRingFind_Flag = 0U;
uint8_t Ring_Find_Flag = 0U; 
uint8_t LeftRing_Find_Flag = 0U; 
uint8_t RightRing_Find_Flag = 0U; 
uint8_t Ring_Line_Value = 0U; 
uint8_t assist0 = 0U; 
uint8_t assist1 = 0U; 
uint8_t assist2 = 0U; 
uint8_t assist3 = 0U; 
uint8_t assist4 = 0U; 
uint8_t assist5 = 0U; 
uint8_t assist6 = 0U; 
uint8_t assist_ADD = 0U;
uint8_t assist_ADD1 = 0U; 
uint8_t assist_ADD2 = 0U; 
uint8_t assist_ADD3 = 0U; 
uint8_t QFlag = 0U; 
uint8_t TempError = 0U; 
extern int16_t CurrentError; 
uint8_t MidPointHis[10];//////////////历史的中线 
extern uint8_t  StopFlag; 

uint8_t  S; 

uint8_t assistr0 = 0U; 
uint8_t assistr1 = 0U; 
uint8_t assistr2 = 0U; 
uint8_t assistr3 = 0U; 
uint8_t assistr4 = 0U; 
uint8_t assistr5 = 0U; 
uint8_t assistr6 = 0U; 
uint8_t assist_rADD = 0U;
uint8_t assist_ADDr2 = 0U;
uint8_t assist_ADDr1 = 0U;
uint8_t assist_ADDr3 = 0U;
uint8_t H, W,i,j,l;  
uint8_t QZ_End = 18U;
uint8_t QZ_Top = 48U;
uint8_t point = 40U; 
uint8_t num_ave = 0U; 
uint8_t ave_center = 40U; 
uint8_t bian_line[120]; 
uint8_t tubian_num = 0, tubian_num_H = 0; 
uint8_t left_lost = 0, right_lost = 0, h_left_lost = 0, h_right_lost = 0; 
uint8_t za_flag_r = 0, za_flag_l = 0, za_flag = 0, zhangai = 0, shi_flag = 0; 
uint32_t sum_center = 0; 
Site_t center_line[60]; 

uint8_t distence[61] = {  0, 4, 4, 4, 5, 5, 5, 5, 5, 6,
                          6, 6, 7, 7, 7, 8, 8, 8, 9, 9,
                         10,10, 11,11,12,12,13,13,14,14,
                         15,15, 16,16,17,18,18,19,19,20,
                         20,21, 22,22,23,23,24,24,25,25,
                         26,27, 27,28,29,29,30,30,31,31,32
                     };
 
uint8_t distence2[61] = { 0, 4, 4, 4, 5, 5, 5, 5, 5, 6,
                          6, 6, 7, 7, 7, 8, 8, 8, 9, 9,
                         10,10, 11,11,12,12,13,13,14,14,
                         15,15, 16,16,17,18,18,19,19,20,
                         20,21, 22,22,23,23,24,24,25,25,
                         26,27, 27,28,29,29,30,30,31,31,32
                     };
 
uint8_t NeedLine[60] = { 20,  21,  22,  23,  24,  25,  26,  27,  28,  30, 
                         32,  34,  36,  38,  40,  42,  44,  46,  48,  50,
                         53,  56,  59,  62,  65,  68,  71,  74,  77,  80,
                         84,  88,  92,  96, 100, 104, 108, 112, 116, 120,
                        125, 130, 135, 140, 145, 150, 155, 160, 165, 170,
                        176, 182, 188, 194, 200, 206, 212, 218, 224, 230
                     };
 

uint8_t q,w,e,r,t,y,u,p;
uint8_t rq,rw,re,rr,rt,ry,ru,rp;
uint8_t X_Value, StreetCalLong; 
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


/////注意0是黑色，非零是白色 
void ImageIdentification(void) 
{ 
                  j = 0; 
                  for(i = 0; i < 60; i++) 
                  { 
                          for(; j < 240; j++)  
                          { 
                                  if(j == (NeedLine[i]))
                                  { 
                                        Img_Extract(ImageBuffer[i], gImageBuffer + (NeedLine[i] - 1) * 10, 10);
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
/***********************************出环岛条件************************************************/
                  for(X_Value = 59; X_Value > 0; X_Value--) //第40列有黑点直道长度
                  { if (ImageBuffer[X_Value][40] == 0) break;} StreetCalLong = 59 - X_Value; 
                  
                  for(Y_Value = 40; Y_Value < 80; Y_Value++) //第20行有黑点右边
                  { if (ImageBuffer[20][Y_Value] == 0) break;} StreetCalWdith = Y_Value - 40;
                  
                  for(Y0_Value = 40; Y0_Value > 0 ; Y0_Value--) //第20行有黑点左边
                  { if (ImageBuffer[20][Y0_Value] == 0) break;} StreetCalWdith0 = 40 - Y0_Value;
                  
                  for(Y1_Value = 40; Y1_Value < 80; Y1_Value++) //第50行有黑点右边
                  { if (ImageBuffer[50][Y1_Value] == 0) break;} StreetCalWdith1 = Y1_Value - 40;                   
                  
                  for(Y2_Value = 40; Y2_Value < 80; Y2_Value++)  //第35行有黑点右边
                  { if (ImageBuffer[35][Y2_Value] == 0) break;} StreetCalWdith2 = Y2_Value - 40; 
 
                  for(Y3_Value = 40; Y3_Value > 0; Y3_Value--) //第50行有黑点左边
                  { if (ImageBuffer[50][Y3_Value] == 0) break;} StreetCalWdith3 = 40 - Y3_Value; 
 
                  for(Y4_Value = 40; Y4_Value  > 0; Y4_Value--) //第35行有黑点左边
                  { if (ImageBuffer[35][Y4_Value] == 0) break;} StreetCalWdith4 = 40 - Y4_Value;
                  
                  for(Y5_Value = 40; Y5_Value  < 80; Y5_Value++) //第30行有黑点右边
                  { if (ImageBuffer[30][Y5_Value] == 0) break;} StreetCalWdith5 = Y5_Value - 40;  
                  
                  for(Y6_Value = 40; Y6_Value  > 0; Y6_Value--) //第53行有黑点左边
                  { if (ImageBuffer[53][Y6_Value] == 0) break; } StreetCalWdith6 = 40 - Y6_Value; 
                  
                  for(Y7_Value = 40; Y7_Value  > 0; Y7_Value--) //第30行有黑点左边
                  { if (ImageBuffer[30][Y7_Value] == 0) break;} StreetCalWdith7 = 40 - Y7_Value;
                  
                  for(Y8_Value = 40; Y8_Value < 80; Y8_Value++) //第53行有黑点右边
                  { if (ImageBuffer[53][Y8_Value] == 0) break;} StreetCalWdith8 = Y8_Value - 40; 
                  
                  for(Y9_Value = 40; Y9_Value  > 0; Y9_Value--) //第45行有黑点左边
                  { if (ImageBuffer[45][Y9_Value] == 0) break;} StreetCalWdith9 = 40 - Y9_Value;
                  
                  /**********中线历史数组************/
                  if (assist4 == 0 || assistr4 == 0)
                  {
                              MidPointHis[9] = MidPointHis[8];
                              MidPointHis[8] = MidPointHis[7];
                              MidPointHis[7] = MidPointHis[6];
                              MidPointHis[6] = MidPointHis[5];
                              MidPointHis[5] = MidPointHis[4];
                              MidPointHis[4] = MidPointHis[3];
                              MidPointHis[3] = MidPointHis[2];
                              MidPointHis[2] = MidPointHis[1];
                              MidPointHis[1] = MidPointHis[0];
                              MidPointHis[0] = ave_center;
                  }
                  
 
                  for(H = 59; H > 55; H--) 
                  { 
                             center_line[H].y = H; 

                             for(W = 40; W < 80; W++)
                             { 
                                          if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W - 1]) != 0) 
                                          { 
                                                      bian_line[H * 2 + 1] = W; 
                                                      break;
                                          } 
                                          else 
                                          { 
                                                      if((W == 79) && (ImageBuffer[H][W] != 0))
                                                      { 
                                                                bian_line[H * 2 + 1] = 79;
                                                      } 
                                          } 
                            } 
                          
                             for(W = 40; W > 0; W--)
                             { 
                                          if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W + 1] != 0))
                                          { 
                                                      bian_line[H * 2] = W;
                                                      break;
                                          } 
                                          else
                                          { 
                                                      if((W == 1) && (ImageBuffer[H][W] != 0))
                                                      { 
                                                                bian_line[H * 2] = 0;
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
                            center_line[H].y = H; 
 
                            /*以下是防止卡死的操作(祖传操作，经检验没啥有)*/
                            if (point != 0) 
                            { 
                                      if(ImageBuffer[H][point] == 0)
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
                                                           }
                                                           point = center_line[56].x;
                                                           break;
                                                 }
                                      } 
                            } 
 
                            /*以下是非十字处理*/
                            if (shi_flag == 0) 
                            {  
                                      if( right_lost == 0) //右边没丢线
                                      { 
                                                for(W = point; W < 80; W++) //向右扫描
                                                { 
                                                            if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W-1]) != 0) 
                                                            { 
                                                                      bian_line[H * 2 + 1] = W;
                                                                      break;
                                                             } 
                                                             else 
                                                            {
                                                                      if((W == 79) && (ImageBuffer[H][W] != 0)) 
                                                                      { 
                                                                              bian_line[H * 2 + 1] = 79;
                                                                              break;
                                                                       } 
                                                             } 
                                                } 
                                               
                                                if((h_left_lost == 0) && (left_lost == 1) && (bian_line[H * 2 + 1] - bian_line[H * 2 + 3] > 0) )
                                                { 
                                                            bian_line[H * 2 + 1] = 79;
                                                            shi_flag = 1;
                                                } 
                                      } 
                                      else
                                      {
                                                  bian_line[H * 2 + 1] = 79; 
                                      }

                                      if(left_lost == 0)//左边没丢线
                                      {
                                                for(W = point; W > 0; W--)
                                                {
                                                            if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W + 1]) != 0)                                       
                                                            {  
                                                                      bian_line[H * 2] = W;
                                                                      break;
                                                             }
                                                             else                                                                      
                                                            {
                                                                      if((W == 1) && (ImageBuffer[H][W] != 0))
                                                                      {
                                                                              bian_line[H * 2] = 0;
                                                                              break;
                                                                       }
                                                             }
                                                  }
                                                if((right_lost == 1) && (bian_line[H * 2] - bian_line[H * 2 + 2] < 0) && (h_right_lost == 0))
                                                { 
                                                            bian_line[H * 2] = 0;
                                                            shi_flag = 1;
                                                 }
                                       }
                                      else
                                      {
                                                  bian_line[H * 2] = 0;
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
                                                 if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W - 1]) != 0)                                       
                                                 {  
                                                            bian_line[H * 2 + 1] = W;
                                                            break;
                                                 }
                                                 else                                                                      
                                                 {
                                                            if((W == 79) && (ImageBuffer[H][W] != 0))
                                                            {
                                                                       bian_line[H * 2 + 1] = 79;
                                                                       break;
                                                             }
                                                  }
                                       }
                                      
                                      for(W = point; W > 0; W--)
                                      {
                                                if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W + 1]) != 0)                                       
                                                {  
                                                          bian_line[H * 2] = W;
                                                          break;
                                                }
                                                else                                                                      
                                                {
                                                           if((W == 1) && (ImageBuffer[H][W] != 0))
                                                           {
                                                                    bian_line[H * 2] = 0;
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
                                      for(i = H + 8; i > (H - 5); i--)
                                      {
                                                if(za_flag_r == 1)
                                                { 
                                                          center_line[i].x = (uint8_t)(center_line[i + 1].x - 2); 
                                                          if(center_line[i].x < 1)
                                                          { 
                                                                    center_line[i].x = 1;
                                                          } 
                                                } 
                                                if(za_flag_l == 1)
                                                { 
                                                          center_line[i].x = (uint8_t)(center_line[i + 1].x + 2); 
                                                          if(center_line[i].x > 78)
                                                          { 
                                                                    center_line[i].x = 78; 
                                                          } 
                                                 } 
                                                bian_line[i * 2] = 0;
                                                bian_line[i * 2 + 1] = 79;
                                      }
                                      for(i = (H - 5); i > 0; i--)
                                      {
                                                center_line[i].x = 0; 
                                                bian_line[i * 2] = 0;
                                                bian_line[i * 2 + 1] = 79;
                                      }
                                      point = center_line[56].x;
                                      break; 
                             }
 
/////////////////////////////////////////////以下确定是环岛后的进环处理 
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
                                                                        if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W - 1]) != 0)                                       
                                                                        { 
                                                                                bian_line[H * 2 + 1] = W; 
                                                                                break; 
                                                                        } 
                                                                        else 
                                                                        { 
                                                                                 if((W == 79) && (ImageBuffer[H][W] != 0)) 
                                                                                 { 
                                                                                        bian_line[H * 2 + 1] = 79; 
                                                                                        break; 
                                                                                 } 
                                                                        } 
                                                              } 
                                                              center_line[H].x = bian_line[H * 2 + 1] - distence2[H] + 2; 
                                                  } 

                                                  if (assist_ADD == 1 && h_left_lost == 1 && h_right_lost == 0 ) 
                                                  { 
                                                              assist1 = 1; 
                                                              assist0 = 0;
                                                              for (W = point; W < 80; W++) 
                                                              { 
                                                                          if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W - 1]) != 0) 
                                                                          { 
                                                                                      bian_line[H * 2 + 1] = W; 
                                                                                      break; 
                                                                           } 
                                                                           else 
                                                                           {
                                                                                      if((W == 79) && (ImageBuffer[H][W] != 0)) 
                                                                                      { 
                                                                                                   bian_line[H * 2 + 1] = 79; 
                                                                                                   break; 
                                                                                       } 
                                                                           } 
                                                                } 
                                                              center_line[H].x = bian_line[H * 2 + 1] - distence2[H];  
                                                   } 

                                                  if (h_left_lost == 0 && assist1 == 1) 
                                                  { 
                                                              assist_ADD = 0;
                                                              for(W = point; W > 0; W--) 
                                                              { 
                                                                          if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W + 1] != 0))
                                                                          { 
                                                                                    bian_line[H * 2] = W;
                                                                                    break;
                                                                           } 
                                                                           else
                                                                           {
                                                                                     if((W == 1) && (ImageBuffer[H][W] != 0))
                                                                                     {
                                                                                               bian_line[H * 2] = 0;
                                                                                     } 
                                                                            } 
                                                               } 

                                                              center_line[H].x = bian_line[H * 2] + distence2[H];  

                                                              if (h_left_lost == 0 && h_right_lost == 1) 
                                                              {                         
                                                                          assist2 = 1;
                                                              } 
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
                                                                          if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W + 1] != 0)) 
                                                                          { 
                                                                                    bian_line[H * 2] = W;
                                                                                    break;
                                                                           } 
                                                                          else
                                                                          { 
                                                                                     if((W == 1) && (ImageBuffer[H][W] != 0))
                                                                                     { 
                                                                                               bian_line[H * 2] = 0;
                                                                                     } 
                                                                            }  
                                                              } 
                                                              center_line[H].x = bian_line[H * 2] + distence2[H]; 
                                                  } 
 
                                                  if (assist_rADD == 1 && h_right_lost == 1 && h_left_lost == 0 ) 
                                                  { 
                                                              assistr1 = 1; 
                                                              assistr0 = 0;
                                                              for(W = point; W > 0; W--) //向左扫描
                                                              { 
                                                                          if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W + 1] != 0))
                                                                          { 
                                                                                    bian_line[H * 2] = W;
                                                                                    break;
                                                                           } 
                                                                           else
                                                                           {
                                                                                     if((W == 1) && (ImageBuffer[H][W] != 0))
                                                                                     {
                                                                                               bian_line[H * 2] = 0;
                                                                                     } 
                                                                            } 
                                                               } 
                                                              center_line[H].x = bian_line[H * 2] + distence2[H]; 
                                                  }
                                    
                                                  if (h_right_lost == 0 && assistr1 == 1) 
                                                  { 
                                                              assist_rADD = 0;
                                                              for (W = point; W < 80; W++) //向右扫描
                                                              { 
                                                                        if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W - 1]) != 0)                                       
                                                                        { 
                                                                                bian_line[H * 2 + 1] = W; 
                                                                                break; 
                                                                        } 
                                                                        else 
                                                                        { 
                                                                                 if((W == 79) && (ImageBuffer[H][W] != 0)) 
                                                                                 { 
                                                                                        bian_line[H * 2 + 1] = 79; 
                                                                                        break; 
                                                                                 } 
                                                                        } 
                                                              } 
                                                              
                                                              center_line[H].x = bian_line[H * 2 + 1] - distence2[H]; 

                                                              if (h_right_lost == 0 && h_left_lost == 1) 
                                                              { 
                                                                          assistr2 = 1;
                                                              } 
                                                  }
                                       } 
                            } 
 
/////////////////////////////////////////////出左环岛检测 点C0灯
                            if((assist3==1 && OutRingFind_Flag==1 && center_line[33].x == 0))
                            { 
                                        assist3 = 0; 
                                        assist4 = 1; 
                                        OutRingFind_Flag=0;
                                        GPIO_WritePinOutput(GPIOC,0,0); 
                            } 
/////////////////////////////////////////////完全进左环岛检测 点C0灯

                                                        
/////////////////////////////////////////////出右环岛检测 
                            if((assistr3==1 && OutRingFind_Flag==1 && center_line[33].x == 0))
                            { 
                                        assistr3 = 0; 
                                        assistr4 = 1; 
                                        OutRingFind_Flag = 0;
                                        GPIO_WritePinOutput(GPIOC,0,0); 
                            } 
/////////////////////////////////////////////////////完全进右环岛检测 

 
/////////////////////////////////////////////////////开始出左环岛 
                            if (assist4 == 1) 
                            { 
                                      shi_flag = 0; 
                                      for(W = point; W > 0; W--) 
                                      { 
                                                   if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W + 1] != 0))
                                                   { 
                                                               bian_line[H * 2] = W;
                                                               break;
                                                   } 
                                                   else
                                                   { 
                                                               if((W == 1) && (ImageBuffer[H][W] != 0))
                                                               { 
                                                                          bian_line[H * 2] = 0;
                                                               } 
                                                   } 
                                      } 
                                      if(bian_line[H*2]>1) 
                                                center_line[H].x = bian_line[H * 2] + distence2[H] - 5;
                                      else 
                                                center_line[H].x = 15;
                            } 
/////////////////////////////////////////////////////开始出左环岛 
 
 
 
//////////////////////////////////////////////////////开始出右环岛 
                            if (assistr4 == 1) 
                            { 
                                      shi_flag = 0; 
                                      for (W = point; W < 80; W++) 
                                      { 
                                                 if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W - 1]) != 0) 
                                                 { 
                                                               bian_line[H * 2 + 1] = W; 
                                                               break; 
                                                 } 
                                                 else 
                                                 { 
                                                                if((W == 79) && (ImageBuffer[H][W] != 0)) 
                                                                { 
                                                                             bian_line[H * 2 + 1] = 79; 
                                                                             break; 
                                                                } 
                                                  } 
                                      } 
                                      center_line[H].x = bian_line[H * 2 + 1] - distence2[H] + 3;
                                      if(bian_line[H * 2 + 1] > 78) center_line[H].x = 63;
                            } 
 
//////////////////////////////////////////////////////开始出右环岛 

 
////////////////////////////////////////////识别到出环口就靠右边补直线出去 
                            if (assist5 == 1) 
                            { 
                                          for (W = point; W < 80; W++)
                                          { 
                                                    if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W - 1]) != 0)                                       
                                                    { 
                                                              bian_line[H * 2 + 1] = W; 
                                                              break; 
                                                    } 
                                                    else 
                                                    { 
                                                              if((W == 79) && (ImageBuffer[H][W] != 0)) 
                                                              { 
                                                                        bian_line[H * 2 + 1] = 79; 
                                                                        break; 
                                                              } 
                                                     } 
                                          } 
                                          center_line[H].x = bian_line[H * 2 + 1] - distence2[H];
                            } 
////////////////////////////////////////////识别到出环口就靠右边补直线出去 

 
/////////////////////////////////////////出右环岛识别到出环口就靠左边补直线出去 
                            if (assistr5 == 1)
                            { 
                                          for(W = point; W > 0; W--) 
                                          { 
                                                        if((ImageBuffer[H][W] == 0) && (ImageBuffer[H][W + 1] != 0))
                                                        { 
                                                                         bian_line[H * 2] = W;
                                                                         break;
                                                        } 
                                                        else
                                                        {
                                                                         if((W == 1) && (ImageBuffer[H][W] != 0))
                                                                         {
                                                                                    bian_line[H * 2] = 0;
                                                                          } 
                                                         } 
                                          } 
                                          center_line[H].x = bian_line[H * 2] + distence2[H];
                            } 
/////////////////////////////////////////出右环岛识别到出环口就靠左边补直线出去 

 
                            if (H == 1) 
                            { 
                                  point = center_line[56].x; 
                            } 
 
                            /*中线限幅*/
                            if ((center_line[H].x < 0) || (center_line[H].x > 79)) 
                            { 
                                        for(i = H; i > 0; i--)
                                        { 
                                                    center_line[i].x = 0;
                                                    bian_line[i * 2] = 0;
                                                    bian_line[i * 2 + 1] = 79;
                                        } 
                                        point = center_line[56].x;
                                        break;
                           }
                  } 
 
 
///////////////////////////左环岛assist3准确置一法/////////////////////////////////////点A17
                  if (assist2 == 1 && StreetCalWdith1 > 39) //50行右边点
                  { 
                            assist_ADD2 = 1; 
                  } 
                  if (assist2 == 1 && assist_ADD2 ==1 && StreetCalWdith1 < 38)//50行右边点
                  { 
                            assist3 = 1; 
                            TempError = CurrentError;//////偏差来区分环岛大小
                            assist1 = 0; 
                            assist_ADD2 = 0; 
                            assist2 = 0; 
                            Ring_Find_Flag = 0;
                            GPIO_WritePinOutput(GPIOA,17,0); 
                  } 
///////////////////////////左环岛assist3准确置一法/////////////////////////////////////点A17
 
 
 
//////////////////////////右环岛assistr3准确置一法 点A17
                  if (assistr2 == 1 && StreetCalWdith3 > 39) //50行左边点
                  { 
                            assist_ADDr2 = 1; 
                  } 
                  if (assistr2 == 1 && assist_ADDr2 == 1 && StreetCalWdith3 < 38)//50行左边点
                  { 
                            assistr3 = 1; 
                            assistr1 = 0; 
                            assist_ADDr2 = 0; 
                            assistr2 = 0; 
                            Ring_Find_Flag = 0;
                            GPIO_WritePinOutput(GPIOA,17,0); 
                  } 
//////////////////////////右环岛assistr3准确置一法 点A17

 
/////////////////////出左环岛口准确识别 点C0
                  if ((StreetCalLong > 38 && assist3==1) 
                       || (center_line[32].x == 0 && center_line[35].x == 0 
                           && center_line[38].x == 0 && center_line[41].x == 0
                           && center_line[44].x == 0 && assist3 == 1))
                  { 
                            OutRingFind_Flag = 1; 
                  } 
/////////////////////出左环岛口准确识别 点C0
                  
                      
/////////////////////出右环岛口准确识别 点C0
                  if ((StreetCalLong > 38 && assistr3 == 1) 
                       || (center_line[32].x == 0 && center_line[35].x == 0 
                           && center_line[38].x == 0 && center_line[41].x == 0
                           && center_line[44].x == 0 && assistr3 == 1))
                  { 
                            OutRingFind_Flag = 1; 
                  } 
/////////////////////出右环岛口准确识别 点C0 
                  
                     
                  
//////////////////以下是出左环岛要补直线出去检测 点D15 
                  if (assist4 == 1 && StreetCalWdith1 == 40)////50行右边 
                  { 
                                 assist_ADD1 = 1; 
                  } 
 
                  if (assist_ADD1 == 1 && assist4 == 1 && StreetCalWdith1 < 38) 
                  { 
                                 assist5 = 1; 
                                 assist4 = 0; 
                                 assist_ADD1 = 0; 
                                 GPIO_WritePinOutput(GPIOD,15,0); 
                  } 
//////////////////以下是出左环岛要补直线出去检测 点D15 
 
 
 
 
//////////////////以下是出右环岛要补直线出去检测 点D15
                  if (assistr4 == 1 && StreetCalWdith3 == 40)////50行左边
                  { 
                                 assist_ADDr1 = 1;
                  } 
 
                  if (assist_ADDr1 == 1 && StreetCalWdith3 < 38 && assistr4 == 1)
                  { 
                                 assistr5 = 1; 
                                 assistr4 = 0; 
                                 assist_ADDr1 = 0; 
                                 GPIO_WritePinOutput(GPIOD,15,0); 
                  } 
//////////////////以下是出右环岛要补直线出去检测 点D15
 
 
 
/////////////////////在将要出左环岛时将标志位清除 清灯 
                  if (StreetCalWdith6>39  && StreetCalWdith3>39 && assist5==1) ////6第53行有黑点左边,3第50行有黑点在左边
                  { 
                          assist_ADD3 = 1; 
                  } 
                  if (assist_ADD3==1 && StreetCalWdith6<30 && StreetCalWdith3<30 
                      && assist5==1 && h_left_lost==0) 
                  { 
                           assist5 = 0;
                           assist_ADD3 = 0;
                           LeftRing_Find_Flag = 0;
                           GPIO_WritePinOutput(GPIOE,29,1); 
                           GPIO_WritePinOutput(GPIOA,17,1); 
                           GPIO_WritePinOutput(GPIOC, 0,1); 
                           GPIO_WritePinOutput(GPIOD,15,1); 
                  } 
/////////////////////在将要出左环岛时将标志位清除 清灯

 
 
 
/////////////////////在将要出右环岛时将标志位清除 清灯
                  if (StreetCalWdith8>39 && StreetCalWdith1>39 && assistr5==1) //8第53行有黑点右边
                  { 
                          assist_ADDr3 = 1; 
                  } 
                  if (assist_ADDr3==1 && StreetCalWdith8<30 && StreetCalWdith1<30 
                      && assistr5==1 && h_right_lost==0)  
                  { 
                           assistr5 = 0;
                           assist_ADDr3 = 0;
                           RightRing_Find_Flag = 0;
                           GPIO_WritePinOutput(GPIOE,29,1); 
                           GPIO_WritePinOutput(GPIOA,17,1); 
                           GPIO_WritePinOutput(GPIOC, 0,1); 
                           GPIO_WritePinOutput(GPIOD,15,1); 
                  } 
/////////////////////在将要出右环岛时将标志位清除 清灯
                   
                  
  
///////////////////////////////以下是环岛检测 点E29
                  if (Ring_Find_Flag == 0  && LeftRing_Find_Flag==0) 
                  { 
                              for(Ring_Line_Value = 48; Ring_Line_Value > 28; Ring_Line_Value-- ) 
                              { 
                                             if(       assist5 ==0 //防止出环岛前重入
                                                       && h_left_lost == 0 && h_right_lost == 0 
                                                       && left_lost == 1 && right_lost == 0 

                                                       && (bian_line[Ring_Line_Value * 2] < 2) 
                                                       && (bian_line[Ring_Line_Value * 2 + 6] >  2) 
 
                                                       && (bian_line[Ring_Line_Value * 2 - 3] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 - 5] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 - 7] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 + 1] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 + 7] < 78) 
 
                                                       && (abs(bian_line[Ring_Line_Value * 2 + 6] - bian_line[Ring_Line_Value * 2]) > 15) 
                                                       && (abs(bian_line[Ring_Line_Value * 2 + 7] - bian_line[Ring_Line_Value * 2 + 1]) < 5) 
                                                       && (StreetCalWdith < 40) && (StreetCalWdith5 < 38)&& (StreetCalWdith4 > 30)//20,30行右，35行左
                                                       && (bian_line[49] < 78) && StreetCalLong > 35 
                                                ) 
                                             { 
                                                            assist0 = 1; 
                                                            Ring_Find_Flag = 1; 
                                                            LeftRing_Find_Flag = 1; 
                                                            StartLineFind_Flag = 1; 
                                                            GPIO_WritePinOutput(GPIOE,29,0);//点灯指示 
                                             } 
                                             if(       assistr5 ==0  //&& //S == 0//防止出环岛前重入 
                                                       && h_right_lost == 0 && h_left_lost == 0 
                                                       && right_lost == 1 && left_lost == 0 
                                                         
                                                       && (bian_line[Ring_Line_Value * 2 + 1] > 78) 
                                                       && (bian_line[Ring_Line_Value * 2 + 7] < 78) 
                                                         
                                                       && (bian_line[Ring_Line_Value * 2 - 4] > 1) 
                                                       && (bian_line[Ring_Line_Value * 2 - 6] > 1) 
                                                       && (bian_line[Ring_Line_Value * 2 - 8] > 1) 
                                                       && (bian_line[Ring_Line_Value * 2] > 1) 
                                                       && (bian_line[Ring_Line_Value * 2 + 8] > 1) 
                                                         
                                                       && (abs(bian_line[Ring_Line_Value * 2 + 6] - bian_line[Ring_Line_Value * 2]) < 5) 
                                                       && (bian_line[58] > 15 && bian_line[60] > 15) 
                                                       && (bian_line[62] > 15 && bian_line[64] > 15 && bian_line[66] > 15) 
                                                       && (bian_line[68] > 15 && bian_line[70] > 15 && bian_line[72] > 15) 
                                                       && (bian_line[74] > 15 && bian_line[76] > 15 && bian_line[78] > 15) 
                                                       && (abs(bian_line[64] - bian_line[78]) < 5) 
                                                       && (bian_line[119] < 78) 
                                                       && (StreetCalWdith2 > 33 && StreetCalWdith4 > 7) 
                                               ) 
                                             { 
                                                        assistr0 = 1; 
                                                        Ring_Find_Flag = 1; 
                                                        RightRing_Find_Flag = 1;                                                       
                                                        StartLineFind_Flag = 1; 
                                                        GPIO_WritePinOutput(GPIOE,29,0);//点灯指示 
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
                  ave_center = sum_center / num_ave; 
                  sum_center = 0; 
                  num_ave = 0; 
}


char User_Stop_Line_JianCe(void)
{
        unsigned char x,y;
        char i = 0;
        if (StartLineFind_Flag == 1)
        {  
              for(y = 44; y < 60; y++)
              { 
                    for(x = 11; x < 72; x++ )
                    {
                          if((ImageBuffer[y][x]==0)&&(ImageBuffer[y][x+1]!=0))
                          { 
                                x+=3;
                                for(;x < 72; x++)
                                {
                                      if((ImageBuffer[y][x]!=0)&&(ImageBuffer[y][x+1]==0))   
                                      {
                                            for(;x < 72; x++)
                                            {
                                                  if((ImageBuffer[y][x]==0)&&(ImageBuffer[y][x+1]!=0)) //两个
                                                  {
                                                        x+=3;
                                                        for(;x < 72; x++)
                                                        {
                                                              if((ImageBuffer[y][x]!=0)&&(ImageBuffer[y][x+1]==0))
                                                              {
                                                                    for(;x < 72; x++)
                                                                    {
                                                                          if((ImageBuffer[y][x]==0)&&(ImageBuffer[y][x+1]!=0)) //三个
                                                                          {
                                                                                x+=3;
                                                                                for(;x < 72; x++)
                                                                                {                            
                                                                                      if((ImageBuffer[y][x]!=0)&&(ImageBuffer[y][x+1]==0))
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