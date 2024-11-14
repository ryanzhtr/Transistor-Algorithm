#include "DetectArmor.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <torch/script.h>
#include <iostream>
#include <fstream>

DetectArmor::DetectArmor() 
    : enemy_color(NO), detected(0), hei(0.0f), dep(0.0f), bias(0.0f) {
    // 加载 PyTorch 模型
    try {
        module = torch::jit::load("/home/rm2/aim_ws/src/auto_aim/auto_aim/modelEpoch_201.pth");
        binary_module = torch::jit::load("/home/rm2/aim_ws/src/auto_aim/auto_aim/binarymodel.pth");
        model.eval();
        binary.eval();
    } catch (const c10::Error& e) {
        std::cerr << "Error loading model.\n";
    }

    // 初始化滤波器
    Filter = KalmanFilter(0.1f, 0.00001f);
}

DetectArmor::~DetectArmor() {}

void DetectArmor::setEnemyColor(Color color) {
    enemy_color = color;
}

void DetectArmor::setImage(const cv::Mat& img) {
    src = img.clone();
    preprocessImage();
}

void DetectArmor::preprocessImage() {
    // 预处理代码，类似于 Python 版本中的 setImage
    cv::Mat thres_whole = cv::cvtColor(src, cv::COLOR_BGR2GRAY);
    double thres = cv::mean(thres_whole)[0];
    if (thres < 120) thres = 120;
    cv::threshold(thres_whole, thres_whole, thres * 0.30, 255, cv::THRESH_BINARY);

    cv::Mat _max_color = cv::Mat::zeros(src.size(), CV_8UC1);
    if (enemy_color == RED) {
        cv::subtract(src[:,:,2], src[:,:,0], _max_color);
        cv::threshold(_max_color, _max_color, 100, 255, cv::THRESH_BINARY);
    } else {
        cv::subtract(src[:,:,0], src[:,:,2], _max_color);
        cv::threshold(_max_color, _max_color, 100, 255, cv::THRESH_BINARY);
    }

    cv::GaussianBlur(_max_color, _max_color, cv::Size(5, 5), 0);
    _max_color = cv::dilate(_max_color, cv::Mat(), cv::Point(-1, -1), 1, 1);
    ppdForDetect = _max_color & thres_whole;
}

void DetectArmor::findTarget() {
    // 寻找目标，类似于 Python 版本中的 findTarget
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(ppdForDetect, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (auto& contour : contours) {
        try {
            cv::RotatedRect e = cv::fitEllipse(contour);
            Light bd_rect(e);
            if (isValidArmor(bd_rect)) {
                light.push_back(bd_rect);
            }
        } catch (...) {
            continue;
        }
    }

    if (light.size() < 2) return;
    std::sort(light.begin(), light.end(), [](const Light& l1, const Light& l2) {
        return l1.getPosition().x < l2.getPosition().x;
    });

    for (size_t i = 0; i < light.size() - 1; ++i) {
        // 判断两个灯条是否符合条件，并且是否构成装甲板
        Armor obj_rect = boundingRect(light[i], light[i+1]);
        if (obj_rect.isValid()) {
            board.push_back(obj_rect);
        }
    }
}

void DetectArmor::drawResult() {
    // 绘制轮廓和装甲板
    cv::Mat con = src.clone();
    for (const auto& contour : contours_max) {
        cv::drawContours(con, contour, -1, cv::Scalar(0, 255, 0), 2);
    }

    // 绘制结果
    for (const auto& a : armor) {
        cv::Point2f pts[4];
        a.getBoundingRect().points(pts);
        for (int i = 0; i < 4; i++) {
            cv::line(con, pts[i], pts[(i + 1) % 4], cv::Scalar(255, 255, 255), 2);
        }
    }
    cv::imshow("Result", con);
}

void DetectArmor::ROIpics() {
    // ROI图片提取
    if (!board.empty()) {
        // 获取当前时间，并保存ROI图像
    }
}

void DetectArmor::lightPics() {
    // 提取灯条图片
}

void DetectArmor::isDigital() {
    // 识别数字
}

void DetectArmor::pnpexe() {
    // 执行PnP求解
}

void DetectArmor::kf_T() {
    // 使用卡尔曼滤波器
}

bool DetectArmor::isValidArmor(const Armor& a) {
    // 判断是否是有效的装甲板
    return true;
}

cv::RotatedRect DetectArmor::boundingRect(const Light& left, const Light& right) {
    // 计算装甲板的外接矩形
    return cv::RotatedRect();
}

void DetectArmor::exe(const cv::Mat& src) {
    // 执行整个过程
    this->setImage(src);
    this->findTarget();
    this->isDigital();
    this->drawResult();
    if (!armor.empty()) {
        this->pnpexe();
        this->kf_T();
    }
}
