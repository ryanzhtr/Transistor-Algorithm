#include "Tracker.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// Armor类的实现
Armor::Armor(ArmorSize size, int id, const cv::Mat& T, const cv::Mat& R_matrix)
    : size(size), id(id), T(T), R(R_matrix), dis(T.at<double>(2)) {}

// Tracker类的实现
Tracker::Tracker()
    : trackedArmor(nullptr), nowArmor(nullptr), trackerState(Status::DETECT),
      trackedId(-1), detectCount(0), lostCount(0), i(0) {
    window.resize(7);
    windowX.resize(7);
}

void Tracker::makeArmorList(const std::vector<Armor>& armorsDetected, 
                             const std::vector<cv::Mat>& armorsT, 
                             const std::vector<cv::Mat>& armorsR, 
                             double pitch) {
    armors.clear();
    if (!armorsDetected.empty()) {
        for (size_t i = 0; i < armorsDetected.size(); ++i) {
            // 假设 transformToWorld 函数已经实现
            cv::Mat T_w, R_w;
            transformToWorld(armorsT[i], armorsR[i], pitch, T_w, R_w);
            armors.push_back(Armor(armorsDetected[i].size, armorsDetected[i].id, T_w, R_w));
        }
    }
}

void Tracker::findNearestArmor() {
    if (armors.empty()) return;
    
    double minDistance = armors[0].dis;
    trackedArmor = &armors[0];
    
    for (auto& a : armors) {
        if (a.dis < minDistance) {
            trackedArmor = &a;
            minDistance = a.dis;
        }
    }
    trackedId = trackedArmor->id;
    nowArmor = trackedArmor;
}

bool Tracker::findIdArmor() {
    for (auto& a : armors) {
        if (a.id == trackedId) {
            nowArmor = &a;
            return true;
        }
    }
    return false;
}

void Tracker::updateTrackedArmor() {
    trackedArmor = nowArmor;
    trackedId = trackedArmor->id;
}

void Tracker::clearTrackedArmor() {
    trackedArmor = nullptr;
    trackedId = -1;
    nowArmor = nullptr;
}

bool Tracker::judgeIsSpinning() {
    double trackedArmorYaw = getYaw(trackedArmor->T, trackedArmor->R);
    double nowArmorYaw = getYaw(nowArmor->T, nowArmor->R);
    double deltaYaw = std::fabs(trackedArmorYaw - nowArmorYaw);
    
    if (deltaYaw > para["M_YAW_THRES"] && deltaYaw < para["K_YAW_THRES"]) {
        return true;
    }
    return false;
}

cv::Mat Tracker::getMeasurement() {
    cv::Mat z(4, 1, CV_64F);
    z.at<double>(0) = nowArmor->T.at<double>(0);
    z.at<double>(1) = nowArmor->T.at<double>(1);
    z.at<double>(2) = nowArmor->T.at<double>(2);
    z.at<double>(3) = getYaw(nowArmor->T, nowArmor->R);
    return z;
}

cv::Mat Tracker::getSpinningMeasurement() {
    double r = calculateRadius(*trackedArmor, *nowArmor);
    return calculateMeasurement(r);
}

void Tracker::getOutput(const cv::Mat& x) {
    if (!lastX.empty()) {
        if (std::fabs(x.at<double>(1) - lastX.at<double>(1)) > 0.2 || std::fabs(x.at<double>(2) - lastX.at<double>(2)) > 0.2) {
            lastX = x;
        }
    } else {
        lastX = x;
    }
}

cv::Mat Tracker::calculateMeasurement(double r) {
    // 假设 calculateMeasurement 函数实现逻辑
    // 返回计算后的测量值
}

cv::Mat Tracker::initKF_x() {
    cv::Mat x0(8, 1, CV_64F);
    x0.at<double>(0) = trackedArmor->T.at<double>(0);
    x0.at<double>(1) = trackedArmor->T.at<double>(1);
    x0.at<double>(2) = trackedArmor->T.at<double>(2);
    x0.at<double>(3) = getYaw(trackedArmor->T, trackedArmor->R);
    x0.at<double>(4) = 0;
    x0.at<double>(5) = 0;
    x0.at<double>(6) = 0;
    x0.at<double>(7) = 0;
    return x0;
}

double Tracker::calculateRadius(const Armor& formerArmor, const Armor& nowArmor) {
    double yaw0 = getYaw(formerArmor.T, formerArmor.R);
    double yaw = getYaw(nowArmor.T, nowArmor.R);
    double theta = std::fabs(yaw0 - yaw);
    
    cv::Mat formerArmorCenter = formerArmor.T.rowRange(0, 2);
    cv::Mat nowArmorCenter = nowArmor.T.rowRange(0, 2);
    double xy = cv::norm(nowArmorCenter - formerArmorCenter);
    
    return xy / (2.0 * std::sin(theta / 2.0));
}

void Tracker::updateTrackerState() {
    // 实现状态更新逻辑
    // 判断跟踪状态，更新卡尔曼滤波器等
}

void Tracker::updateFilter() {
    // 更新卡尔曼滤波器
}

void Tracker::main(const std::vector<Armor>& armorsDetected, 
                    const std::vector<cv::Mat>& armorsT, 
                    const std::vector<cv::Mat>& armorsR, 
                    double pitch) {
    i++;
    makeArmorList(armorsDetected, armorsT, armorsR, pitch);
    updateTrackerState();
    updateFilter();
}
