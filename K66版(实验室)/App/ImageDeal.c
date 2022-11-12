#include "common.h"
#include "include.h"
#include "ImageDeal.h"

extern  Site_t   center_line[60]; 
extern  Site_t   sit_L[60]; 
extern  Site_t   sit_R[60]; 
extern  uint32   sum_center; 
extern  uint8    num_ave;
extern  uint8    ave_center;
extern  uint8    bian_line[120]; 
uint8    R_max,L_min;
uint8    speed_ave;
uint16   bianbi_num;
float   bian_bi,bian_ca;
uint16   ave_center_s = 40;
uint8    line[60];
uint8    bian[120];
uint8    bianxin[60];
uint16   ave_S_num,S_num;

//#define       QZ_End      20   //前瞻最前面
//#define       QZ_Top      50   //前瞻最后面

/*固定权值加权算偏差*/
void UseTheWeightCountCenterlineAverage()
{ 
        //CenterLineLvBo();////先对中线滤波处理
        int i;
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
        bianbi_num = 0;
        R_max = 40;
        L_min = 40;
        for(i=0; i<60; i++) //中线加权平均值计算
        {
                  if((center_line[i].x>0) && (center_line[i].x<79)) //检测中线是否有效
                  {
                            if(center_line[i].x > R_max) //找到右边线最大值
                            {
                                    R_max = center_line[i].x;
                            }
                            if(center_line[i].x < L_min) //找到左边线最小值
                            {
                                    L_min = center_line[i].x;
                            }
                            
                            if(num_ave == 0)
                            {
                                    speed_ave = i; //扫描到第一行有效值得时候  记录下来
                            }
                            sum_center += center_line[i].x;
                            num_ave++;
                            if((i > speed_ave) && (i < speed_ave + (60 - speed_ave) / 2)) //只算前一半线的前瞻                                                      //加权 
                            {
                                    sum_center += center_line[i].x;
                                    sum_center += center_line[i].x;
                                    num_ave += 2;
                            }
                            bianbi_num++;
                  }
        }
        bian_bi = (float)bianbi_num / 60.0;

        if((1 - (float)(R_max - L_min) / 72.0) > 0)
        {
                  bian_ca = 1 - ((float)(R_max - L_min) / 72.0);
        }
        else   bian_ca = 0;
  
        ave_center_s = sum_center / num_ave;
        sum_center = 0;
        num_ave = 0;
       
        for(i=0; i<60; i++)
        { 
                line[i] = center_line[i].x;
        } 
        for(i=0; i<120; i++)
        { 
                bian[i] = bian_line[i];
        } 
        for(i=0; i<60; i++) //求边心数组
        { 
                bianxin[i] = (sit_R[i].x - sit_L[i].x) / 2;
        } 
        S_num = 0;
        ave_S_num = 0;
        for(i=59; i>40; i--) 
        {
           S_num += center_line[i].x;
        }
        ave_S_num = S_num / 19;
}

//extern assist1;
////针对环岛进行类型识别以搭配不同的参数
//void RingInsideDeal(void)
//{ 
//        if (assist1 == 1)//当已经向左环岛打角进入时进行环岛大小识别
//        {                 
//                if (
//                    bian_line[H * 2] 
//                    bian_line[H * 2 + 2] 
//                    bian_line[H * 2 + 4] //只取有效的三点进行弯曲度粗略计算
//                    )
//                {}
//        }
//} 


extern uint8  Ring_Find_Flag; 
extern uint8  LeftRing_Find_Flag;
extern uint8  RightRing_Find_Flag;
extern uint8  ave_center; 
extern uint8  shi_flag; 
extern uint8 LittleSFlag;
extern uint8 assist3;
extern uint8 assist4;
extern uint8 ErrorRecord;

float  ServoPValue[2] = {0.32, 930.5}; 
float  ServoPDValue[2] = {0.52, 1.5};
float  CenterValue; 
int8    CurrentError; 

uint8  OutRingFind_Flag = 0;

void StreetRealize(void)
{
         if (center_line[32].x == 0 && center_line[35].x == 0 
             &&center_line[38].x == 0 && center_line[41].x == 0
             &&center_line[44].x == 0 && assist3 == 1) 
          {
                   OutRingFind_Flag = 1;
                   led(LED1, LED_ON); 
          } 
}
   
