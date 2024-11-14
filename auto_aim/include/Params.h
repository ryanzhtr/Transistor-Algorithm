#ifndef PARAMS_H
#define PARAMS_H

struct Params {
    // 灯条检测参数
    int min_light_height = 8;
    int light_slope_offset = 30;
    int light_min_area = 10;
    float max_light_wh_ratio = 10;
    float min_light_wh_ratio = 0.1;
    float light_max_tilt_angle = 60;
    int min_light_delta_x = 28;
    float min_light_dx_ratio = 0.8;
    float max_light_dy_ratio = 1;
    float max_light_delta_angle = 30;
    int near_face_v = 600;
    float max_lr_rate = 0.7;
    float max_wh_ratio = 6;
    float min_wh_ratio = 0.5;
    float small_armor_wh_threshold = 3.6;
    int bin_cls_thres = 166;
    int target_max_angle = 20;
    float goodToTotalRatio = 1;
    int matchDistThre = 50;
    float wh_ratio_threshold = 3.2;
    float wh_ratio_max = 4.5;
    int M_YAW_THRES = 31416;  // 5 degrees in radians (approx)
    float K_YAW_THRES = 0.7;
    int MAX_DETECT_CNT = 2;
    int MAX_LOST_CNT = 3;
};

#endif // PARAMS_H
