#include "include.h"
#include "common.h"

void main()
{ 
         System_Init(); 
         Boma_Key_Init();  
         while(1) 
         { 
                     ImageWatching(); //ͼ�����Լ���ʾ
                     UseTheWeightCountCenterlineAverage();//���ڽ����������������վ�ֵ 
                     IncrementalServoControl();//�������
          } 
} 
