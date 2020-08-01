#include "conv_layer1.h"

void conv_layer1(float In[CHin][Rin][Cin],float Out[CHout][R][C],float W[CHout][CHin][K][K],float bias_buf[CHout],bool active)
{

#pragma HLS ARRAY_PARTITION variable=Out cyclic factor=2 dim=1
float Out_buf[CHout][R][C];

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
					Out_buf[i][j][m] += bias_buf[i];
					if(active)
						Out[i][j][m] = (Out_buf[i][j][m]>0) ? Out_buf[i][j][m] : 0;
					else
					{
						Out[i][j][m] = Out_buf[i][j][m];
					}
					
				}
				
			}
			
		}
}
