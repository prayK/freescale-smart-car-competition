#ifndef _keyboard_h
#define _keyboard_h

extern float g_fExpectSpeed;
extern float g_speedControl_P;
extern float g_speedControl_I;
extern float g_dirControl_P;
extern float g_dirControl_D;
extern int set_num;
extern int flag_display;
void key_init();
void key();
unsigned char key_get(unsigned char num);


#define  K1_get key_get(1)
#define  K2_get key_get(2)
#define  K3_get key_get(3)
#define  K4_get key_get(4)
#define  K5_get key_get(5)
#define  bm1    gpio_get(BM1)
#define  bm2    gpio_get(BM2)
#define  bm3    gpio_get(BM3)
#define  bm4    gpio_get(BM4)
#define  bm5    gpio_get(BM5)
#define  bm6    gpio_get(BM6)
#define  bm7    gpio_get(BM7)
#define  bm8    gpio_get(BM8)

#endif
