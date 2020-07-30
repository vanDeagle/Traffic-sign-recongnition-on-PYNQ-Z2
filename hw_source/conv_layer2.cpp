#include "conv_layer2.h"

void conv_layer2(float In[CHin][Rin][Cin],float Out[CHout][R][C],float *Weight,float *bias,bool active)
{

float W[CHout][CHin];
float bias_buf[CHout];
float Out_buf[CHout][R][C];
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi depth=256 port=Weight offset=slave
#pragma HLS INTERFACE m_axi depth=256 port=bias offset=slave
#pragma HLS ARRAY_PARTITION variable=Out cyclic factor=2 dim=1
#pragma HLS ARRAY_PARTITION variable=W cyclic factor=4 dim=1


	for (int kr = 0; kr < K; kr++)
	{
		/* code */
		for (int kc = 0; kc < K; kc++)
		{
			load_weights:for (int i = 0; i < CHout; i++)
			{
				/* code */
				for (int j = 0; j < CHin; j++)
				{
		#pragma HLS PIPELINE
					/* code */
					W[i][j] = *Weight++;
				}    
			}

			cal_Row:
			for(int r=0; r<R; r++)				
			{
				Column:
				for(int c=0; c<C; c++)	
				{		
					Output_Channel:
					for(int chi=0; chi<CHin; chi++)
					{
						#pragma HLS PIPELINE
						Input_Channel:
						for(int cho=0; cho<CHout; cho++)						
						{
							Out_buf[cho][r][c] += In[chi][r+kr][c+kc] * W[cho][chi];
						}
					}
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