/*静态P算法*/
float UseSticPValue()
{ 
          CenterValue = ServoCenterValue; 
          CurrentError = ave_center - 40; 
          return 1;
} 
uint8  UFlag = 0;
/*二次P算法*/
void UseLineValueChangePValue() 
{
          CenterValue = ServoCenterValue; 
//          if (assist4 == 1)
//                  CurrentError = ErrorRecord - 40; 
//          else
          CurrentError = ave_center - 40; 
          
          if ((LittleSFlag == 1) && (Ring_Find_Flag != 1)) //小S情况下给小P,直冲 
          { 
                   ServoPDValue[0] = 0.03; 
                   ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]); 
          } 
          if((UFlag == 1) && (Ring_Find_Flag != 1))
          {             
                   ServoPDValue[0] = 0.45; 
                   ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]); 
          }
          else
          ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]);
}

/*二次P加赛道类型识别分段P算法*/
float UseTwicePValue()
{
          CenterValue = ServoCenterValue;  
          CurrentError = ave_center - 40;
 
          if ((LittleSFlag == 1) && (Ring_Find_Flag != 1)) //小S情况下给小P,直冲 
          { 
                   ServoPDValue[0] = 0.03; 
                   return  ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]); 
          } 
 
          else if (assist3 == 1)//遇到环岛根据情况来修正P 
          { 
                   ServoPDValue[0] = 0.13; 
                   ServoPDValue[1] = 0; 
                   return ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]); 
          } 

          else if ((center_line[LittleEndLine].x < 38 && center_line[EndLine].x == 0) 
            &&(center_line[LittleTopLine].x != 0 && center_line[TopLine].x != 0) ///左转 
            &&(center_line[MiddleLine].x != 0) 
            &&(shi_flag != 1) 
            &&(Ring_Find_Flag != 1)) ///U型 
          { 
                   ServoPValue[0] = 0.46;
                   return ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]);
          } 

          else if ((center_line[LittleEndLine].x > 42 && center_line[EndLine].x == 0) 
            &&(center_line[LittleTopLine].x != 0 && center_line[TopLine].x != 0)///右转 
            &&(center_line[MiddleLine].x != 0)
            &&(shi_flag != 1) 
            &&(Ring_Find_Flag != 1))//U型 
          { 
                   ServoPValue[0] = 0.46;
                   return ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]);
          } 
         else///其他赛道 
         { 
              ServoPValue[0] = 0.25;
              return ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]);
         } 
}


/*边线滤波,理论函数效果未知*/
void AverageLvBo(void) 
{ 
        uint8 line;
        for(line=EndLine; line<TopLine; line++)
        { 
                    bian_line[line * 2 + 1] = (bian_line[line * 2 - 3] 
                                               + bian_line[line * 2 - 1] 
                                               + bian_line[line * 2 + 1]
                                               + bian_line[line * 2 + 3] 
                                               + bian_line[line * 2 + 5]
                                               ) / 5;

                    bian_line[line * 2] = (bian_line[line * 2 - 4]
                                           + bian_line[line * 2 -2]
                                           + bian_line[line * 2] 
                                           + bian_line[line * 2 + 2]
                                           + bian_line[line * 2 + 4]
                                           ) / 5;
        } 
} 


/*中线滤波,理论函数效果未知*/
void CenterLineLvBo(void) 
{ 
        uint8 line;
        for(line=0; line<60; line++)
        { 
                 if((center_line[line].x > 1) && (center_line[line].x < 78)) 
                 { 
                              center_line[line].x = (center_line[line - 1].x
                                                   + center_line[line - 2].x
                                                   + center_line[line].x
                                                   + center_line[line + 1].x
                                                   + center_line[line + 2].x
                                                   ) / 5;
                 } 
        } 
} 

