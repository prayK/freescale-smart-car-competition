#ifndef __IMAGEDEAL_H__
#define __IMAGEDEAL_H__

void RingInsideDeal(void);
extern float UseTwicePValue();
extern float UseSticPValue();
extern void  UseTheWeightCountCenterlineAverage();
extern void UseLineValueChangePValue();
extern void  CenterLineLvBo(void);
extern void  AverageLvBo(void);
extern int   regression(int startline,int endline);
extern float UseTheChangeableWeightCountCenterlineAverage();
extern void  StreetRealize(void);
#define       MostEndLine        13   //��ǰ��/////�����ж�ʮ��
#define       EndLine            18   //��ǰ��
//#define       MoreEndLine        23   //��ǰ��
#define       LittleEndLine      28   //��ǰ��
//#define       LittleMiddleLine   33   //��ǰ��
#define       MiddleLine         38   //��ǰ��
//#define       MostMiddleLine     43   //��ǰ��
#define       LittleTopLine      48   //�Ϻ���
//#define       MoreTopLine        53   //�Ϻ���
#define       TopLine            58   //�����

//#define       QZ_End      33   //ǰհ��ǰ��/////��Ӧ���190�ٶ�
//#define       QZ_Top      55   //ǰհ�����

//#define       QZ_End      20   //ǰհ��ǰ��
//#define       QZ_Top      56   //ǰհ�����

//#define       QZ_End      26   //ǰհ��ǰ��///////��Ӧ���210�ٶ�
//#define       QZ_Top      55   //ǰհ�����

#define       QZ_End      20   //ǰհ��ǰ��
#define       QZ_Top      50   //ǰհ�����

#endif 

