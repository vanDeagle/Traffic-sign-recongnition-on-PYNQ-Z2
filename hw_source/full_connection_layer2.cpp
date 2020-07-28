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
    bool active   
)
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi depth=30 port=weights
#pragma HLS ARRAY_PARTITION variable=input_data_buf complete dim=1
#pragma HLS ARRAY_PARTITION variable=output_data_buf complete dim=1
    float weights_buf[OUTPUT_NUM1][INPUT_NUM1];
#pragma HLS ARRAY_PARTITION variable=weights_buf complete dim=2

    load_data:
    {
        load_weights:for (int i = 0; i < OUTPUT_NUM1; i++)
        {
            /* code */
            for (int j = 0; j < INPUT_NUM1; j++)
            {
#pragma HLS PIPELINE
                /* code */
                weights_buf[i][j] = *weights++;
            }    
        }
    }

    full_C_cal:
    {
    	calculate:for (int i = 0; i < OUTPUT_NUM1; i++)
        {
#pragma HLS PIPELINE
            /* code */
            float temp = 0;
            PROCESS:for (int j = 0; j < INPUT_NUM1; j++)
            {
                /* code */
                temp += input_data_buf[j] * weights_buf[i][j];
            }
            if(active)
                output_data_buf[i] = (temp > 0) ? temp : 0;
            else
            {
                output_data_buf[i] = temp;
            }
            
        }
    }
}
