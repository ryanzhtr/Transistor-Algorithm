#include "PnPSolver.h"
#include <opencv2/calib3d.hpp>

namespace PnPsolver {

    // 常量初始化
    const double small_armor_length = 136;   // 小装甲板的长度
    const double small_armor_width = 57;     // 小装甲板的宽度
    const double big_armor_length = 224.5;  // 大装甲板的长度
    const double big_armor_width = 57;      // 大装甲板的宽度

    const cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) <<
        1310.422473, 0, 652.1782683,
        0, 1310.496146, 541.894165,
        0, 0, 1);

    const cv::Mat dist_coeffs = (cv::Mat_<double>(1, 5) <<
        -0.0807085646490320, 0.160324172041083, -0.0505325187663191, 0, 0);

    bool solvePnP(const std::vector<Armor>& armor, std::vector<cv::Mat>& R, std::vector<cv::Mat>& T) {
        // 物体点数据（对应小装甲板和大装甲板）
        cv::Mat s_object_points = (cv::Mat_<double>(4, 3) <<
            small_armor_width / 2.0 / 1000.0, -small_armor_length / 2.0 / 1000.0, 0,
            -small_armor_width / 2.0 / 1000.0, -small_armor_length / 2.0 / 1000.0, 0,
            -small_armor_width / 2.0 / 1000.0, small_armor_length / 2.0 / 1000.0, 0,
            small_armor_width / 2.0 / 1000.0, small_armor_length / 2.0 / 1000.0, 0);

        cv::Mat b_object_points = (cv::Mat_<double>(4, 3) <<
            big_armor_width / 2.0 / 1000.0, -big_armor_length / 2.0 / 1000.0, 0,
            -big_armor_width / 2.0 / 1000.0, -big_armor_length / 2.0 / 1000.0, 0,
            -big_armor_width / 2.0 / 1000.0, big_armor_length / 2.0 / 1000.0, 0,
            big_armor_width / 2.0 / 1000.0, big_armor_length / 2.0 / 1000.0, 0);

        // 对每个装甲板调用 cv::solvePnP
        bool suc = false;
        for (size_t i = 0; i < armor.size(); ++i) {
            cv::Mat image_points = cv::Mat(armor[i].points);
            image_points.convertTo(image_points, CV_64F);

            if (armor[i].size == ArmorSize::SMALL) {
                cv::Mat R_temp, T_temp;
                suc = cv::solvePnP(s_object_points, image_points, camera_matrix, dist_coeffs, R_temp, T_temp);
                R.push_back(R_temp);
                T.push_back(T_temp);
            } else {
                cv::Mat R_temp, T_temp;
                suc = cv::solvePnP(b_object_points, image_points, camera_matrix, dist_coeffs, R_temp, T_temp);
                R.push_back(R_temp);
                T.push_back(T_temp);
            }
        }

        return suc;
    }

}
