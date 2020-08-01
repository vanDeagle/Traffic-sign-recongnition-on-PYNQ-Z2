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
		
				

}
