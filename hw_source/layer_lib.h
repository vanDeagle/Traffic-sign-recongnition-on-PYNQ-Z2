#ifndef __LAYER_LIB_H__
#define __LAYER_LIB_H__

#define input_R 32
#define input_C 32
#define input_channel 3
#define output_length 43


#define CONV_K 5


#define CONV1_Rin 32
#define CONV1_Cin 32
#define CONV1_R 28
#define CONV1_C 28
#define CONV1_CHin 3
#define CONV1_CHout 32

#define CONV2_Rin 14
#define CONV2_Cin 14
#define CONV2_R 10
#define CONV2_C 10
#define CONV2_CHin 32
#define CONV2_CHout 32

#define POOLING_K 2

#define POOLING1_Rin 28
#define POOLING1_Cin 28
#define POOLING1_R 14
#define POOLING1_C 14
#define POOLING1_CHin 32
#define POOLING1_CHout 32

#define POOLING2_Rin 10
#define POOLING2_Cin 10
#define POOLING2_R 5
#define POOLING2_C 5
#define POOLING2_CHin 32
#define POOLING2_CHout 32

#define FC1_INPUT_NUM1      800
#define FC1_OUTPUT_NUM1     64

#define FC2_INPUT_NUM1      64
#define FC2_OUTPUT_NUM1     43

#define FC3_INPUT_NUM1      84
#define FC3_OUTPUT_NUM1     43



extern void pooling_layer1(
    float In[POOLING1_CHin][POOLING1_Rin][POOLING1_Cin],
	float Out[POOLING1_CHout][POOLING1_R][POOLING1_C]
);

extern void pooling_layer2(
    float In[POOLING2_CHin][POOLING2_Rin][POOLING2_Cin],
	float out_1D[POOLING2_CHout*POOLING2_R*POOLING2_C]
);

extern void conv_layer1(
    float In[CONV1_CHin][CONV1_Rin][CONV1_Cin],
    float Out[CONV1_CHout][CONV1_R][CONV1_C],
    float *Weight,
    float *bias,
    bool active
    );

extern void conv_layer2(
    float In[CONV2_CHin][CONV2_Rin][CONV2_Cin],
    float Out[CONV2_CHout][CONV2_R][CONV2_C],
    float *weights,
    float *bias,
    bool active
    );

extern void full_connection_layer1(
    float input_data_buf[FC1_INPUT_NUM1],
    float output_data_buf[FC1_OUTPUT_NUM1],
    float *weights,
    float *bias,
    bool active   
);

extern void full_connection_layer2(
    float input_data_buf[FC2_INPUT_NUM1],
    float output_data_buf[FC2_OUTPUT_NUM1],
    float *weights,
    float *bias,
    bool active   
);

extern void full_connection_layer3(
    float input_data_buf[FC3_INPUT_NUM1],
    float output_data_buf[FC3_OUTPUT_NUM1],
    float *weights,
    bool active   
);
#endif