// ==============================================================
// File generated on Fri Jul 31 10:41:52 +0800 2020
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXILiteS
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of conv1_w
//        bit 31~0 - conv1_w[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of conv1_bias
//        bit 31~0 - conv1_bias[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of conv2_w
//        bit 31~0 - conv2_w[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of conv2_bias
//        bit 31~0 - conv2_bias[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of fc1_w
//        bit 31~0 - fc1_w[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of fc1_bias
//        bit 31~0 - fc1_bias[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of fc2_w
//        bit 31~0 - fc2_w[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of fc2_bias
//        bit 31~0 - fc2_bias[31:0] (Read/Write)
// 0x4c : reserved
// 0x50 : Data signal of input_data
//        bit 31~0 - input_data[31:0] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of output_data
//        bit 31~0 - output_data[31:0] (Read/Write)
// 0x5c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XLENET_HW_AXILITES_ADDR_AP_CTRL          0x00
#define XLENET_HW_AXILITES_ADDR_GIE              0x04
#define XLENET_HW_AXILITES_ADDR_IER              0x08
#define XLENET_HW_AXILITES_ADDR_ISR              0x0c
#define XLENET_HW_AXILITES_ADDR_CONV1_W_DATA     0x10
#define XLENET_HW_AXILITES_BITS_CONV1_W_DATA     32
#define XLENET_HW_AXILITES_ADDR_CONV1_BIAS_DATA  0x18
#define XLENET_HW_AXILITES_BITS_CONV1_BIAS_DATA  32
#define XLENET_HW_AXILITES_ADDR_CONV2_W_DATA     0x20
#define XLENET_HW_AXILITES_BITS_CONV2_W_DATA     32
#define XLENET_HW_AXILITES_ADDR_CONV2_BIAS_DATA  0x28
#define XLENET_HW_AXILITES_BITS_CONV2_BIAS_DATA  32
#define XLENET_HW_AXILITES_ADDR_FC1_W_DATA       0x30
#define XLENET_HW_AXILITES_BITS_FC1_W_DATA       32
#define XLENET_HW_AXILITES_ADDR_FC1_BIAS_DATA    0x38
#define XLENET_HW_AXILITES_BITS_FC1_BIAS_DATA    32
#define XLENET_HW_AXILITES_ADDR_FC2_W_DATA       0x40
#define XLENET_HW_AXILITES_BITS_FC2_W_DATA       32
#define XLENET_HW_AXILITES_ADDR_FC2_BIAS_DATA    0x48
#define XLENET_HW_AXILITES_BITS_FC2_BIAS_DATA    32
#define XLENET_HW_AXILITES_ADDR_INPUT_DATA_DATA  0x50
#define XLENET_HW_AXILITES_BITS_INPUT_DATA_DATA  32
#define XLENET_HW_AXILITES_ADDR_OUTPUT_DATA_DATA 0x58
#define XLENET_HW_AXILITES_BITS_OUTPUT_DATA_DATA 32

