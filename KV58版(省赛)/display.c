#include "headfile.h"

void  display()
{
  if(flag_display==0) display1();
  else  display2();
}

void  display1()
{
        OLED_Print_Num1(10,0,g_ValueOfAD[0]);//显示水平左电感
        OLED_Print_Num1(80,0,g_ValueOfAD[1]);//显示水平右电感		
	OLED_Print_Num1(10,1,g_ValueOfAD[2]);//显示垂直左电感
	OLED_Print_Num1(80,1,g_ValueOfAD[3]);//显示垂直右电感
        OLED_Print_Num1(10,4,g_nLeftSpeed);
        OLED_Print_Num1(80,4,g_nRighSpeed);
        OLED_Print_Num1(10,7,flag_display);

}
void  display2()
{
    unsigned char i;
    OLED_P6x8Str(10,0,"g_s"); OLED_Print_Num1(30,0,g_fExpectSpeed); 
    OLED_P6x8Str(10,1,"s_p"); OLED_Print_Num1(30,1,g_speedControl_P); 
    OLED_P6x8Str(10,2,"s_i"); OLED_Print_Num1(30,2,g_speedControl_I);  
    OLED_P6x8Str(10,3,"d_p"); OLED_Print_Num1(30,3,g_dirControl_P); 
    OLED_P6x8Str(10,4,"d_d"); OLED_Print_Num1(30,4,g_dirControl_D); 
    for(i=0;i<8;i++)
        if(i==set_num-1)
           OLED_P6x8Str(0,i,"*");
        else 
           OLED_P6x8Str(0,i," "); 
}











