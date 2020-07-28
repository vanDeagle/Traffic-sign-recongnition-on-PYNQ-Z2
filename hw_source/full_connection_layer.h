#ifndef FULL_CONNECTION_LAYER_H
#define FULL_CONNECTION_LAYER_H

#define INPUT_NUM1      3
#define INPUT_NUM2      3
#define OUTPUT_NUM1     5
#define OUTPUT_NUM2     5


extern void full_connection_layer1(
    float *input_data,
    float *output_data,
    float *weights,
    bool active   
);

#endif