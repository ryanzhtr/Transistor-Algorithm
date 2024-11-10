#ifndef AUTOAIM_PARAMS_H
#define AUTOAIM_PARAMS_H

#include <string>
#include "opencv2/opencv.hpp"

using namespace std;

namespace br
{
    class CameraParam
    {
    public:
        static string sn;           // 设备SN号
        static string video_path;   // 测试视频位置
        static string picture_path; // 测试图片位置
        static int exposure_time;   // 曝光时间
        static double gain;         // 增益
        static double fx;           // 相机内参
        static double fy;
        static double u0;
        static double v0;
    };

    class BuffParam
    {
    public:
        static int binary_thresh;         // 灰度图二值化阈值
        static int color_thresh;          // 颜色通道相减阈值
        static int armor_size_min;        // 轮廓点数最小
        static int armor_size_max;        // 轮廓点数最大
        static float armor_ratio_min; // 长宽比最小
        static float armor_ratio_max; // 长宽比最大
    };

    class DetectorParam
    {
    public:
        static int thresh;            // 二值化阈值
        static BuffParam buff_params;
    };

    class ArmorDetectParam
    {
    public:
        static float angle_diff_max;     // 灯条角度差
        static float lightbar_ratio_max; // 灯条长宽比
        static float lightbar_ratio_min;
        static float lightbar_area_max; // 灯条面积
        static float lightbar_area_min;
        static float armor_ratio_max; // 装甲板长宽比
        static float armor_ratio_min;
        static float lightbar_center_diff; // 两灯条中心像素差
        static float lightbar_angle_min;   // 灯条角度
        static float lightbar_angle_max;
        static float rectangle_likely;      // 多像矩形
        static float lightbar_length_ratio; // 两灯条长度比例

        // debug参数
        static bool show_thresh;        // 是否显示二值化图像
        static bool show_lightbar_info; // 控制台显示灯条信息
    };
}

#endif // AUTOAIM_PARAMS_H
