#include "Params.h"
#include <iostream>

using namespace std;

namespace br
{
    // // 相机参数初始化，您可以根据实际需求调整这些值
    // int CameraParam::device_type = 0;   // 设备类型（根据实际设备类型选择）
    // string CameraParam::sn = "12345678"; // 相机的序列号
    // string CameraParam::picture_path = "/path/to/pictures";  // 存储图片的路径
    // string CameraParam::video_path = "/path/to/videos";      // 存储视频的路径
    // int CameraParam::exposure_time = 100;   // 曝光时间（ms）
    // double CameraParam::gamma = 1.0;        // 伽马校正
    // double CameraParam::gain = 10.0;        // 相机增益
    // double CameraParam::fx = 1000.0;        // 相机焦距（X轴）
    // double CameraParam::fy = 1000.0;        // 相机焦距（Y轴）
    // double CameraParam::u0 = 640.0;         // 主点u0（图像中心X坐标）
    // double CameraParam::v0 = 480.0;         // 主点v0（图像中心Y坐标）
    // double CameraParam::k1 = 0.0;           // 相机畸变系数k1
    // double CameraParam::k2 = 0.0;           // 相机畸变系数k2
    // double CameraParam::k3 = 0.0;           // 相机畸变系数k3
    // double CameraParam::p1 = 0.0;           // 畸变系数p1
    // double CameraParam::p2 = 0.0;           // 畸变系数p2

    // // 自动曝光和自动增益设置（根据需求选择启用或禁用）
    // bool AutoExposureGain::is_use_auto_exposure = false; // 是否启用自动曝光
    // bool AutoExposureGain::is_use_auto_gain = false;     // 是否启用自动增益
    // int AutoExposureGain::auto_exposure_min = 10;       // 自动曝光最小值
    // int AutoExposureGain::auto_exposure_max = 1000;      // 自动曝光最大值
    // int AutoExposureGain::auto_gain_min = 1;             // 自动增益最小值
    // int AutoExposureGain::auto_gain_max = 20;            // 自动增益最大值

    // // 白平衡设置
    // bool WhiteBalanceParam::is_auto_balance = false; // 是否启用自动白平衡
    // float WhiteBalanceParam::white_balance_ratio_r = 1.0f;  // 红色通道白平衡系数
    // float WhiteBalanceParam::white_balance_ratio_b = 1.0f;  // 蓝色通道白平衡系数
    // float WhiteBalanceParam::white_balance_ratio_g = 1.0f;  // 绿色通道白平衡系数

    // // 灯条相关设置
    // // 您可以在这里调整灯条的识别参数，如亮度、色彩范围等
    // int LightbarParam::min_brightness = 100;  // 灯条最小亮度阈值
    // int LightbarParam::max_brightness = 255;  // 灯条最大亮度阈值
    // int LightbarParam::min_length = 20;       // 灯条最小长度（像素）
    // int LightbarParam::max_length = 1000;     // 灯条最大长度（像素）
    // int LightbarParam::color_threshold = 50;  // 灯条颜色差异阈值

    int DetectorParam::thresh = 128;  // 二值化阈值（举例值）
    BuffParam DetectorParam::buff_params;

    // ArmorDetectParam 类的变量定义
    float ArmorDetectParam::angle_diff_max = 30.0f;  // 灯条角度差最大值
    float ArmorDetectParam::lightbar_ratio_max = 3.0f; // 灯条长宽比最大值
    float ArmorDetectParam::lightbar_ratio_min = 0.5f; // 灯条长宽比最小值
    float ArmorDetectParam::lightbar_area_max = 1000.0f; // 灯条面积最大值
    float ArmorDetectParam::lightbar_area_min = 100.0f;  // 灯条面积最小值
    float ArmorDetectParam::armor_ratio_max = 2.0f; // 装甲板长宽比最大值
    float ArmorDetectParam::armor_ratio_min = 0.5f; // 装甲板长宽比最小值
    float ArmorDetectParam::lightbar_center_diff = 20.0f; // 两灯条中心像素差最大值
    float ArmorDetectParam::lightbar_angle_min = 10.0f;   // 灯条角度最小值
    float ArmorDetectParam::lightbar_angle_max = 60.0f;   // 灯条角度最大值
    float ArmorDetectParam::rectangle_likely = 0.7f;  // 矩形相似度
    float ArmorDetectParam::lightbar_length_ratio = 0.5f; // 两灯条长度比例

    // debug参数
    bool ArmorDetectParam::show_thresh = true;        // 是否显示二值化图像
    bool ArmorDetectParam::show_lightbar_info = true; // 控制台显示灯条信息
}