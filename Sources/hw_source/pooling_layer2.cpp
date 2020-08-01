#include "pooling_layer2.h"

void pooling_layer2(
    float In[CHin][Rin][Cin],
	float out_1D[CHout*R*C]
)
{
    float Out[CHout][R][C];
    for (int chi = 0; chi < CHin; chi++)
    {
        for (int r = 0; r < R; r++)
        {
            /* code */
            for (int c = 0; c < C; c++)
            {
                /* code */
                float max = In[chi][2*r][2*c];
                for (int kr = 0; kr < K; kr++)
                {
                    /* code */
                    for (int kc = 0; kc < K; kc++)
                    {
                        /* code */
                        max = (In[chi][2*r+kr][2*c+kc] > max) ? In[chi][2*r+kr][2*c+kc] : max;
                    }
                    
                }
                Out[chi][r][c] = max;
            }
            
        }
        /* code */
    }
    
    int cnt = 0;
    for (int r = 0; r < R; r++)
    {
        /* code */
        for (int c = 0; c < C; c++)
        {
            /* code */
            for (int cho = 0; cho < CHout; cho++)
            {
                #pragma HLS PIPELINE
                /* code */
                out_1D[cnt] = Out[cho][r][c];
                cnt++;
            }
            
        }
        
    }
    
}