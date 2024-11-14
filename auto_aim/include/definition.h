#ifndef DEFINITION_H
#define DEFINITION_H

#include <opencv2/opencv.hpp>
#include <torch/torch.h>
#include <vector>
#include <cmath>

// 定义敌人颜色
enum class EnemyColor {
    RED = 0,
    BLUE = 1
};

// 定义装甲板大小
enum class ArmorSize {
    SMALL = 0,
    BIG = 1
};

// Light 类：表示灯条
class Light {
public:
    cv::RotatedRect el;
    cv::Point2f top, bottom;
    double length, width;
    double tilt_angle;

    Light(const cv::RotatedRect &box);
};

// Armor 类：表示装甲板
class Armor {
public:
    cv::RotatedRect rect;
    std::vector<cv::Point2f> points;
    ArmorSize size;
    int id;
    std::vector<int> light_ids;
    float prob;

    Armor(const cv::RotatedRect &rect, const std::vector<cv::Point2f> &points, ArmorSize size, int id, const std::vector<int> &light_ids);
};

// LeNet 类：神经网络模型
class LeNet : public torch::nn::Module {
public:
    LeNet();

    torch::Tensor forward(torch::Tensor x);

private:
    torch::nn::Conv2d conv1, conv2;
    torch::nn::MaxPool2d pool1, pool2;
    torch::nn::Linear fc1, fc2, fc3;
    torch::nn::Dropout dropout;
};

// PnPsolver 类：用于相机的PnP求解
class PnPsolver {
public:
    static constexpr double small_armor_length = 136;
    static constexpr double small_armor_width = 57;
    static constexpr double big_armor_length = 224.5;
    static constexpr double big_armor_width = 57;

    static cv::Mat camera_matrix;
    static cv::Mat dist_coeffs;
};

#endif // DEFINITION_H
