#ifndef __POOLING_LAYER2_H__
#define __POOLING_LAYER2_H__

#define K 2
#define Rin 10
#define Cin 10
#define R 5
#define C 5
#define CHin 64
#define CHout 64

extern void pooling_layer2(
    float In[CHin][Rin][Cin],
	float out_1D[CHout*R*C],
    float *bias
);

#endif