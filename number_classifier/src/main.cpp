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
    
    for (auto& batch : *data_loader) {
        auto data = batch.data.to(torch::kFloat32);
        auto target = batch.target.squeeze().to(torch::kLong);
        
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
                      << " [" << batch_idx * batch.data.size(0) << "/" 
                      << dataset_size << "] Loss: " 
                      << running_loss / batch_idx << std::flush;
        }
    }
    
    float accuracy = 100.0f * static_cast<float>(correct) / static_cast<float>(dataset_size);
    std::cout << "\nTrain Epoch: " << epoch << " Average loss: " 
              << running_loss / batch_idx 
              << " Accuracy: " << accuracy << "%" << std::endl;
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
        
        auto train_dataset = NumberDataset(train_dir, true)
            .map(torch::data::transforms::Stack<>());
        auto test_dataset = NumberDataset(test_dir, false)
            .map(torch::data::transforms::Stack<>());
        
        auto train_loader = torch::data::make_data_loader<torch::data::samplers::RandomSampler>(
            std::move(train_dataset),
            torch::data::DataLoaderOptions().batch_size(32).workers(4));
            
        auto test_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
            std::move(test_dataset),
            torch::data::DataLoaderOptions().batch_size(32).workers(4));
        
        float best_accuracy = 0.0f;
        size_t num_epochs = 50;
        
        for (size_t epoch = 1; epoch <= num_epochs; ++epoch) {
            train(*model, train_loader, optimizer, epoch, train_dataset.size().value());
            float accuracy = validate(*model, test_loader, test_dataset.size().value());
            
            if (accuracy > best_accuracy) {
                best_accuracy = accuracy;
                // 修改保存模型的方式
                torch::save(model, "../models/best_model.pt");
                std::cout << "New best model saved!" << std::endl;
            }
        }
        
        std::cout << "Best accuracy: " << best_accuracy << "%" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}