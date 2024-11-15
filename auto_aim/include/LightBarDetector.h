#ifndef LIGHTBARDETECTOR_H
#define LIGHTBARDETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Params.h"

class Light {
public:
    cv::RotatedRect el;  // 旋转矩形
    float length = 0;    // 灯条的长度
    float width = 0;     // 灯条的宽度
    
    Light(const cv::RotatedRect& rect);

    void calculateLengthWidth();
    void calculateDimensions();
    
    cv::RotatedRect getRect() const { return el; }
};

class LightBarDetector {
public:
    LightBarDetector(const Params& params);

    void detectLights(const std::vector<cv::Mat>& images);
    void processLights();
    std::vector<Light> getLights() const { return lights; }

private:
    Params params;
    std::vector<Light> lights;

    std::vector<cv::RotatedRect> detectLightRects(const cv::Mat& img);
    void filterLights();
    void updateLights();
};

#endif // LIGHTBARDETECTOR_H
