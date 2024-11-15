#include "LightBarDetector.h"
#include <opencv2/opencv.hpp>
#include <cmath>

Light::Light(const cv::RotatedRect& rect) : el(rect) {
    calculateLengthWidth();
}

void Light::calculateLengthWidth() {
    calculateDimensions();
}

void Light::calculateDimensions() {
    length = std::max(el.size.width, el.size.height);
    width = std::min(el.size.width, el.size.height);
}

LightBarDetector::LightBarDetector(const Params& params) : params(params) {}

void LightBarDetector::detectLights(const std::vector<cv::Mat>& images) {
    lights.clear();  // 清除之前的检测结果
    
    for (const auto& img : images) {
        std::vector<cv::RotatedRect> detectedRects = detectLightRects(img);
        for (const auto& rect : detectedRects) {
            lights.emplace_back(rect);
        }
    }
}

std::vector<cv::RotatedRect> LightBarDetector::detectLightRects(const cv::Mat& img) {
    std::vector<cv::RotatedRect> rects;
    
    // 1. 通道分离，提取蓝色通道
    std::vector<cv::Mat> channels;
    cv::split(img, channels);
    cv::Mat blue = channels[0];  // BGR格式中的蓝色通道
    
    // 2. 高斯模糊去噪
    cv::Mat blurred;
    cv::GaussianBlur(blue, blurred, cv::Size(5, 5), 0);
    
    // 3. 自适应阈值处理
    cv::Mat binary;
    cv::adaptiveThreshold(blurred, binary, 255, 
                         cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                         cv::THRESH_BINARY, 
                         11, -5);  // 参数可调

    // 4. 形态学操作，去除噪点
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(binary, binary, cv::MORPH_OPEN, element);
    cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, element);

    // 5. 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 6. 轮廓筛选
    for (const auto& contour : contours) {
        double area = cv::contourArea(contour);
        if (area < params.light_min_area) continue;

        // 轮廓拟合椭圆
        if (contour.size() < 5) continue;  // 至少需要5个点才能拟合椭圆
        cv::RotatedRect rect = cv::fitEllipse(contour);

        // 获取灯条的长宽和长宽比
        float width = std::min(rect.size.width, rect.size.height);
        float length = std::max(rect.size.width, rect.size.height);
        float ratio = length / width;

        // 角度计算和调整
        float angle = rect.angle;
        if (rect.size.width < rect.size.height) {
            angle = angle + 90;
        }
        
        // 确保角度在 [-90, 90] 范围内
        while (angle > 90) angle -= 180;
        while (angle < -90) angle += 180;

        // 条件筛选
        bool isValidLight = ratio >= params.min_light_wh_ratio &&
                            ratio <= params.max_light_wh_ratio &&
                            length >= params.min_light_height &&
                            std::abs(angle) <= params.light_max_tilt_angle;

        if (isValidLight) {
            rects.push_back(rect);
        }
    }

    return rects;
}

void LightBarDetector::processLights() {
    filterLights();
    updateLights();
}

void LightBarDetector::filterLights() {
    lights.erase(std::remove_if(lights.begin(), lights.end(),
        [this](const Light& light) {
            return light.length < params.min_light_height || 
                   light.length / light.width > params.max_light_wh_ratio ||
                   light.length / light.width < params.min_light_wh_ratio;
        }), lights.end());
}

void LightBarDetector::updateLights() {
    // 暂时不实现更新逻辑
}
