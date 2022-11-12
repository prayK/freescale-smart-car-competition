#include  "common.h"
#include  "include.h"
#include  "common.h"
#include  "ImageInformation.h"
#include  "math.h"

/********************寻线，识别,补线变量*******************/
uint8  StartLineFind_Flag = 0; //开始进行起跑线识别标志位
uint8  Ring_Find_Flag = 0; 
uint8  LeftRing_Find_Flag = 0; 
uint8  RightRing_Find_Flag = 0; 
uint8  Ring_Line_Value = 0; //环岛识别标志位 
uint8  ErrorRecord = 0; 
extern uint8 ave_center;
extern uint8 OutRingFind_Flag;

uint8  assist0 = 0; 
uint8  assist1 = 0; 
uint8  assist2 = 0; 
uint8  assist3 = 0; 
uint8  assist4 = 0; 
uint8  assist5 = 0; 
uint8  assist6 = 0; 
uint8  assist_ADD = 0;/////////左环岛标志位 

uint8  assistr0 = 0; 
uint8  assistr1 = 0; 
uint8  assistr2 = 0; 
uint8  assistr3 = 0; 
uint8  assistr4 = 0; 
uint8  assistr5 = 0; 
uint8  assistr6 = 0; 
uint8  assist_rADD = 0;/////////右环岛标志位 

float Left_Cur_K=0; //左圆环补线斜率
float Right_Cur_K=0; //右圆环补线斜率
uint16 Site_Y=0,StreetLong = 0;

uint8  H, W,i,j,l,P; 

uint8  point = 40;

uint32  sum_center = 0; 
uint8   num_ave = 0;
uint8   ave_center = 40;


uint8_t left_lost = 0, 
        right_lost = 0,
        h_left_lost = 0,
        h_right_lost = 0;

uint8  za_flag_r = 0, 
       za_flag_l = 0, 
       za_flag = 0,
       zhangai = 0,
       shi_flag = 0; 

uint8  tubian_num = 0, 
       tubian_num_H = 0; 

uint8  imgbuff[CAMERA_SIZE]; 
uint8  img[60][CAMERA_W]; 

uint8  bian_line[120]; 
Site_t center_line[60]; 
Site_t sit_L[60]; 
Site_t sit_R[60]; 
 
uint8 RealWidth[60]={ 
                          8,8,9,10,12,12,14,14,15,16,
                          18,18,20,21,22,23,24,25,26,
                          27,28,29,30,31,32,32,33,34,35,
                          36,36,38,38,39,40,40,41,42,43,
                          44,44,45,46,47,48,50,51,51,52,
                          53,54,54,55,56,57,58,59,60,61,62
                     };

uint8 distence[61] = {   
                          0, 4, 4, 4, 5, 5, 5, 5, 5, 6,
                          6, 6, 7, 7, 7, 8, 8, 8, 9, 9,
                         10,10, 11,11,12,12,13,13,14,14,
                         15,15, 16,16,17,18,18,19,19,20,
                         20,21, 22,22,23,23,24,24,25,25,
                         26,27, 27,28,29,29,30,30,31,31,32
                     };

uint8 distence2[61] = {   
                          0, 4, 4, 4, 5, 5, 5, 5, 5, 6, 
                          6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 
                         10,10, 11,11,12,12,13,13,14,14, 
                         15,15, 16,16,17,18,18,19,19,20, 
                         20,21, 22,22,23,23,24,24,25,25,
                         26,27, 27,28,29,29,30,30,31,31,32
                     };

uint8 NeedLine[60] = { 
                         20,  21,  22,  23,  24,  25,  26,  27,  28,  30, 
                         32,  34,  36,  38,  40,  42,  44,  46,  48,  50,
                         53,  56,  59,  62,  65,  68,  71,  74,  77,  80,
                         84,  88,  92,  96, 100, 104, 108, 112, 116, 120,
                        125, 130, 135, 140, 145, 150, 155, 160, 165, 170,
                        176, 182, 188, 194, 200, 206, 212, 218, 224, 230
                     };

