#include "full_connection_layer.h"

void full_connection_test()
{
    float input_data_buf[INPUT_NUM1] = {1, 2, 3};
    float output_data_sw[OUTPUT_NUM1];
    float output_data_hw[OUTPUT_NUM1];
    float weights_buf[OUTPUT_NUM1][INPUT_NUM1];
    float weights_flatten_buf[OUTPUT_NUM1*INPUT_NUM1];

    int err;

    for (int i = 0; i < OUTPUT_NUM1; i++)
    {
        /* code */
        for (int j = 0; j < INPUT_NUM1; j++)
        {
            /* code */
            weights_buf = i*INPUT_NUM1 + j;
        }
    }
    
    for (int i = 0; i < OUTPUT_NUM1; i++)
    {
        /* code */
        for (int j = 0; j < INPUT_NUM1; j++)
        {
            /* code */
            weights_flatten_buf = weights_buf[i][j];
        }
    }

    for (int i = 0; i < OUTPUT_NUM1; i++)
    {
        /* code */
        PROCESS:for (int j = 0; j < INPUT_NUM1; j++)
        {
            /* code */
            output_data_sw[i] += input_data_buf[j] * weights_buf[i][j];
        }
        #ifdef active
        output_data_sw[i] = (output_data_buf[i] > 0) ? output_data_buf[i] : 0;
        #endif
    }

    full_connection_layer1(input_data_buf,output_data_hw,weights_flatten_buf,0);

    for (int i = 0; i < OUTPUT_NUM1; i++)
    {
        /* code */
        if(output_data_sw != output_data_hw)
            err ++;
    }
    
    return err;

}