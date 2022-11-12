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

//#define       QZ_End      20   //ǰհ��ǰ��
//#define       QZ_Top      50   //ǰհ�����

/*�̶�Ȩֵ��Ȩ��ƫ��*/
void UseTheWeightCountCenterlineAverage()
{ 
        //CenterLineLvBo();////�ȶ������˲�����
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
        for(i=0; i<60; i++) //���߼�Ȩƽ��ֵ����
        {
                  if((center_line[i].x>0) && (center_line[i].x<79)) //��������Ƿ���Ч
                  {
                            if(center_line[i].x > R_max) //�ҵ��ұ������ֵ
                            {
                                    R_max = center_line[i].x;
                            }
                            if(center_line[i].x < L_min) //�ҵ��������Сֵ
                            {
                                    L_min = center_line[i].x;
                            }
                            
                            if(num_ave == 0)
                            {
                                    speed_ave = i; //ɨ�赽��һ����Чֵ��ʱ��  ��¼����
                            }
                            sum_center += center_line[i].x;
                            num_ave++;
                            if((i > speed_ave) && (i < speed_ave + (60 - speed_ave) / 2)) //ֻ��ǰһ���ߵ�ǰհ                                                      //��Ȩ 
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
        for(i=0; i<60; i++) //���������
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
////��Ի�����������ʶ���Դ��䲻ͬ�Ĳ���
//void RingInsideDeal(void)
//{ 
//        if (assist1 == 1)//���Ѿ����󻷵���ǽ���ʱ���л�����Сʶ��
//        {                 
//                if (
//                    bian_line[H * 2] 
//                    bian_line[H * 2 + 2] 
//                    bian_line[H * 2 + 4] //ֻȡ��Ч��������������ȴ��Լ���
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
   
/*��̬P�㷨*/
float UseSticPValue()
{ 
          CenterValue = ServoCenterValue; 
          CurrentError = ave_center - 40; 
          return 1;
} 
uint8  UFlag = 0;
/*����P�㷨*/
void UseLineValueChangePValue() 
{
          CenterValue = ServoCenterValue; 
//          if (assist4 == 1)
//                  CurrentError = ErrorRecord - 40; 
//          else
          CurrentError = ave_center - 40; 
          
          if ((LittleSFlag == 1) && (Ring_Find_Flag != 1)) //СS����¸�СP,ֱ�� 
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

/*����P����������ʶ��ֶ�P�㷨*/
float UseTwicePValue()
{
          CenterValue = ServoCenterValue;  
          CurrentError = ave_center - 40;
 
          if ((LittleSFlag == 1) && (Ring_Find_Flag != 1)) //СS����¸�СP,ֱ�� 
          { 
                   ServoPDValue[0] = 0.03; 
                   return  ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]); 
          } 
 
          else if (assist3 == 1)//���������������������P 
          { 
                   ServoPDValue[0] = 0.13; 
                   ServoPDValue[1] = 0; 
                   return ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]); 
          } 

          else if ((center_line[LittleEndLine].x < 38 && center_line[EndLine].x == 0) 
            &&(center_line[LittleTopLine].x != 0 && center_line[TopLine].x != 0) ///��ת 
            &&(center_line[MiddleLine].x != 0) 
            &&(shi_flag != 1) 
            &&(Ring_Find_Flag != 1)) ///U�� 
          { 
                   ServoPValue[0] = 0.46;
                   return ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]);
          } 

          else if ((center_line[LittleEndLine].x > 42 && center_line[EndLine].x == 0) 
            &&(center_line[LittleTopLine].x != 0 && center_line[TopLine].x != 0)///��ת 
            &&(center_line[MiddleLine].x != 0)
            &&(shi_flag != 1) 
            &&(Ring_Find_Flag != 1))//U�� 
          { 
                   ServoPValue[0] = 0.46;
                   return ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]);
          } 
         else///�������� 
         { 
              ServoPValue[0] = 0.25;
              return ServoPDValue[0] = (ServoPValue[0] + (CurrentError * CurrentError) / ServoPValue[1]);
         } 
}


/*�����˲�,���ۺ���Ч��δ֪*/
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


/*�����˲�,���ۺ���Ч��δ֪*/
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

/*�����˲�����*/
//uchar Point_Average(void)
//{
//	uchar i, Half_Line;//
//	int32 Point, Sum = 0;
//	static uchar Last_Point = 40;//
//	
//	if (Out_Side || Line_Count >= 55) // �����������ͷͼ���쳣  //uchar Out_Side = 0; // ���߿��� uchar Line_Count; // ��¼�ɹ�ʶ�𵽵���������
//
//	{ 
//		Point  = Last_Point; // ʹ���ϴ�Ŀ���
//	} 
//	else
//	{ 
//		Half_Line = 59 - (59 - Line_Count) / 2; // ������Ч�е��м���
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
//			Point = Sum / ((61-Line_Count)/2); // ��������ƽ��
//			if (Left_Add_Line[Half_Line] >= 20) // ̫ƫ��
//			{
//				Point += (Left_Add_Line[Half_Line]-20);	// �ʵ�����
//			}
//			if (Right_Add_Line[Half_Line] <= 60) // ̫ƫ��
//			{
//				Point -= (60-Right_Add_Line[Half_Line]); // �ʵ�����
//			}
//		}
//		
//		Point = Point*0.9 + Last_Point*0.1; // ��ͨ�˲�
//		Point = range_protect(Point, 1, 79); // �޷�����ֹ�������
//		Last_Point = Point; // �����ϴ�Ŀ���
//	}
//	return Point;
//}


/*���Իع鷽�̼���б��,���ۺ���Ч��δ֪*/
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


/*��̬��Ȩ��ƫ��,2018.6.13��֤ûͨ��*/
float weighting[33] = {   0.8, 0.9, 1.0, 1.1, 1.2,//24-28�е�Ȩ��
                          1.8, 1.9, 2.0, 2.1, 2.2,//29��33�е�Ȩ��
                          2.8, 2.9, 3.0, 3.1, 3.2,//34��38�е�Ȩ��
                          3.8, 3.9, 4.0, 4.1, 4.2,//39��43�е�Ȩ�� 
                          4.8, 4.9, 5.0, 5.1, 5.2,//44��48�е�Ȩ�� 
                          5.8, 5.9, 6.0, 6.1, 6.2,//49��53�е�Ȩ�� 
                          4.9, 5, 5.1             //54��56�е�Ȩ�� 
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
