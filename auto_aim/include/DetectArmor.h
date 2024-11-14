#ifndef DETECTARMOR_H
#define DETECTARMOR_H

#include <opencv2/opencv.hpp>
#include <torch/torch.h>
#include <vector>
#include <string>
#include "Light.h"  // 假设Light.h与Armor.h已经存在
#include "Armor.h"  // 包含Armor类定义
#include "KalmanFilter.h"  // 假设KalmanFilter.h存在
#include "LeNet.h"  // 假设LeNet.h存在

class DetectArmor {
public:
    enum Color { RED = 2, BLUE = 1, NO = 0 };
    enum Size { SMALL = 0, BIG = 1 };

    DetectArmor();
    ~DetectArmor();

    void setEnemyColor(Color color);
    void setImage(const cv::Mat& img);
    void findTarget();
    void drawResult();
    void ROIpics();
    void lightPics();
    void isDigital();
    void pnpexe();
    void kf_T();
    void exe(const cv::Mat& src);

private:
    // 成员变量
    std::vector<Light> light;
    std::vector<Armor> armor;
    std::vector<Armor> board;
    cv::Mat src;
    
    LeNet model;
    LeNet binary;
    torch::jit::script::Module module;
    torch::jit::script::Module binary_module;
    
    torch::Tensor R;
    torch::Tensor T;
    
    KalmanFilter Filter;

    float hei, dep, bias;
    Color enemy_color;
    int detected;
    std::vector<std::vector<cv::Point>> contours_max;
    cv::Mat ppdForDetect;
    cv::Mat ppdForROI;
    
    // 辅助函数
    void preprocessImage();
    void findContours();
    bool isValidArmor(const Armor& armor);
    cv::RotatedRect boundingRect(const Light& left, const Light& right);
    bool containLight(const Light& light1, const Light& light2);
    void applyKalmanFilter();
};

#endif // DETECTARMOR_H
