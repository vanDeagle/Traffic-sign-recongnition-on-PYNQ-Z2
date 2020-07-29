#include "conv_layer1.h"

void conv_layer1(float In[CHin][Rin][Cin],float Out[CHout][R][C],float *Weight,float *bias,bool active)
{

float W[CHout][CHin][K][K];
float bias_buf[CHout];
float Out_buf[CHout][R][C];
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi depth=256 port=Weight offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=bias offset=slave
#pragma HLS ARRAY_PARTITION variable=In complete dim=1
#pragma HLS array_partition variable=Out complete dim=1
#pragma HLS ARRAY_PARTITION variable=W cyclic factor=2 dim=1

    load_weights:for (int i = 0; i < CHout; i++)
    {
        /* code */
        for (int j = 0; j < CHin; j++)
        {
#pragma HLS PIPELINE
            /* code */
			for (int m = 0; m < K; m++)
			{
				/* code */
				for (int n = 0; n < K; n++)
				{
					/* code */
            		W[i][j][m][n] = *Weight;
				}
				
			}
			
        }    
    }

	load_bias:
	{
		for (int i = 0; i < CHout; i++)
		{
			/* code */
			bias_buf[i] = *bias++;
		}
		
	}
	Kernel_Row:
	for(int kr=0; kr<K; kr++)					
	{
		Kernel_Column:
		for(int kc=0; kc<K; kc++)				
		{
			Row:
			for(int r=0; r<R; r++)				
			{
				Column:
				for(int c=0; c<C; c++)	
				{		
#pragma HLS PIPELINE
					Output_Channel:
					for(int cho=0; cho<CHout; cho++)
					{
						Input_Channel:
						for(int chi=0; chi<CHin; chi++)						
						{
							Out_buf[cho][r][c] += In[chi][r+kr][c+kc] * W[cho][chi][kr][kc];
						}
					}
				}
			}
		}
	}

	bias:for (int i = 0; i < CHout; i++)
	{
		/* code */
		for (int j = 0; j < R; j++)
		{
			/* code */
			for (int m = 0; m < C; m++)
			{
				/* code */
				Out_buf[i][j][m] += bias[i];
				if(active)
					Out[i][j][m] = (Out_buf[i][j][m]>0) ? Out_buf[i][j][m] : 0;
				else
				{
					Out[i][j][m] = Out_buf[i][j][m];
				}
				
			}
			
		}
		
	}
	

	return;
}
