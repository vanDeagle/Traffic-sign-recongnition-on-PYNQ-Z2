/***********************************************
Author: Kyle 
Associated Filename: full_connection.cpp
Purpose:to acceleration of the full_connection_layer
Device: All 
Revision History: July 28,2020
------------------------------------------
Meanings of registers:
input_data       ---->   DDR address that point to input data
output_data      ---->   DDR address that point to result data
weights          ---->   DDR address that point to weights data
***********************************************/

#include "full_connection_layer2.h"

void full_connection_layer2(
    float input_data_buf[INPUT_NUM1],
    float output_data_buf[OUTPUT_NUM1],
    float *weights,
    float *bias,
    bool active   
)
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi depth=256 port=weights offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=bias offset=slave
    float weights_buf[INPUT_NUM1];
    float bias_buf;
    for (int i = 0; i < OUTPUT_NUM1; i++)
    {
        load_data:
        {
            load_weights:for (int j = 0; j < INPUT_NUM1; j++)
                {
    #pragma HLS PIPELINE
                    /* code */
                    weights_buf[j] = *weights++;
                }    
                /* code */
                bias_buf = *bias++;
        }

        full_C_cal:
        {
            calculate:
                /* code */
                float temp = 0;
                PROCESS:for (int j = 0; j < INPUT_NUM1; j++)
                {
    #pragma HLS PIPELINE
                    /* code */
                    temp += input_data_buf[j] * weights_buf[j];
                }
                temp += bias_buf;
                if(active)
                    output_data_buf[i] = (temp > 0) ? temp : 0;
                else
                {
                    output_data_buf[i] = temp;
                }
                

        }
    }
    
}
