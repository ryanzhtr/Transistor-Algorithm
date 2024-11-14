#ifndef LIGHT_H
#define LIGHT_H

#include <opencv2/opencv.hpp>

class Light {
public:
    Light() : angle(0.0), length(0.0), width(0.0) {}

    Light(cv::RotatedRect rect)
        : rect(rect), angle(rect.angle), length(rect.size.height), width(rect.size.width) {}

    cv::Point2f getPosition() const {
        return rect.center;
    }

    float getAngle() const { return angle; }
    float getLength() const { return length; }
    float getWidth() const { return width; }

    const cv::RotatedRect& getRect() const { return rect; }

private:
    cv::RotatedRect rect;
    float angle;  // 灯条角度
    float length; // 灯条长度
    float width;  // 灯条宽度
};

#endif // LIGHT_H
