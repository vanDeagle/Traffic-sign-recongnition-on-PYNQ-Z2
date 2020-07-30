#ifndef __POOLING_LAYER1_H__
#define __POOLING_LAYER1_H__

#define K 2
#define Rin 28
#define Cin 28
#define R 14
#define C 14
#define CHin 32
#define CHout 32

extern void pooling_layer1(
    float In[CHin][Rin][Cin],
	float Out[CHout][R][C]
);

#endif
