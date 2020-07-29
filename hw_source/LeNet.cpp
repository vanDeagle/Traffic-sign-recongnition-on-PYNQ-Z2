#include "layer_lib.h"

void  LeNet_Hw(
    float *conv1_w,
    float *conv2_w,
    float *fc1_w,
    float *fc2_w,
    float *fc3_w,
    float *input_data,
    float *output_data
)
{
#pragma HLS INTERFACE m_axi depth=256 port=output_data offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=input_data offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=fc3_w offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=fc2_w offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=fc1_w offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=conv2_w offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=conv1_w offset=slave
#pragma HLS INTERFACE s_axilite port=return
    float input_data_buf[1][input_R][input_C];
    float conv1_out[6][28][28];
    float pooling1_out[6][14][14];
    float conv2_out[16][10][10];
    float pooling2_out[400];
    float fc1_out[120];
    float fc2_out[86];
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
        conv_layer1(input_data_buf,conv1_out,conv1_w);
        pooling_layer1(conv1_out,pooling1_out);
        conv_layer2(pooling1_out,conv2_out,conv2_w);
        pooling_layer2(conv2_out,pooling2_out);
        full_connection_layer1(pooling2_out,fc1_out,fc1_w,1);
        full_connection_layer2(fc1_out,fc2_out,fc2_w,1);
        full_connection_layer3(fc2_out,output_data_buf,fc3_w,1);
    }


    for (int i = 0; i < output_length; i++)
    {
#pragma HLS PIPELINE
        /* code */
        *output_data++ = output_data_buf[i];
    }
    

}
