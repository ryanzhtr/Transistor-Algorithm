// #ifndef LIGHT_BAR_DETECTOR_H
// #define LIGHT_BAR_DETECTOR_H

// #include <opencv2/opencv.hpp>
// #include <vector>
// #include "Params.h"

// // Light 类，表示每个灯条的特征
// class Light {
// public:
//     Light(const cv::RotatedRect& rect);

//     // 成员变量
//     cv::RotatedRect el;   // 旋转矩形（椭圆拟合结果）
//     float length;         // 长度
//     float width;          // 宽度

//     // 方法：计算灯条的长度、宽度
//     void calculateLengthWidth();
//     void calculateDimensions();

// private:
//     const float max_wh_ratio = 10;
//     const float min_wh_ratio = 0.1;
// };

// class LightBarDetector {
// public:
//     LightBarDetector(const Params& params);  // 构造函数，接收参数

//     // 方法：用于检测灯条
//     void detectLights(const std::vector<cv::Mat>& images);
//     void processLights();

// private:
//     Params params;    // 使用 Params 类来管理所有参数
//     std::vector<Light> lights;   // 存储灯条对象
//     void filterLights();
//     void updateLights();

//     // 其他辅助函数
//     std::vector<cv::RotatedRect> detectLightRects(const cv::Mat& img);
// };

// #endif // LIGHT_BAR_DETECTOR_H
#ifndef LIGHT_BAR_DETECTOR_H
#define LIGHT_BAR_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Params.h"

// Light 类，表示每个灯条的特征
// class Light {
// public:
//     Light(const cv::RotatedRect& rect);

//     // 成员变量
//     cv::RotatedRect el;   // 旋转矩形（椭圆拟合结果）
//     float length;         // 长度
//     float width;          // 宽度

//     // 方法：计算灯条的长度、宽度
//     void calculateLengthWidth();
//     void calculateDimensions();

// private:
//     const float max_wh_ratio = 10;
//     const float min_wh_ratio = 0.1;
// };
class Light {
public:
    Light(const cv::RotatedRect& rect);

    // 成员变量
    cv::RotatedRect el;   // 旋转矩形（椭圆拟合结果）
    float length;         // 长度
    float width;          // 宽度

    // const member variables
    const float max_wh_ratio = 10;    // 最大宽高比
    const float min_wh_ratio = 0.1;   // 最小宽高比

    // 方法：计算灯条的长度、宽度
    void calculateLengthWidth();
    void calculateDimensions();

    // 显式移动构造函数
    Light(Light&& other) noexcept 
        : el(std::move(other.el)), length(other.length), width(other.width) {}

    // 显式移动赋值操作符
    Light& operator=(Light&& other) noexcept {
        if (this != &other) {
            el = std::move(other.el);
            length = other.length;
            width = other.width;
        }
        return *this;
    }

private:
    // 无需修改其他代码
};

class LightBarDetector {
public:
    LightBarDetector(const Params& params);  // 构造函数，接收参数

    // 方法：用于检测灯条
    void detectLights(const std::vector<cv::Mat>& images);
    void processLights();

    // 新增的 getter 方法
    const std::vector<Light>& getLights() const { return lights; }

private:
    Params params;    // 使用 Params 类来管理所有参数
    std::vector<Light> lights;   // 存储灯条对象
    void filterLights();
    void updateLights();

    // 其他辅助函数
    std::vector<cv::RotatedRect> detectLightRects(const cv::Mat& img);
};

#endif // LIGHT_BAR_DETECTOR_H
