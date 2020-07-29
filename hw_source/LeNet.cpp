#include "layer_lib.h"

void  LeNet_Hw(
    float *conv1_w,
    float *conv1_bias,
    float *conv2_w,
    float *conv2_bias,
    float *fc1_w,
    float *fc1_bias,
    float *fc2_w,
    float *fc2_bias,
    float *input_data,
    float *output_data
)
{
#pragma HLS INTERFACE m_axi depth=256 port=output_data offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=input_data offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=fc2_w offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=fc1_w offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=conv2_w offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=conv1_w offset=slave
#pragma HLS INTERFACE s_axilite port=return
    float input_data_buf[1][input_R][input_C];
    float conv1_out[CONV1_CHout][CONV1_R][CONV1_C];
    float pooling1_out[POOLING1_CHout][POOLING1_R][POOLING1_C];
    float conv2_out[CONV2_CHout][CONV2_R][CONV2_C];
    float pooling2_out[POOLING2_CHout*POOLING2_C*POOLING2_R];
    float fc1_out[FC1_OUTPUT_NUM1];
    float output_data_buf[output_length];

    for (int i = 0; i < input_R; i++)
    {
        /* code */
        for (int j = 0; j < input_C; j++)
        {
#pragma HLS PIPELINE
            /* code */
            input_data_buf[0][i][j] = *input_data++;
        }
    }

    net_cal:
    {
        conv_layer1(input_data_buf,conv1_out,conv1_w,conv1_bias,1);
        pooling_layer1(conv1_out,pooling1_out);
        conv_layer2(pooling1_out,conv2_out,conv2_w,conv2_bias,1);
        pooling_layer2(conv2_out,pooling2_out);
        full_connection_layer1(pooling2_out,fc1_out,fc1_w,fc1_bias,1);
        full_connection_layer2(fc1_out,output_data_buf,fc2_w,fc2_bias,1);
    }


    for (int i = 0; i < output_length; i++)
    {
#pragma HLS PIPELINE
        /* code */
        *output_data++ = output_data_buf[i];
    }
    

}