/*中线滤波函数*/
//uchar Point_Average(void)
//{
//	uchar i, Half_Line;//
//	int32 Point, Sum = 0;
//	static uchar Last_Point = 40;//
//	
//	if (Out_Side || Line_Count >= 55) // 出界或者摄像头图像异常  //uchar Out_Side = 0; // 丢线控制 uchar Line_Count; // 记录成功识别到的赛道行数
//
//	{ 
//		Point  = Last_Point; // 使用上次目标点
//	} 
//	else
//	{ 
//		Half_Line = 59 - (59 - Line_Count) / 2; // 计算有效行的中间行
//		if (Half_Line % 2 == 0)
//		{ 
//			Half_Line += 1;
//		} 
//		if (Left_Max + 12 < Right_Min)
//		{ 
//			Point = (Left_Max + Right_Min) / 2;
//		} 
//		else
//		{ 
//			if (Line_Count <= 21) 
//			{  
//				Line_Count = 21;
//			}  
//			for (i = 61; i >= Line_Count; )
//			{
//				i -= 2;
//				Sum += Mid_Line[i];
//			}
//			Point = Sum / ((61-Line_Count)/2); // 对中线求平均
//			if (Left_Add_Line[Half_Line] >= 20) // 太偏左
//			{
//				Point += (Left_Add_Line[Half_Line]-20);	// 适当补偿
//			}
//			if (Right_Add_Line[Half_Line] <= 60) // 太偏右
//			{
//				Point -= (60-Right_Add_Line[Half_Line]); // 适当补偿
//			}
//		}
//		
//		Point = Point*0.9 + Last_Point*0.1; // 低通滤波
//		Point = range_protect(Point, 1, 79); // 限幅，防止补偿溢出
//		Last_Point = Point; // 更新上次目标点
//	}
//	return Point;
//}


/*线性回归方程计算斜率,理论函数效果未知*/
int B;

int regression(int startline,int endline)         
{
  if(endline>56)endline=56;
  int i;
  int sumX=0,sumY=0,avrX=0,avrY=0 ;
  int num=0,B_up1=0,B_up2=0,B_up,B_down;
  
  for(i=startline;i<=endline;i++)
  {
            num++;
            sumX+=i;
            sumY+=center_line[i].y;
   }
   avrX=sumX/num;
   avrY=sumY/num;
   B_up=0;
   B_down=0;
   for(i=startline;i<=endline;i++)
  {
            B_up1=(int)(center_line[i].y-avrY);
            B_up2=i-avrX;
            B_up+=(int)(10*(B_up1*B_up2));
            B_up=B_up/100*100;
            B_down+=(int)(10*((i-avrX)*(i-avrX)));
   }
   if(B_down==0)  B=0;
   else  B=B_up*16/B_down;//16
   return B;
}


/*动态加权算偏差,2018.6.13验证没通过*/
float weighting[33] = {   0.8, 0.9, 1.0, 1.1, 1.2,//24-28行的权重
                          1.8, 1.9, 2.0, 2.1, 2.2,//29到33行的权重
                          2.8, 2.9, 3.0, 3.1, 3.2,//34到38行的权重
                          3.8, 3.9, 4.0, 4.1, 4.2,//39到43行的权重 
                          4.8, 4.9, 5.0, 5.1, 5.2,//44到48行的权重 
                          5.8, 5.9, 6.0, 6.1, 6.2,//49到53行的权重 
                          4.9, 5, 5.1             //54到56行的权重 
                      };


float UseTheChangeableWeightCountCenterlineAverage()
{ 
        int i;
        for(i=EndLine; i<TopLine+1; i++) 
        { 
                   if((center_line[i].x > 1) && (center_line[i].x < 78)) 
                   { 
                                  sum_center += center_line[i].x * weighting[i]; 
                                  num_ave +=  weighting[i]; 
                   } 
        } 
        
        for(i = 0; i < 60; i++) 
        { 
                   if((center_line[i].x > 1) && (center_line[i].x < 78)) 
                   { 
                                  sum_center += center_line[i].x; 
                                  num_ave++; 
                                  if((i > (int)EndLine) && (i < (int)TopLine)) 
                                  { 
                                                 sum_center += center_line[i].x * 3; 
                                                 num_ave += 3; 
                                  }
                   }
        }

        ave_center = sum_center / num_ave; 
        sum_center = 0; 
        num_ave = 0; 
        return  ave_center;
}
