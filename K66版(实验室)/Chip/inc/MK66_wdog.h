#ifndef __MK66_WDOG_H__
#define __MK66_WDOG_H__

/********************************************************************/

//wdog ���룬���� LDO ʱ�ӣ�����Ƶ��

extern void wdog_init_ms(uint32 ms);   //��ʼ�����Ź�������ι��ʱ�� ms
extern void wdog_feed(void);           //ι��


extern void wdog_disable(void);        //���ÿ��Ź�
extern void wdog_enable(void);         //���ÿ��Ź�

/********************************************************************/
#endif /* __MK66_WDOG_H__ */
