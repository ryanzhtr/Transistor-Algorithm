#ifndef ARMOR_H
#define ARMOR_H

#include <opencv2/opencv.hpp>
#include "Light.h"

class Armor {
public:
    Armor() {}

    Armor(const Light& left, const Light& right) {
        this->left = left;
        this->right = right;
        // 根据灯条位置和角度构造装甲板的外接矩形
        calculateBoundingRect();
    }

    void calculateBoundingRect() {
        // 计算装甲板的外接矩形
        cv::Point2f pts[4];
        boundingBox.points(pts);
        for (int i = 0; i < 4; i++) {
            points.push_back(pts[i]);
        }
    }

    bool isValid() const {
        // 判断是否符合装甲板的有效性条件
        return (boundingBox.size.height > 0 && boundingBox.size.width > 0);
    }

    const cv::RotatedRect& getBoundingRect() const { return boundingBox; }

private:
    Light left;
    Light right;
    cv::RotatedRect boundingBox;
    std::vector<cv::Point2f> points;
};

#endif // ARMOR_H
