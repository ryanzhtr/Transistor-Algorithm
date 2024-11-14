#ifndef PNPSOLVER_H
#define PNPSOLVER_H

#include <opencv2/core.hpp>
#include <vector>

namespace PnPsolver {

    extern const double small_armor_length;
    extern const double small_armor_width;
    extern const double big_armor_length;
    extern const double big_armor_width;

    extern const cv::Mat camera_matrix;
    extern const cv::Mat dist_coeffs;

    enum ArmorSize {
        SMALL = 0,
        BIG = 1
    };

    struct Armor {
        std::vector<cv::Point2f> points;  // 4个点坐标
        ArmorSize size;
    };

    // SolvePnP的函数声明
    bool solvePnP(const std::vector<Armor>& armor, std::vector<cv::Mat>& R, std::vector<cv::Mat>& T);

}

#endif // PNPSOLVER_H
