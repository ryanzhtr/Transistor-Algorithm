// model.h
#pragma once
#include <torch/torch.h>
//8类第0类为没有识别到
class NumberNet : public torch::nn::Module {
public:
    NumberNet(int64_t num_classes = 8) {
        // 卷积层
        conv1 = register_module("conv1", 
            torch::nn::Conv2d(torch::nn::Conv2dOptions(1, 32, 3).padding(1)));
        conv2 = register_module("conv2", 
            torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 64, 3).padding(1)));
        conv3 = register_module("conv3", 
            torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 128, 3).padding(1)));
        
        // 批归一化层
        bn1 = register_module("bn1", torch::nn::BatchNorm2d(32));
        bn2 = register_module("bn2", torch::nn::BatchNorm2d(64));
        bn3 = register_module("bn3", torch::nn::BatchNorm2d(128));
        
        // 全连接层
        int fc_input_size = 128 * (64 / 8) * (48 / 8);
        fc1 = register_module("fc1", torch::nn::Linear(fc_input_size, 512));
        fc2 = register_module("fc2", torch::nn::Linear(512, num_classes));
        
        // Dropout层
        dropout = register_module("dropout", torch::nn::Dropout(0.5));
    }

    torch::Tensor forward(torch::Tensor x) {
        x = torch::relu(bn1(conv1(x)));
        x = torch::max_pool2d(x, 2);
        
        x = torch::relu(bn2(conv2(x)));
        x = torch::max_pool2d(x, 2);
        
        x = torch::relu(bn3(conv3(x)));
        x = torch::max_pool2d(x, 2);
        
        x = x.flatten(1);
        x = torch::relu(fc1(x));
        x = dropout(x);
        x = fc2(x);
        
        return torch::log_softmax(x, 1);
    }

    torch::nn::Conv2d conv1{nullptr}, conv2{nullptr}, conv3{nullptr};
    torch::nn::BatchNorm2d bn1{nullptr}, bn2{nullptr}, bn3{nullptr};
    torch::nn::Linear fc1{nullptr}, fc2{nullptr};
    torch::nn::Dropout dropout{nullptr};
};