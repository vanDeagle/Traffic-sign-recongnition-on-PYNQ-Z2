#include "full_connection_layer.h"

void full_connection_layer1(
    float *input_data,
    float *output_data,
    float *weights,
    bool active   
)
{
    float input_data_buf[INPUT_NUM1];
    float output_data_buf[OUTPUT_NUM1];
    float weights_buf[OUTPUT_NUM1][INPUT_NUM1];

    load_data:
    {
        for (int i = 0; i < INPUT_NUM1; i++)
        {
            /* code */
            input_data_buf[i] = *input_data++;
        }

        for (int i = 0; i < OUTPUT_NUM1; i++)
        {
            /* code */
            for (int j = 0; j < INPUT_NUM1; j++)
            {
                /* code */
                weights_buf[i][j] = *weights++;
            }    
        }
    }

    full_C_cal:
    {
        OUT_NUM:for (int i = 0; i < OUTPUT_NUM1; i++)
        {
            /* code */
            PROCESS:for (int j = 0; j < INPUT_NUM1; j++)
            {
                /* code */
                output_data_buf[i] += input_data_buf[j] * weights_buf[i][j];
            }
            if(active)
                output_data_buf[i] = (output_data_buf[i] > 0) ? output_data_buf[i] : 0;
        }
    }
}