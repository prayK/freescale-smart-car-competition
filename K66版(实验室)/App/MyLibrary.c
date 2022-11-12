#include "common.h"
#include "include.h"
#include "MyLibrary.h"
#include "include.h"

float b2,b1,b0;
float a1,a0;

///////////////整型数组/////////////////////////
float sum_1(int16 *p,uint8 m) //求和函数 //之后给了例子
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=*(p+i);
      }
      return sum;
}

float sum_2(int16 *p,uint8 m) //求平方和
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=(*(p+i))*(*(p+i));
      }
      return sum;
}

float sum_3(int16 *p,int16 *q,uint8 m)  //求乘积和
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=(*(p+i))*(*(q+i));
      }
      return sum;
}

float sum_4(int16 *p,int16 *q,uint8 m) //求乘积
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=( (*(p+i))*(*(p+i)))*(*(q+i));
      }
      return sum;
      
}

float sum_5(int16 *p,uint8 m)
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=pow(*(p+i),3);  
      }
      return sum;
}

float sum_6(int16 *p,uint8 m)
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
            sum+=pow(*(p+i),4);
      return sum;
}

/***********************************************************************************************************************************/

///////////////浮点数组///////////////////////
float sum_11(float *p,uint8 m) //求和函数 //之后给了例子
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=*(p+i);
      }
      return sum;
}

float sum_22(float *p,uint8 m) //求平方和
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=(*(p+i))*(*(p+i));
      }
      return sum;
}

float sum_33(float *p,float *q,uint8 m)  //求乘积和
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=(*(p+i))*(*(q+i));
      }
      return sum;
}

float sum_44(float *p,float *q,uint8 m) //求乘积
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=( (*(p+i))*(*(p+i)))*(*(q+i));
      }
      return sum;
      
}

float sum_55(float *p,uint8 m)
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=pow(*(p+i),3);  
      }
      return sum;
}

float sum_66(float *p,uint8 m)
{
      int16 i;
      float sum=0.0;
      for(i=0;i<m;i++)
            sum+=pow(*(p+i),4);
      return sum;
}


///////////////double数组////////////////////
double sum_111(int16 *p,uint8 m) //求和函数 //之后给了例子
{
      int16 i;
      double sum=0.0;
      for(i=0;i<m;i++)
      { 
            sum+=*(p+i);
      } 
      return sum;
}

double sum_222(int16 *p,uint8 m) //求平方和
{
      int16 i;
      double sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=(*(p+i))*(*(p+i));
      }
      return sum;
}

double sum_333(int16 *p,int16 *q,uint8 m)  //求乘积和
{
      int16 i;
      double sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=(*(p+i))*(*(q+i));
      }
      return sum;
}

double sum_444(int16 *p,int16 *q,uint8 m) //求乘积
{
      int16 i;
      double sum=0.0;
      for(i=0;i<m;i++)
      {
            sum+=( (*(p+i))*(*(p+i)))*(*(q+i));
      }
      return sum;
      
}

double sum_555(int16 *p,uint8 m)
{
      int16 i; 
      double sum=0.0; 
      for(i=0;i<m;i++) 
      { 
            sum+=pow(*(p+i),3); 
      } 
      return sum;
}

double sum_666(int16 *p,uint8 m)
{
      int16 i;
      double sum=0.0;
      for(i=0;i<m;i++)
            sum+=pow(*(p+i),4);
      return sum;
}