/////注意0是黑色，非零是白色
void ImageIdentification(void)
{ 
                  camera_get_img();
                  StreetRealize();//赛道类型识别
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
                                      if( right_lost == 0) //右边没丢线
                                      { 
                                                for(W = point; W < 80; W++) //向右扫描
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
                                               
                                                if((h_left_lost == 0) && (left_lost == 1) && (bian_line[H * 2 + 1] - bian_line[H * 2 + 3] > 0) )
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

                                      if(left_lost == 0)//左边没丢线
                                      {
                                                for(W = point; W > 0; W--)
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
                                                if((right_lost == 1) && (bian_line[H * 2] - bian_line[H * 2 + 2] < 0) && (h_right_lost == 0))
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
                                      for(i = H + 8; i > (H - 5); i--)
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
                                      for(i = (H - 5); i > 0; i--)
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
                                                              
                                                              center_line[H].x = bian_line[H * 2 + 1] - distence2[H]; 
                                                  } 

                                                  if (assist_ADD == 1 && h_left_lost == 1 && h_right_lost == 0 ) 
                                                  { 
                                                              assist1 = 1; 
                                                              assist0 = 0;
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
 
                                                              center_line[H].x = bian_line[H * 2 + 1] - distence2[H] + 2;  
                                                   }

                                                  if (h_left_lost == 0 && assist1 == 1) 
                                                  { 
                                                              assist_ADD = 0;
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

                                                              center_line[H].x = bian_line[H * 2] + distence2[H] + 3;  
                                                              if(H < 35)
                                                              { 
                                                                          for(l = 0; l < 5; l++)
                                                                          { 
                                                                                    center_line[H + l].x = 22; 
                                                                          } 
                                                              } 
 
                                                              if (h_left_lost == 0 && h_right_lost == 1) 
                                                              {                         
                                                                          assist2 = 1;
                                                              } 
                                                  } 

                                                  if(assist2 == 1 && h_left_lost == 0 && h_right_lost == 0
                                                    ||(assist2 == 1 && bian_line[111] < 77 && bian_line[109] < 75 && bian_line[107] < 74)) 
                                                  { 
                                                                assist1 = 0; 
                                                                assist3 = 1; 
                                                                led(LED0, LED_ON); 
                                                  } 
 
                                                  /*在环内的巡线补线操作*/ 
                                                  if (assist3 == 1) 
                                                  { 
                                                              assist2 = 0;
                                                              ErrorRecord = ave_center;
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
 
                                                              if(((bian_line[H * 2] < 1) && (bian_line[H * 2 + 1] < 79)) 
                                                              || ((bian_line[H * 2] > 0) && (bian_line[H * 2 + 1] > 78))) 
                                                              { 
                                                                         if(bian_line[H * 2] < 1) 
                                                                         { 
                                                                                    if((bian_line[H * 2 + 1] - bian_line[H * 2 + 3]) > 1) 
                                                                                    { 
                                                                                              if(H < 45) 
                                                                                              { 
                                                                                                        for(l = 0; l < 5; l++) 
                                                                                                        { 
                                                                                                                center_line[H + l].x = RingInsideTurnValue;
                                                                                                        } 
                                                                                              } 
                                                                                              else
                                                                                                    center_line[H].x = center_line[H + 1].x; 
                                                                                    } 

                                                                                    else
                                                                                    {
                                                                                              if(H > 50)
                                                                                              {
                                                                                                       if(h_left_lost == 1) 
                                                                                                       { 
                                                                                                              center_line[H].x = bian_line[H * 2 + 1] - (bian_line[H * 2 + 3] - point) + distence2[H + 1]- distence2[H] + RingAddValue;  
                                                                                                       } 
                                                                                                         else  
                                                                                                              center_line[H].x = bian_line[H * 2 + 1] - (bian_line[H * 2 + 3] - point) - distence2[H + 1] + distence2[H] + RingAddValue;
                                                                                              }
                                                                                              else
                                                                                                   center_line[H].x = bian_line[H * 2 + 1] - (bian_line[H * 2 + 3] - point) - distence2[H + 1] + distence2[H] + RingAddValue;  
                                                                                     } 
                                                                         }

                                                                         if(bian_line[H * 2 + 1] > 78) 
                                                                         { 
                                                                                  if((bian_line[H * 2] - bian_line[H * 2 + 2]) < -1) 
                                                                                  { 
                                                                                          if(H < 45)
                                                                                          { 
                                                                                                  for(l = 0; l < 5; l++)
                                                                                                  { 
                                                                                                          center_line[H + l].x = RingInsideTurnValue; 
                                                                                                  } 
                                                                                          } 
                                                                                        
                                                                                          else
                                                                                               center_line[H].x = center_line[H + 1].x;
                                                                                  }
                                                                             
                                                                                  else 
                                                                                  { 
                                                                                           if(H > 50) 
                                                                                           { 
                                                                                                   if(h_right_lost == 1)
                                                                                                   { 
                                                                                                            center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] + distence2[H] - distence2[H + 1] + RingAddValue;
                                                                                                   } 
                                                                                                   else
                                                                                                   center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] - distence2[H] + distence2[H + 1] + RingAddValue;  
                                                                                           }
                                                                                          
                                                                                           else
                                                                                                center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] - distence2[H] + distence2[H + 1] + RingAddValue; 
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
                                                                                     if(( bian_line[H * 2] < 1 && bian_line[H * 2 + 1] > 78 && bian_line[111] < 77 
                                                                                        &&bian_line[109] < 75 && bian_line[107] < 74)
                                                                                     || OutRingFind_Flag == 1) 
                                                                                     { 
                                                                                               assist4 = 1; 
                                                                                               assist3 = 0;
                                                                                               gpio_set (PTA15, 1);
                                                                                     } 
                                                                                     else 
                                                                                               center_line[H].x = center_line[H + 1].x;      
                                                                          } 
                                                              } 
                                                  } 
                                      
                                                  if (assist5 == 1) 
                                                  { 
                                                          for (W = point; W < 80; W++)
                                                          { 
                                                                           sit_R[H].y = H; 
                                                                           if((img[H][W] == 0) && (img[H][W - 1]) != 0)                                       
                                                                           { 
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

                                                          center_line[H].x = bian_line[H * 2 + 1] - distence2[H] ;
                                                   } 

                                                  if (assist6 == 1 && h_right_lost == 0 && h_left_lost == 0)
                                                  { 
                                                                  assist6 = 0; 
                                                                  assist5 = 0; 
                                                                  gpio_set (PTA15, 0);
                                                                  Ring_Find_Flag = 0; 
                                                                  LeftRing_Find_Flag = 0; 
                                                   } 
                                       } 
                            }  
                 
                            /*以下是出左环岛操作*/
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

                                          if(((bian_line[H * 2] < 1) && (bian_line[H * 2 + 1] < 79)) 
                                          || ((bian_line[H * 2] > 0) && (bian_line[H * 2 + 1] > 78))
                                            ) 
                                          { 
                                                        if(bian_line[H * 2 + 1] > 78)//右边丢线，左边不丢线
                                                        { 
                                                                       if((bian_line[H * 2] - bian_line[H * 2 + 2]) < -1)
                                                                       { 
                                                                                       center_line[H].x = RingOutsideTurnValue;//
                                                                        } 
 
                                                                       else 
                                                                       { 
                                                                                    if(H > 50) 
                                                                                    { 
                                                                                                 if(h_right_lost == 1) 
                                                                                                 { 
                                                                                                          center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] + distence2[H] - distence2[H + 1] ;  
                                                                                                 } 
                                                                                                 
                                                                                                 else
                                                                                                          center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] - distence2[H] + distence2[H + 1] ;
                                                                                    } 
                                                                                    
                                                                                    else
                                                                                                center_line[H].x = point - bian_line[H * 2 + 2] + bian_line[H * 2] - distence2[H] + distence2[H + 1] ; 
                                                                        } 
                                                        } 
                                            }
                                         
                                          else 
                                          { 
                                                          
                                                         if((bian_line[H * 2] > 0) && (bian_line[H * 2 + 1] < 79)) 
                                                         {
                                                                        center_line[H].x = (bian_line[H * 2] + bian_line[H * 2 + 1]) / 2;//减2
                                                         }
                                                        
                                                         else 
                                                         { 
                                                                        if((bian_line[H * 2] < 1) && (bian_line[H * 2 + 1] > 78))
                                                                        {
                                                                                     for(l = 0; l < 5; l++)
                                                                                     {
                                                                                                  center_line[H + l].x = RingOutsideTurnValue; 
                                                                                      } 
                                                                                      center_line[H].x = center_line[H + 1].x;
                                                                        } 
                                                                        else
                                                                                      center_line[H].x = center_line[H + 1].x;  
                                                          }
                                            }
                                          
                                          if ( center_line[H].x == 0 && center_line[H+1].x == 0 && center_line[H+2].x !=0 )
                                          {
                                           
                                                  center_line[H+1].x = center_line[H+2].x - 1;
                                          }
                            } 

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
                                                    sit_R[i].x = 79;
                                                    sit_L[i].x = 0;
                                        }
                                        point = center_line[56].x;
                                        break;
                           }
                  } 
 
                  /*以下是出环岛检测*/
                  if ( assist4 == 1
                       &&(bian_line[H * 2 + 5] < 70 && bian_line[H * 2 + 3] < 70 
                       && bian_line[H * 2 + 7] < 70 && bian_line[H * 2 + 9] < 70) 
                       &&(abs( bian_line[H * 2 + 5] - bian_line[H * 2 + 3] ) < 3
                       && abs( bian_line[H * 2 + 7] - bian_line[H * 2 + 5] ) < 3
                       && abs( bian_line[H * 2 + 9] - bian_line[H * 2 + 7] ) < 3
                       && abs( bian_line[H * 2 + 9] - bian_line[H * 2 + 5] ) < 3
                       && abs( bian_line[H * 2 + 9] - bian_line[H * 2 + 3] ) < 4) 
                      ) 
                  { 
                               assist5 = 1; 
                               assist4 = 0; 
                   } 

                  /*注意，要写在这找标志位6,补直线出去*/
                  if ( assist5 == 1 && h_right_lost == 0 && h_left_lost == 1)
                  { 
                               assist6 = 1;
                               assist5 = 0; 
                  } 
 
                  /*以下是环岛检测*/
                  if (Ring_Find_Flag == 0) 
                  { 
                              for(Ring_Line_Value = 48; Ring_Line_Value > 28; Ring_Line_Value-- ) 
                              { 
                                           if( 
                                                          h_left_lost == 0 && h_right_lost == 0 && left_lost == 1 && right_lost == 0 

                                                       && (bian_line[Ring_Line_Value * 2] < 1) 
                                                       && (bian_line[Ring_Line_Value * 2 + 6] >  1) 
 
                                                       && (bian_line[Ring_Line_Value * 2 - 3] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 - 5] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 - 7] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 + 1] < 78) 
                                                       && (bian_line[Ring_Line_Value * 2 + 7] < 78) 
 
                                                       && ((bian_line[Ring_Line_Value * 2 + 6] - bian_line[Ring_Line_Value * 2]) > 20) 
                                                       && ((bian_line[Ring_Line_Value * 2 + 7] - bian_line[Ring_Line_Value * 2 + 1]) < 3) 
                                            ) 
                                            { 
                                                        Ring_Find_Flag = 1; 
                                                        LeftRing_Find_Flag = 1; 
                                                        StartLineFind_Flag = 1;//找到一个环岛后开始进行停车线扫描
                                                        assist0 = 1; 
                                            }//左环岛识别 
 
