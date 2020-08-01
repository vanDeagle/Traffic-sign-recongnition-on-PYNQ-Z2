# Traffic-sign-recongnition-on-PYNQ-Z2
> 2020年新工科联盟-Xilinx暑期学校（Summer School）项目。

设计概要：

	本设计是基于神经网络LeNet-5的网络架构进行参数上的微调所形成的神经网络结构。经TensorFlow2进行训练得到各层的权重参数和偏置参数，再利用HLS在PL端形成神经网络的加速器，将权重和偏置参数导入PL端中实现神经网络加速的目的。

	本设计的目的是加速神经网络最终达到能够识别交通标识。在其中，我们学习到了如何利用TensorFlow2进行网络结构的搭建和训练，如果利用HLS快速的搭建已知的网络结构，如何利用HLS合理分配存储空间和缓存实现数据的高速流通。

	交通标识的识别在实际中有运用价值，在无人驾驶等智能驾驶领域都需要有交通标志识别的运用空间。但本设计暂时还未训练带有交通标识定位的能力（只能进行分类），所以还有发展空间。


计划实现：

    1、完成神经网络的训练。
    2、完成神经网络加速器的设计。
    3、完成PS端控制的实现。
    4、将PS端和PL端结合完成整个神经网络加速的设计。
    5、进一步优化系统的延时，提高加速的效果。

已实现功能：

    1、完成神经网络的训练。
    2、完成神经网络加速器的设计。
    3、完成PS端控制实现。
    4、完成PS端和PL端结合完成整个神经网络加速的设计


组内成员：

范峻岭  20BO179A  西南交通大学

孔欣杰  20BO177A  西南交通大学

翟林帆  20BO178A  西南交通大学

使用平台：pynq-z2（无其他外设）

仓库目录：

--> Sources

    --> hw_sources

      ---> LeNet.cpp(顶层文件)  : 所有层均位于此文件中描述

  --> hw_lib:

    ---> layer_lib.h


  --> sw_sources:

    ---> cnn.py

    ---> data_pre_handle.py

    ---> pynq_exec.ipynb

--> ExecutableFiles:

    --> hw_bitstream:

      --> LeNet-5.bit

      --> LeNet-5.hwh

      --> LeNet-5.tcl

    --> jupyter_file:

      --> pynq_exec.ipynb

--> Others:

    --> register_address:

      --> xlenet_hw_hw.h (the address of control registers for axi_lite write or read)

    --> weight_data:

      --> conv1_bias.npy

      --> conv1_weight.npy

      --> conv2_bias.npy

      --> conv2_weight.npy

      --> fc1_bias.npy

      --> fc1_weight.npy

      --> fc2_bias.npy

      --> fc1_weight.npy





