#ifndef __CONV_LAYER2_H__
#define __CONV_LAYER2_H__

#define K 5
#define Rin 14
#define Cin 14
#define R 10
#define C 10
#define CHin 6
#define CHout 16

extern void conv_layer2(float In[CHin][Rin][Cin],float Out[CHout][R][C],float *Weight);
#endif