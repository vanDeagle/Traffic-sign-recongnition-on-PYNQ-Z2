#ifndef __CONV_LAYER1_H__
#define __CONV_LAYER1_H__

#define K 5
#define Rin 32
#define Cin 32
#define R 28
#define C 28
#define CHin 3
#define CHout 32

extern void conv_layer1(float In[CHin][Rin][Cin],float Out[CHout][R][C],float W[CHout][CHin][K][K],float bias_buf[CHout],bool active);

#endif