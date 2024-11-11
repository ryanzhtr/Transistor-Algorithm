// main.cpp
#include <torch/torch.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <memory>
#include "model.h"
#include "dataset.h"

template <typename DataLoader>
void train(
    NumberNet& model,
    DataLoader& data_loader,
    torch::optim::Optimizer& optimizer,
    size_t epoch,
    size_t dataset_size) {
    
    model.train();
    size_t batch_idx = 0;
    float running_loss = 0.0;
    size_t correct = 0;
    size_t total_samples = 0;  // 添加总样本计数
    
    for (auto& batch : *data_loader) {
        auto data = batch.data.to(torch::kFloat32);
        auto target = batch.target.squeeze().to(torch::kLong);
        
        total_samples += data.size(0);  // 累加实际处理的样本数
        
        optimizer.zero_grad();
        auto output = model.forward(data);
        auto loss = torch::nll_loss(output, target);
        
        loss.backward();
        optimizer.step();
        
        running_loss += loss.item().toFloat();
        
        auto pred = output.argmax(1);
        correct += pred.eq(target).sum().item().toLong();
        
        if (batch_idx++ % 100 == 0) {
            std::cout << "\rTrain Epoch: " << epoch 
                      << " [" << total_samples << "/" 
                      << dataset_size << "] Loss: " 
                      << running_loss / batch_idx << std::flush;
        }
    }
    
    // 使用实际处理的样本数计算准确率
    float accuracy = 100.0f * static_cast<float>(correct) / static_cast<float>(total_samples);
    std::cout << "\nTrain Epoch: " << epoch 
              << " Average loss: " << running_loss / batch_idx 
              << " Accuracy: " << accuracy << "% ("
              << correct << "/" << total_samples << ")" << std::endl;
}

template <typename DataLoader>
float validate(
    NumberNet& model,
    DataLoader& data_loader,
    size_t dataset_size) {
    
    model.eval();
    float test_loss = 0;
    size_t correct = 0;
    
    torch::NoGradGuard no_grad;
    
    for (const auto& batch : *data_loader) {
        auto data = batch.data.to(torch::kFloat32);
        auto target = batch.target.squeeze().to(torch::kLong);
        
        auto output = model.forward(data);
        test_loss += torch::nll_loss(output, target, {}, torch::Reduction::Sum).item().toFloat();
        
        auto pred = output.argmax(1);
        correct += pred.eq(target).sum().item().toLong();
    }
    
    test_loss /= static_cast<float>(dataset_size);
    float accuracy = 100.0f * static_cast<float>(correct) / static_cast<float>(dataset_size);
    
    std::cout << "Test set: Average loss: " << test_loss 
              << ", Accuracy: " << accuracy << "%" << std::endl;
              
    return accuracy;
}

int main() {
    try {
        torch::manual_seed(1);
        
        std::cout << "Using device: " 
                  << (torch::cuda::is_available() ? "CUDA" : "CPU") << std::endl;
        
        torch::Device device(torch::cuda::is_available() ? 
            torch::kCUDA : torch::kCPU);
        
        auto model = std::make_shared<NumberNet>();
        model->to(device);
        
        torch::optim::Adam optimizer(model->parameters(), 
            torch::optim::AdamOptions(1e-3));
        
        std::string train_dir = "../data/train";
        std::string test_dir = "../data/test";
        
        // 首先创建数据集并获取大小
        NumberDataset train_dataset(train_dir, true);
        NumberDataset test_dataset(test_dir, false);
        
        // 保存数据集大小
        const size_t train_size = train_dataset.size().value();
        const size_t test_size = test_dataset.size().value();
        
        // 打印数据集信息
        std::cout << "Training dataset size: " << train_size << std::endl;
        std::cout << "Test dataset size: " << test_size << std::endl;
        
        const size_t batch_size = 16;
        
        // 创建数据加载器
        auto train_loader = torch::data::make_data_loader<torch::data::samplers::RandomSampler>(
            train_dataset.map(torch::data::transforms::Stack<>()),
            torch::data::DataLoaderOptions().batch_size(batch_size).workers(4));
            
        auto test_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
            test_dataset.map(torch::data::transforms::Stack<>()),
            torch::data::DataLoaderOptions().batch_size(batch_size).workers(4));
        
        float best_accuracy = 0.0f;
        size_t num_epochs = 50;
        
        for (size_t epoch = 1; epoch <= num_epochs; ++epoch) {
            train(*model, train_loader, optimizer, epoch, train_size);
            float accuracy = validate(*model, test_loader, test_size);
            
            if (accuracy > best_accuracy) {
                best_accuracy = accuracy;
                torch::save(model, "../models/best_model.pt");
                std::cout << "New best model saved! Accuracy: " << accuracy << "%" << std::endl;
            }
        }
        
        std::cout << "Best accuracy: " << best_accuracy << "%" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}