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

#define       EndLine            18   //��ǰ��
#define       LittleEndLine      28   //��ǰ��
#define       MiddleLine         38   //��ǰ��
#define       LittleTopLine      48   //�Ϻ���
#define       TopLine            58   //�����

//#define       QZ_End      33   //ǰհ��ǰ��/////��Ӧ���190�ٶ�
//#define       QZ_Top      55   //ǰհ�����

//#define       QZ_End      20   //ǰհ��ǰ��
//#define       QZ_Top      56   //ǰհ�����

//#define       QZ_End      26   //ǰհ��ǰ��///////��Ӧ���210�ٶ�
//#define       QZ_Top      55   //ǰհ�����

#define       QZ_End      21   //ǰհ��ǰ��///��ǰ�ٶ�ͦ�ö���x85
#define       QZ_Top      49   //ǰհ�����

#endif 

