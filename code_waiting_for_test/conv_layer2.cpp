#include "conv_layer2.h"

void conv_layer2(float In[CHin][Rin][Cin],float Out[CHout][R][C],float W[CHout][CHin],float bias_buf[CHout],bool active,int kr,int kc)
{

float Out_buf[CHout][R][C];
#pragma HLS ARRAY_PARTITION variable=Out cyclic factor=2 dim=1
#pragma HLS ARRAY_PARTITION variable=W cyclic factor=4 dim=1




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
		
				
	

	if((kr == K)&(kc == K))
	{
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
	return;
}
