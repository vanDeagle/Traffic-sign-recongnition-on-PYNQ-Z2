#ifndef __LAYER_LIB_H__
#define __LAYER_LIB_H__

#define input_R 32
#define input_C 32
#define output_length 43

extern void pooling_layer1(
    float In[CHin][Rin][Cin],
	float Out[CHout][R][C]
);

extern void pooling_layer2(
    float In[CHin][Rin][Cin],
	float out_1D[CHout*R*C]
);

extern void conv_layer1(float In[CHin][Rin][Cin],float Out[CHout][R][C],float *Weight);

extern void conv_layer2(float In[CHin][Rin][Cin],float Out[CHout][R][C],float *Weight);

extern void full_connection_layer1(
    float input_data_buf[INPUT_NUM1],
    float output_data_buf[OUTPUT_NUM1],
    float *weights,
    bool active   
)

extern void full_connection_layer2(
    float input_data_buf[INPUT_NUM1],
    float output_data_buf[OUTPUT_NUM1],
    float *weights,
    bool active   
)

extern void full_connection_layer3(
    float input_data_buf[INPUT_NUM1],
    float output_data_buf[OUTPUT_NUM1],
    float *weights,
    bool active   
)
#endif