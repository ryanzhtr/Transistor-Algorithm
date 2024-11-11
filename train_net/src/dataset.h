// dataset.h
#pragma once
#include <torch/torch.h>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

namespace fs = std::filesystem;

class NumberDataset : public torch::data::Dataset<NumberDataset> {
public:
    // 接收数据集根目录路径和训练/测试模式标志
    // 调用loadImages加载图像
    // 初始化随机数生成器用于数据增强
    NumberDataset(const std::string& root_dir, bool train = true) 
        : train_(train) {
        loadImages(root_dir);
        
        // 初始化随机数生成器
        std::random_device rd;
        rng_ = std::mt19937(rd());
    }

    torch::data::Example<> get(size_t index) override {
        cv::Mat image = cv::imread(image_paths_[index], cv::IMREAD_GRAYSCALE);
        if(image.empty()) {
            throw std::runtime_error("Failed to load image: " + image_paths_[index]);
        }
        
        cv::resize(image, image, cv::Size(64, 48));
        // 50%概率进行随机旋转（±10度）
        // 50%概率进行随机平移（±5像素）
        if (train_) {
            std::uniform_int_distribution<int> dist(0, 1);
            std::uniform_real_distribution<double> angle_dist(-10.0, 10.0);
            std::uniform_int_distribution<int> shift_dist(-5, 5);
            
            if (dist(rng_)) {
                double angle = angle_dist(rng_);
                cv::Point2f center(image.cols/2.0f, image.rows/2.0f);
                cv::Mat rotation = cv::getRotationMatrix2D(center, angle, 1.0);
                cv::warpAffine(image, image, rotation, image.size());
            }
            
            if (dist(rng_)) {
                int tx = shift_dist(rng_);
                int ty = shift_dist(rng_);
                cv::Mat trans = (cv::Mat_<float>(2,3) << 1, 0, tx, 0, 1, ty);
                cv::warpAffine(image, image, trans, image.size());
            }
        }

        torch::Tensor img_tensor = torch::from_blob(image.data, 
            {1, image.rows, image.cols}, torch::kUInt8).to(torch::kFloat32);
        // 将像素值从[0,255]转换到[0,1]
        // 然后转换到[-1,1]范围
        img_tensor = img_tensor / 255.0;
        img_tensor = (img_tensor - 0.5) / 0.5;
        
        return {img_tensor, torch::tensor(labels_[index], torch::kLong)};
    }

    torch::optional<size_t> size() const override {
        return image_paths_.size();
    }

private:
    // 检查目录是否存在
    // 遍历目录结构：
    // 第一层目录名作为标签（如"0","1","2"等）
    // 收集每个标签目录下的所有图片文件
    // 存储图片路径和对应标签
    // 对训练集进行随机打乱
    void loadImages(const std::string& root_dir) {
        if (!fs::exists(root_dir)) {
            throw std::runtime_error("Directory not found: " + root_dir);
        }

        for (const auto& entry : fs::directory_iterator(root_dir)) {
            if (entry.is_directory()) {
                std::string label_str = entry.path().filename().string();
                int label = std::stoi(label_str);
                
                for (const auto& img_file : fs::directory_iterator(entry.path())) {
                    if (img_file.path().extension() == ".jpg" || 
                        img_file.path().extension() == ".png") {
                        image_paths_.push_back(img_file.path().string());
                        labels_.push_back(label);
                    }
                }
            }
        }
        
        if (image_paths_.empty()) {
            throw std::runtime_error("No images found in: " + root_dir);
        }

        // 打乱数据集
        if (train_) {
            // 创建索引数组
            std::vector<size_t> indices(image_paths_.size());
            std::iota(indices.begin(), indices.end(), 0); // 填充0,1,2,...
            
            // 打乱索引
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(indices.begin(), indices.end(), g);
            
            // 使用打乱的索引重新排列数据
            std::vector<std::string> temp_paths(image_paths_.size());
            std::vector<int> temp_labels(labels_.size());
            
            for (size_t i = 0; i < indices.size(); ++i) {
                temp_paths[i] = image_paths_[indices[i]];
                temp_labels[i] = labels_[indices[i]];
            }
            
            // 交换数据
            image_paths_ = std::move(temp_paths);
            labels_ = std::move(temp_labels);
        }

        std::cout << "Loaded " << image_paths_.size() << " images from " << root_dir << std::endl;
    }


    std::vector<std::string> image_paths_;
    std::vector<int> labels_;
    bool train_;
    std::mt19937 rng_;
};