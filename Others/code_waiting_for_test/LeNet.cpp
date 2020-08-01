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
#pragma HLS INTERFACE m_axi depth=500 port=output_data offset=slave
#pragma HLS INTERFACE m_axi depth=500 port=input_data offset=slave
#pragma HLS INTERFACE m_axi depth=500 port=fc2_w offset=slave
#pragma HLS INTERFACE m_axi depth=32 port=fc2_bias offset=slave
#pragma HLS INTERFACE m_axi depth=500 port=fc1_w offset=slave
#pragma HLS INTERFACE m_axi depth=32 port=fc1_bias offset=slave
#pragma HLS INTERFACE m_axi depth=500 port=conv2_w offset=slave
#pragma HLS INTERFACE m_axi depth=32 port=conv2_bias offset=slave
#pragma HLS INTERFACE m_axi depth=500 port=conv1_w offset=slave
#pragma HLS INTERFACE m_axi depth=32 port=conv1_bias offset=slave
#pragma HLS INTERFACE s_axilite port=return
    float input_data_buf[input_channel][input_R][input_C];
    float conv1_out[CONV1_CHout][CONV1_R][CONV1_C];
    float pooling1_out[POOLING1_CHout][POOLING1_R][POOLING1_C];
    float conv2_out[CONV2_CHout][CONV2_R][CONV2_C];
    float pooling2_out[POOLING2_CHout*POOLING2_C*POOLING2_R];
    float fc1_out[FC1_OUTPUT_NUM1];
    float output_data_buf[output_length];
    float fc1_weights_buf[FC1_INPUT_NUM1];
    float fc1_bias_buf[FC1_OUTPUT_NUM1];
    float conv1_W[CONV1_CHout][CONV1_CHin][CONV_K][CONV_K];
    float conv1_bias_buf[CONV1_CHout];
    float conv2_W[CONV2_CHout][CONV2_CHin];
    float conv2_bias_buf[CONV2_CHout];
    float fc2_weights_buf[FC2_INPUT_NUM1];
    float fc2_bias_buf[FC2_OUTPUT_NUM1];

    for (int i = 0; i < FC1_OUTPUT_NUM1; i++)
    {
        /* code */
        fc1_bias_buf[i] = *fc1_bias++;
    }

    for (int m = 0; m < CONV_K; m++)
    {
        /* code */
        for (int n = 0; n < CONV_K; n++)
        {
#pragma HLS PIPELINE
            /* code */
			for (int j = 0; j < CONV1_CHin; j++)
			{
				/* code */
				for (int i = 0; i < CONV1_CHout; i++)
				{
					/* code */
            		conv1_W[i][j][m][n] = *conv1_w++;
				}
				
			}
			
        }    
    }
    for (int i = 0; i < CONV1_CHout; i++)
	{
			/* code */
		conv1_bias_buf[i] = *conv1_bias++;
	}

    for (int i = 0; i < FC2_OUTPUT_NUM1; i++)
    {
        /* code */
        fc2_bias_buf[i] = *fc2_bias++;
    }

	for (int i = 0; i < CONV2_CHout; i++)
	{
		/* code */
		conv2_bias_buf[i] = *conv2_bias++;
	}

    for (int i = 0; i < input_R; i++)
    {
        /* code */
        for (int j = 0; j < input_C; j++)
        {
#pragma HLS PIPELINE
            /* code */
            for (int chi = 0; chi < input_channel; chi++)
            {
                /* code */
                input_data_buf[chi][i][j] = *input_data++;
            }
        }
    }

    net_cal:
    {
        for (int i = 0; i < CONV1_CHout; i++)
		{
			/* code */
			for (int j = 0; j < CONV1_R; j++)
			{
				/* code */
				for (int m = 0; m < CONV1_C; m++)
				{
					/* code */
					conv1_out[i][j][m] = 0;
				}
				
			}
			
		}
        /**************** CONV1_LAYER****************************/
        conv_layer1(input_data_buf,conv1_out,conv1_W,conv1_bias_buf,1);

        /**************** POOLING1_LAYER****************************/
        pooling_layer1(conv1_out,pooling1_out);

        /**************** CONV2_LAYER****************************/
        for (int i = 0; i < CONV2_CHout; i++)
		{
			/* code */
			for (int j = 0; j < CONV2_R; j++)
			{
				/* code */
				for (int m = 0; m < CONV2_C; m++)
				{
					/* code */
					conv2_out[i][j][m] = 0;
				}
				
			}
			
		}

        for (int kr = 0; kr < CONV_K; kr++)
	    {
		    /* code */
		    for (int kc = 0; kc < CONV_K; kc++)
		    {
                for (int i = 0; i < CONV2_CHin; i++)
                {
                    /* code */
                    for (int j = 0; j < CONV2_CHout; j++)
                    {
            #pragma HLS PIPELINE
                        /* code */
                        conv2_W[j][i] = *conv2_w++;
                    }    
                }
                conv_layer2(pooling1_out,conv2_out,conv2_W,conv2_bias_buf,1,kr,kc);
            }
        }
        bias:for (int i = 0; i < CONV2_CHout; i++)
		{
			/* code */
			for (int j = 0; j < CONV2_R; j++)
			{
				/* code */
				for (int m = 0; m < CONV2_C; m++)
				{
					/* code */
					conv2_out[i][j][m] += conv2_bias_buf[i];
					conv2_out[i][j][m] = (conv2_out[i][j][m]>0) ? conv2_out[i][j][m] : 0;
				}
				
			}
			
		}



        /**************** POOLING2_LAYER****************************/
        pooling_layer2(conv2_out,pooling2_out);


        /**************** FULL_CONNECTION1_LAYER****************************/
        for (int i = 0; i < FC1_INPUT_NUM1; i++)
        {       
            for (int j = 0; j < FC1_OUTPUT_NUM1; j++)
                {
    #pragma HLS PIPELINE
                    /* code */
                    fc1_weights_buf[j] = *fc1_w++;
                }    
                if(i == 0)
                {
                    for (int cho = 0; cho < FC1_OUTPUT_NUM1; cho++)
                    {
                        /* code */
                        fc1_out[cho] = 0;
                    }
                    
                }
            full_connection_layer1(pooling2_out,fc1_out,fc1_weights_buf,fc1_bias_buf,1,i);
        }

        for (int i = 0; i < FC1_OUTPUT_NUM1; i++)
        {
            /* code */
            fc1_out[i] += fc1_bias_buf[i];
            fc1_out[i] = (fc1_out[i] > 0) ? fc1_out[i] : 0;
        }
        

        /**************** FULL_CONNECTION2_LAYER****************************/
        for (int i = 0; i < FC2_INPUT_NUM1; i++)
        {
            load_data:
            {
                load_weights:for (int j = 0; j < FC2_OUTPUT_NUM1; j++)
                    {
        #pragma HLS PIPELINE
                        /* code */
                        fc2_weights_buf[j] = *fc2_w++;
                    }    
                if(i == 0)
                {
                    for (int cho = 0; cho < FC2_OUTPUT_NUM1; cho++)
                    {
                        /* code */
                        output_data_buf[cho] = 0;
                    }
                    
                }
                full_connection_layer2(fc1_out,output_data_buf,fc2_weights_buf,fc2_bias_buf,0,i);
                    /* code */ 
            }
            
        }
        
        for (int i = 0; i < FC2_OUTPUT_NUM1; i++)
        {
            /* code */
            output_data_buf[i] += fc2_bias_buf[i];
        }
        
    }


    for (int i = 0; i < output_length; i++)
    {
#pragma HLS PIPELINE
        /* code */
        *output_data++ = output_data_buf[i];
    }
    
    return;


}
