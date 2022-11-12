#include "headfile.h"
 
int set_num;
int flag_display;

void  key_init()
{
    gpio_init(K1,GPI,1);         //1	按键开关，K1-4若用于备用接口则改为GPO;
    gpio_init(K2,GPI,1);         //2
    gpio_init(K3,GPI,1);         //3
    gpio_init(K4,GPI,1);         //4
    gpio_init(K5,GPI,1);
    gpio_init(BM1,GPI,1);         //1	拨码开关，K1-4若用于备用接口则改为GPO;
    gpio_init(BM2,GPI,1);         //2
    gpio_init(BM3,GPI,1);         //3
    gpio_init(BM4,GPI,1);         //4
    gpio_init(BM5,GPI,1);  
    gpio_init(BM6,GPI,1); 
    gpio_init(BM7,GPI,1); 
    gpio_init(BM8,GPI,1);     
    prot_pull(K1);	
    prot_pull(K2);     
    prot_pull(K3);	
    prot_pull(K4);    
    prot_pull(K5);  
    prot_pull(BM1);	
    prot_pull(BM2);     
    prot_pull(BM3);	
    prot_pull(BM4);    
    prot_pull(BM5); 
    prot_pull(BM6);	
    prot_pull(BM7);    
    prot_pull(BM8);      
}

unsigned char key_get(unsigned char num)
{
  switch (num)
  { 
    case 1:     
      if(gpio_get(K1)==0)
      {
        systick_delay_ms(10);  
        if(gpio_get(K1)==0)
        {
         while(!gpio_get(K1));
         return 1;
        } 
      }
      else return 0;
      break;
      
    case 2:     
      if(gpio_get(K2)==0)
      {
        systick_delay_ms(10);  
        if(gpio_get(K2)==0)
        { 
         while(!gpio_get(K2));
         return 1;
        } 
      }
      else return 0;
      break;
      
    case 3:     
      if(gpio_get(K3)==0)
      {
        systick_delay_ms(10);  
        if(gpio_get(K3)==0)
        {
         while(!gpio_get(K3));
         return 1;
        }  
      }
      else return 0;
      break;
      
    case 4:     
      if(gpio_get(K4)==0)
      {
        systick_delay_ms(10);  
        if(gpio_get(K4)==0)
        {
         while(!gpio_get(K4));
         return 1;
        }  
      }
      else return 0;
      break;      
     
    case 5:     
      if(gpio_get(K5)==0)
      {
        systick_delay_ms(10);  
        if(gpio_get(K5)==0)
        { 
         while(!gpio_get(K5));
         return 1;
        } 
      }
      else return 0;
      break; 
    default: return 0;break;

  }
}

void key()
{


   if(flag_display==1)
   switch(set_num)
   {
     case 1: 
             if(K1_get) g_fExpectSpeed+=20;
             if(K2_get) g_fExpectSpeed-=10;
             break;
     case 2:
             if(K1_get) g_speedControl_P+=2;
             if(K2_get) g_speedControl_P-=1;
             break;              
     case 3: 
             if(K1_get) g_speedControl_I+=2;
             if(K2_get) g_speedControl_I-=1;
             break;
     case 4: 
             if(K1_get) g_dirControl_P+=40;
             if(K2_get) g_dirControl_P-=10;
             break;  
     case 5:
             if(K1_get) g_dirControl_D+=40;
             if(K2_get) g_dirControl_D-=10;
             break;  
    default: break;          
       
   }
    if(K3_get)
   {
     set_num++;
     if(set_num>5) set_num=0;
   } 
    if(K5_get)
   {
     flag_display++;
     OLED_Fill(0x00); 
     if(flag_display==2) flag_display=0;
   }  
//             if(K1_get) g_fExpectSpeed+=20;
//             if(K2_get) g_fExpectSpeed-=10;
//             if(K3_get) g_speedControl_P+=2;
//             if(K4_get) g_speedControl_P-=1;

}
