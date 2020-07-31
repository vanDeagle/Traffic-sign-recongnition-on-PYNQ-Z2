#include "pooling_layer1.h"

int main()
{
    float In[CHin][Rin][Cin];
	float Out[CHout][R][C];

    int temp = 0;

    for (int i = 0; i < CHin; i++)
    {
        /* code */
        for (int j = 0; j < Rin; j++)
        {
            /* code */
            for (int m = 0; m < Cin; m++)
            {
                /* code */
                In[i][j][m] = temp++;
            }
            
        }
        
    }

    pooling_layer1(In,Out);
    return 0;
}