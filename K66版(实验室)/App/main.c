#include "include.h"
#include "common.h"

void main()
{ 
         System_Init(); 
         Boma_Key_Init();  
         while(1) 
         { 
                     ImageWatching(); //图像处理以及显示
                     UseTheWeightCountCenterlineAverage();//对于结算出的中线求出最终均值 
                     IncrementalServoControl();//舵机控制
          } 
} 
