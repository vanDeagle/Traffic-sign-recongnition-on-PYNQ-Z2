#ifndef __FULL_CONNECTION_LAYER3_H__
#define __FULL_CONNECTION_LAYER3_H__

#define INPUT_NUM1      84
#define OUTPUT_NUM1     43


extern void full_connection_layer3(
    float input_data_buf[INPUT_NUM1],
    float output_data_buf[OUTPUT_NUM1],
    float *weights,
    bool active   
);

#endif