//                                            if( 
//                                                          h_right_lost == 0 && h_left_lost == 0 && right_lost == 1 && left_lost == 0
//
//                                                       && (bian_line[Ring_Line_Value * 2 + 1] > 78) 
//                                                       && (bian_line[Ring_Line_Value * 2 + 7] < 78) 
// 
//                                                       && (bian_line[Ring_Line_Value * 2 + 2] > 1)
//                                                       && (bian_line[Ring_Line_Value * 2 + 4] > 1) 
//                                                       && (bian_line[Ring_Line_Value * 2 + 6] > 1) 
//                                                       && (bian_line[Ring_Line_Value * 2] > 1)
//                                                       && (bian_line[Ring_Line_Value * 2 + 8] > 1) 
// 
//                                                       && ((bian_line[Ring_Line_Value * 2 + 1] - bian_line[Ring_Line_Value * 2 + 7]) > 20) 
//                                                       && ((bian_line[Ring_Line_Value * 2 + 6] - bian_line[Ring_Line_Value * 2]) < 3) 
//                                            ) 
//                                            { 
//                                                        led(LED0, LED_ON); 
//                                                        Ring_Find_Flag = 1; 
//                                                        RightRing_Find_Flag = 1; 
//                                                        assistr0 = 1; 
//                                            }//右环岛识别
                              } 
                  } 

           #if(0) /*以下是标志位上位机检测*/
                  
                        printf("\n bian_line[115] ：%d",bian_line[115] );
                        printf("\n bian_line[113] ：%d",bian_line[113] ); 
                        printf("\n bian_line[111] ：%d",bian_line[111] );
                        printf("\n bian_line[109] ：%d",bian_line[109] );
                        printf("\n bian_line[107] ：%d",bian_line[107] );
                        printf("\n bian_line[105] ：%d",bian_line[105] );
                        printf("\n bian_line[103] ：%d",bian_line[103] );
                        
                        printf("\n bian_line[110] ：%d",bian_line[110] );
                        printf("\n bian_line[118] ：%d",bian_line[118] ); 
                        printf("\n bian_line[116] ：%d",bian_line[116] );
                        printf("\n bian_line[114] ：%d",bian_line[114] );
                        printf("\n bian_line[112] ：%d",bian_line[112] );
                        printf("\n bian_line[110] ：%d",bian_line[110] );
                        printf("\n bian_line[108] ：%d",bian_line[108] );
                        
                        
                        
                        printf("\n bian_line[H * 2 + 1] ：%d",bian_line[H * 2 + 1] );
                        printf("\n bian_line[H * 2 + 3] ：%d",bian_line[H * 2 + 3] ); 
                        printf("\n bian_line[H * 2 + 5] ：%d",bian_line[H * 2 + 5] );
                        printf("\n bian_line[H * 2 + 7] ：%d",bian_line[H * 2 + 7] );
                        printf("\n bian_line[H * 2 + 9] ：%d",bian_line[H * 2 + 9] );
                        
                        printf("\n bian_line[H * 2] ：%d",bian_line[H * 2] );
                        printf("\n bian_line[H * 2 - 2] ：%d",bian_line[H * 2 - 2] ); 
                        printf("\n bian_line[H * 2 - 4] ：%d",bian_line[H * 2 - 4] );
                        printf("\n bian_line[H * 2 - 6] ：%d",bian_line[H * 2 - 6] );
                        printf("\n bian_line[H * 2 - 8] ：%d",bian_line[H * 2 - 8] );

                        if (h_right_lost == 1) printf("\n h_right_lost ：%d",1 );
                        if (h_left_lost == 1) printf("\n h_left_lost ：%d",1 );
                        if (right_lost == 1) printf("\n right_lost ：%d",1 );
                        if (left_lost == 1) printf("\n left_lost ：%d",1 );
                        if (za_flag == 1) printf("\n za_flag ：%d",1 ); 
                        if (shi_flag == 1) printf("\n shi_flag ：%d",1 ); 
                        if (Ring_Find_Flag == 1) printf("\n Ring_Find_Flag ：%d",1 );
           #endif 
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
                          if((img[y][x]==0)&&(img[y][x+1]!=0))
                          { 
                                x+=3;
                                for(;x < 72; x++)
                                {
                                      if((img[y][x]!=0)&&(img[y][x+1]==0))   
                                      {
                                            for(;x < 72; x++)
                                            {
                                                  if((img[y][x]==0)&&(img[y][x+1]!=0)) //两个
                                                  {
                                                        x+=3;
                                                        for(;x < 72; x++)
                                                        {
                                                              if((img[y][x]!=0)&&(img[y][x+1]==0))
                                                              {
                                                                    for(;x < 72; x++)
                                                                    {
                                                                          if((img[y][x]==0)&&(img[y][x+1]!=0)) //三个
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

void StreetLongCal(void) 
{
        /*中线直道长度测量*/
        for(Site_Y=55; Site_Y>=1; Site_Y--) 
        { 
                if(img[Site_Y][40] == 0) break;
        } 
        StreetLong = 59 - Site_Y;
 
//        if(cur_R_real_delay_flag) 
//        {
//                /*右圆环切入点测量*/
//                for(Site_Y=55; Site_Y>=1; Site_Y--)
//                {
//                      if(img[Site_Y][Right_data[47]-3] == 0) break;
//                } 
//                Right_Cur_K = 10 * (Right_data[47]-35) / (59-Site_Y);
//        }
//        if(cur_L_real_delay_flag) 
//        {
//              /*左圆环切入点测量*/
//              for(Site_Y=55; Site_Y>=1; Site_Y--)
//              {
//                      if(img[Site_Y][Left_data[47]+3] == 0) break;
//              }
//              Left_Cur_K=10*(50-Left_data[47]) / (59-Site_Y);
//        }
}
