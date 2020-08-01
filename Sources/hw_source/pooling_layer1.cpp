#include "pooling_layer1.h"

void pooling_layer1(
    float In[CHin][Rin][Cin],
	float Out[CHout][R][C]
)
{
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
    

    
}