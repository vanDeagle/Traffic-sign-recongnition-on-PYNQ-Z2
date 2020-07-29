#include "conv_layer2.h"

void conv_layer2(float In[CHin][Rin][Cin],float Out[CHout][R][C],float *Weight)
{

float W[CHout][CHin][K][K];
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi depth=30 port=Weight
#pragma HLS array_partition variable=In complete dim=1
#pragma HLS array_partition variable=Out complete dim=1
#pragma HLS array_partition variable=W complete dim=1
#pragma HLS array_partition variable=W complete dim=2

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
							Out[cho][r][c] += In[chi][r+kr][c+kc] * W[cho][chi][kr][kc];
						}
					}
				}
			}
		}
	}

	return;
}
