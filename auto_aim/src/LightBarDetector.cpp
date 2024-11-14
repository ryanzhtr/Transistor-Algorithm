// #include "LightBarDetector.h"
// #include <opencv2/opencv.hpp>
// #include <cmath>

// Light::Light(const cv::RotatedRect& rect) : el(rect) {
//     calculateLengthWidth();
// }
// class Light {
// // public:
// //     Light(const cv::RotatedRect& rect);

// //     // 成员变量
// //     cv::RotatedRect el;   // 旋转矩形（椭圆拟合结果）
// //     float length;         // 长度
// //     float width;          // 宽度

// //     // 方法：计算灯条的长度、宽度
// //     void calculateLengthWidth();
// //     void calculateDimensions();

// // private:
// //     const float max_wh_ratio = 10;
// //     const float min_wh_ratio = 0.1;
// // };ght);
//     width = std::min(el.size.width, el.size.height);
// }

// LightBarDetector::LightBarDetector(const Params& params) : params(params) {
// }

// void LightBarDetector::detectLights(const std::vector<cv::Mat>& images) {
//     lights.clear();  // 清除之前的检测结果
    
//     for (const auto& img : images) {
//         std::vector<cv::RotatedRect> detectedRects = detectLightRects(img);
//         for (const auto& rect : detectedRects) {
//             lights.emplace_back(rect);
//         }
//     }
// }

// std::vector<cv::RotatedRect> LightBarDetector::detectLightRects(const cv::Mat& img) {
//     std::vector<cv::RotatedRect> rects;
    
//     // 1. 通道分离，提取蓝色通道
//     std::vector<cv::Mat> channels;
//     cv::split(img, channels);
//     cv::Mat blue = channels[0];  // BGR格式中的蓝色通道
    
//     // 2. 自适应阈值处理
//     cv::Mat binary;
//     cv::adaptiveThreshold(blue, binary, 255, 
//                          cv::ADAPTIVE_THRESH_GAUSSIAN_C,
//                          cv::THRESH_BINARY, 
//                          11, -5);  // 参数可调

//     // 3. 形态学操作，去除噪点
//     cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
//     cv::morphologyEx(binary, binary, cv::MORPH_OPEN, element);
//     cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, element);

//     // 4. 查找轮廓
//     std::vector<std::vector<cv::Point>> contours;
//     cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

//     // 5. 轮廓筛选
//     for (const auto& contour : contours) {
//         // 面积过滤
//         double area = cv::contourArea(contour);
//         if (area < params.light_min_area) continue;

//         // 轮廓拟合椭圆
//         if (contour.size() < 5) continue;  // 至少需要5个点才能拟合椭圆
//         cv::RotatedRect rect = cv::fitEllipse(contour);

//         // 获取灯条的长宽
//         float width = std::min(rect.size.width, rect.size.height);
//         float length = std::max(rect.size.width, rect.size.height);
//         float ratio = length / width;

//         // 角度计算和调整
//         float angle = rect.angle;
//         if (rect.size.width < rect.size.height) {
//             angle = angle + 90;
//         }
        
//         // 确保角度在 [-90, 90] 范围内
//         while (angle > 90) angle -= 180;
//         while (angle < -90) angle += 180;

//         // 条件筛选
//         bool isValidLight = ratio >= params.min_light_wh_ratio &&
//                           ratio <= params.max_light_wh_ratio &&
//                           length >= params.min_light_height &&
//                           std::abs(angle) <= params.light_max_tilt_angle;

//         if (isValidLight) {
//             rects.push_back(rect);
//         }
//     }

//     return rects;
// }

// void LightBarDetector::processLights() {
//     filterLights();
//     updateLights();
// }

// void LightBarDetector::filterLights() {
//     lights.erase(std::remove_if(lights.begin(), lights.end(),
//         [this](const Light& light) {
//             return light.length < params.min_light_height || 
//                    light.length / light.width > params.max_light_wh_ratio ||
//                    light.length / light.width < params.min_light_wh_ratio;
//         }), lights.end());
// }

// void LightBarDetector::updateLights() {
//     // 暂时不实现更新逻辑
// }
#include "LightBarDetector.h"
#include <opencv2/opencv.hpp>
#include <cmath>

Light::Light(const cv::RotatedRect& rect) : el(rect) {
    calculateLengthWidth();
    calculateTopBottom();
}

void Light::calculateLengthWidth() {
    length = std::max(el.size.width, el.size.height);
    width = std::min(el.size.width, el.size.height);
    
    // Calculate tilt angle
    tilt_angle = el.angle;
    if (el.size.width < el.size.height) {
        tilt_angle = tilt_angle + 90;
    }
    
    // Normalize angle to [-90, 90]
    while (tilt_angle > 90) tilt_angle -= 180;
    while (tilt_angle < -90) tilt_angle += 180;
    tilt_angle = std::abs(tilt_angle);
}

void Light::calculateTopBottom() {
    cv::Point2f vertices[4];
    el.points(vertices);
    
    // Find top and bottom points
    if (el.size.width < el.size.height) {
        top = vertices[0];
        bottom = vertices[2];
    } else {
        top = vertices[1];
        bottom = vertices[3];
    }
}

std::vector<cv::RotatedRect> LightBarDetector::detectLightRects(const cv::Mat& img) {
    std::vector<cv::RotatedRect> rects;
    
    // 1. Extract blue channel and create binary image
    std::vector<cv::Mat> channels;
    cv::split(img, channels);
    cv::Mat blue = channels[0];
    
    // 2. Create color difference image
    cv::Mat color_diff;
    if (params.enemy_color == RED) {
        cv::subtract(channels[2], channels[0], color_diff); // RED - BLUE
    } else {
        cv::subtract(channels[0], channels[2], color_diff); // BLUE - RED
    }
    
    // 3. Threshold and preprocess
    cv::Mat binary;
    cv::threshold(color_diff, binary, params.color_threshold, 255, cv::THRESH_BINARY);
    
    // Apply Gaussian blur
    cv::GaussianBlur(binary, binary, cv::Size(5, 5), 0);
    
    // Morphological operations
    cv::Mat element = cv2::getStructuringElement(cv2::MORPH_ELLIPSE, cv::Size(7, 7));
    cv::dilate(binary, binary, element);
    
    // 4. Find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 5. Filter and process contours
    for (const auto& contour : contours) {
        if (contour.size() < 5) continue;
        
        double area = cv::contourArea(contour);
        if (area < params.light_min_area) continue;

        cv::RotatedRect rect = cv::fitEllipse(contour);
        Light light(rect);
        
        // Apply filters based on light bar properties
        if (light.width == 0) continue;
        
        float wh_ratio = light.length / light.width;
        if (wh_ratio < 1) continue;
        
        if (wh_ratio < params.min_light_wh_ratio || 
            wh_ratio > params.max_light_wh_ratio) continue;
            
        if (light.tilt_angle > params.light_max_tilt_angle) continue;

        rects.push_back(rect);
    }

    return rects;
}