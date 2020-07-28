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
    float input_data_buf[input_R][input_C];
    float conv1_out[28][28][6];
    float pooling1_out[14][14][6];
    float conv2_out[10][10][16];
    float pooling2_out[400];
    float fc1_out[120];
    float fc2_out[86];
    float output_data_buf[output_length];

    for (int i = 0; i < input_R; i++)
    {
        /* code */
        for (int j = 0; j < input_C; j++)
        {
            /* code */
            input_data_buf[i][j] = *input_data++;
        }
        
    }
    
    conv_layer1(input_data_buf,conv1_out,conv1_w);
    pooling_layer1(conv1_out,pooling1_out);
    conv_layer2(pooling1_out,conv2_out,conv2_w);
    pooling_layer2(conv2_out,pooling2_out);
    full_connection_layer1(pooling2_out,fc1_out,fc1_w,1);
    full_connection_layer2(fc1_out,fc2_out,fc2_w,1);
    full_connection_layer3(fc2_out,output_data_buf,fc3_w,1);

    for (int i = 0; i < output_length; i++)
    {
        /* code */
        *output_data++ = output_data_buf[i];
    }
    

}