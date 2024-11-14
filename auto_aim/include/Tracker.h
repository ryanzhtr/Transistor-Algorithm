#ifndef TRACKER_H
#define TRACKER_H

#include <vector>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/video/tracking.hpp>
#include "KF.h"  // 假设 KF 类在这个文件中

// 装甲板大小的枚举
enum ArmorSize {
    SMALL = 0,
    BIG = 1
};

// 装甲板状态
enum class Status {
    DETECT = 1,
    TRACK = 2,
    TEMP_LOST = 3,
    TRACK_SPIN = 4
};

// Armor类表示单个装甲板的状态和位置
class Armor {
public:
    Armor(ArmorSize size, int id, const cv::Mat& T, const cv::Mat& R_matrix);
    
    cv::Mat T;   // 位置向量
    cv::Mat R;   // 旋转矩阵
    double dis;  // 距离
    ArmorSize size; // 装甲板大小
    int id;      // 装甲板ID
};

// Tracker类负责跟踪装甲板
class Tracker {
public:
    Tracker();

    void makeArmorList(const std::vector<Armor>& armorsDetected, 
                        const std::vector<cv::Mat>& armorsT, 
                        const std::vector<cv::Mat>& armorsR, 
                        double pitch);
    
    void updateTrackerState();
    void updateFilter();

    void main(const std::vector<Armor>& armorsDetected, 
              const std::vector<cv::Mat>& armorsT, 
              const std::vector<cv::Mat>& armorsR, 
              double pitch);
    
private:
    void findNearestArmor();
    bool findIdArmor();
    void updateTrackedArmor();
    void clearTrackedArmor();
    bool judgeIsSpinning();
    cv::Mat getMeasurement();
    cv::Mat getSpinningMeasurement();
    void getOutput(const cv::Mat& x);
    cv::Mat calculateMeasurement(double r);
    cv::Mat initKF_x();
    double calculateRadius(const Armor& formerArmor, const Armor& nowArmor);

    Armor* trackedArmor;
    Armor* nowArmor;
    Status trackerState;
    int trackedId;
    int detectCount;
    int lostCount;
    KF filter;  // 卡尔曼滤波器
    std::vector<Armor> armors;  // 装甲板列表
    std::vector<Armor> window;
    std::vector<double> windowX;
    cv::Mat lastX;
    int i;
};

#endif // TRACKER_H
