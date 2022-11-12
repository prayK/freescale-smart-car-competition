#ifndef __IMAGEDEAL_H__
#define __IMAGEDEAL_H__

extern float UseTwicePValue();
extern float UseSticPValue();
extern void  UseTheWeightCountCenterlineAverage();
extern float UseLineValueChangePValue();
extern void  bianxian_averageLvBo(void);
extern void  AverageLvBo(void);
extern int   regression(int startline,int endline);
extern float UseTheChangeableWeightCountCenterlineAverage();

#define       EndLine            18   //最前面
#define       LittleEndLine      28   //最前面
#define       MiddleLine         38   //较前面
#define       LittleTopLine      48   //较后面
#define       TopLine            58   //最后面

//#define       QZ_End      33   //前瞻最前面/////对应弯道190速度
//#define       QZ_Top      55   //前瞻最后面

//#define       QZ_End      20   //前瞻最前面
//#define       QZ_Top      56   //前瞻最后面

//#define       QZ_End      26   //前瞻最前面///////对应弯道210速度
//#define       QZ_Top      55   //前瞻最后面

#define       QZ_End      21   //前瞻最前面///当前速度挺好都是x85
#define       QZ_Top      49   //前瞻最后面

#endif 

