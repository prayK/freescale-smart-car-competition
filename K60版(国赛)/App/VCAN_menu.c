#include "common.h"
#include "VCAN_LCD.h"
#include "VCAN_key.h"

#include "VCAN_menu.h"
extern char *num_str[3];


void menu_init(Site_t site,menu_t *menu,uint8 tab,uint8 new_tab,uint8 max_tab)
{
    menu_display(site,menu,max_tab ,new_tab,max_tab);
}

result_e menu_deal(Site_t site,menu_t *menu,uint8 tab,uint8 *new_tab,uint8 max_tab)
{
    KEY_MSG_t keymsg;

    while(get_key_msg(&keymsg) == 1)
    { 
        if(keymsg.status == KEY_DOWN)
        {
            switch(keymsg.key)
            {
            case KEY_D:
                {
                    if(*new_tab < max_tab-1)
                    {
                        (*new_tab)++;
                         menu_display(site,menu,*new_tab - 1 ,*new_tab,max_tab);
                    }
                    else
                    {
                        *new_tab=0;
                        menu_display(site,menu,max_tab - 1 ,*new_tab,max_tab);
                    }
                    menu_display(site,menu,*new_tab ,*new_tab,max_tab);
                    break;
                }
            case KEY_U:
                {
                    if(*new_tab == 0)
                    {
                        *new_tab = max_tab - 1;
                        menu_display(site,menu,0 ,*new_tab,max_tab);
                    }
                    else
                    {
                        (*new_tab)--;
                        menu_display(site,menu,*new_tab + 1 ,*new_tab,max_tab);
                    }
                    menu_display(site,menu,*new_tab ,*new_tab,max_tab);
                    break;
                }
            case KEY_A:
                {
                    return RESULT_INIT;
                }
            case KEY_B:
                {
                    return menu[*new_tab].pfunc();
                }

               default:
                break;

            }

        }
    }

    return RESULT_NULL;
}

void menu_display(Site_t  site,menu_t *menu,uint8 tab,uint8 new_tab,uint8 max_tab)
{
    //定义背景延时
#define SELECT_BG         WHITE   //当前选中，而且没有改变
#define NO_SELECT_BG      BCOLOUR     //没有选中，而且没有改变（普通的就是这样）

    //定义文字颜色
#define SELECT_FC            RED    //当前选中，而且没有改变
#define NO_SELECT_FC         FCOLOUR   //没有选中，而且改变了

    uint8  i = 0;
    uint16 bkColor;
    uint16 Color;
    Site_t  sitetmp;
    sitetmp.x =  site.x;

    if(tab == max_tab)      //显示全部
    {
        i = max_tab - 1;    //循环的次数
        tab = 0;
    }

    do
    {
        if(tab == new_tab)
        {

            Color   =  SELECT_FC;
            bkColor =  SELECT_BG;

        }
        else
        {
            Color   =  NO_SELECT_FC;
            bkColor =  NO_SELECT_BG;
        }


        //显示文字
        //LCD_num_C(VAR_SITE(tab), VAR_VALUE(tab), Color, bkColor);
        sitetmp.y = site.y +  tab * LCD_CH_H ;
        LCD_FSTR_CH_FUNC(sitetmp,menu[tab].strbuff,menu[tab].strnum,Color,bkColor);
        //LCD_Str_ENCH(Site_t site,const uint8 *str  , uint16 Color ,uint16 bkColor); //中英混合字符串

        tab++;
    }
    while(i--);         //tab != VAR_MAX 的时候，执行一次就跳出
}
void mymenu_display(Site_t site,char Str[][10],uint8 tab,uint8 new_tab,uint8 max_tab)
{
#define SELECT_BG            BLUE    //当前选中，而且没有改变
#define NO_SELECT_BG         BCOLOUR     //没有选中，而且没有改变（普通的就是这样）
#define SELECT_FC            RED    //当前选中，而且没有改变
#define NO_SELECT_FC         FCOLOUR   //没有选中，而且改变了

    uint8  i = 0;
    uint16 bkColor;
    uint16 Color;
    Site_t  sitetmp;
    sitetmp.x =  site.x;

    if(tab == max_tab)      //显示全部
    {
        i = max_tab - 1;    //循环的次数
        tab = 0;
    }

    do
    {
        if(tab == new_tab)
        {

            Color   =  SELECT_FC;
            bkColor =  SELECT_BG;

        }
        else
        {
            Color   =  NO_SELECT_FC;
            bkColor =  NO_SELECT_BG;
        }
        sitetmp.y = site.y +  tab * LCD_CH_H ;
       LCD_str(sitetmp,Str[tab],Color,bkColor); 
        tab++;
    }
    while(i--);         //tab != VAR_MAX 的时候，执行一次就跳出

}
result_e mymenu_deal(Site_t site,char Str[][10],float *str_string[],uint8 tab,uint8 *new_tab,uint8 max_tab,float key_change[])
{
  KEY_MSG_t keymsg;
  mymenu_display(site,Str,max_tab ,*new_tab,max_tab);
  while(get_key_msg(&keymsg) == 1)
    {
        if(keymsg.status == KEY_DOWN)
        {
            switch(keymsg.key)
            {
            case KEY_D:
                {
                    if(*new_tab < max_tab-1)
                    {
                        (*new_tab)++;
                         mymenu_display(site,Str,*new_tab - 1 ,*new_tab,max_tab);
                    }
                    else
                    {
                        *new_tab=0;
                        mymenu_display(site,Str,max_tab - 1 ,*new_tab,max_tab);
                    }
                    mymenu_display(site,Str,*new_tab ,*new_tab,max_tab);
                    break;
                }
            case KEY_U:
                {
                    if(*new_tab == 0)
                    {
                        *new_tab = max_tab - 1;
                        mymenu_display(site,Str,0 ,*new_tab,max_tab);
                    }
                    else
                    {
                        (*new_tab)--;
                        mymenu_display(site,Str,*new_tab + 1 ,*new_tab,max_tab);
                    }
                    mymenu_display(site,Str,*new_tab ,*new_tab,max_tab);
                    break;
                }
            case KEY_L:
                {
                   *str_string[*new_tab]= *str_string[*new_tab]-key_change[*new_tab];
                    if(*str_string[*new_tab]<=0)
                    *str_string[*new_tab]=0;
                   break;
                }
            case KEY_R:
                {
                   *str_string[*new_tab]= *str_string[*new_tab]+key_change[*new_tab];
                   break;
                }
            case KEY_A:
                {
                   return 1;
                }
            case KEY_B:
                {
                    return 1;
                    break;
                }
                default:return 0;
                break;
            }

        }
    } 
}
