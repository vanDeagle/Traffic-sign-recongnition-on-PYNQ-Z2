#ifndef __FULL_CONNECTION_LAYER2_H__
#define __FULL_CONNECTION_LAYER2_H__

#define INPUT_NUM1      64
#define OUTPUT_NUM1     43


extern void full_connection_layer2(
    float input_data_buf[INPUT_NUM1],
    float output_data_buf[OUTPUT_NUM1],
    float weights_buf[INPUT_NUM1],
    float bias_buf[OUTPUT_NUM1],
    bool active,
    int i   
);

#endif