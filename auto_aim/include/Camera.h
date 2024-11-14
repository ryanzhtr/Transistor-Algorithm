#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <unistd.h>
#include "MvCameraControl.h"

extern bool g_bExit;
extern cv::Mat g_image;
extern pthread_mutex_t g_mutex;

class Camera {
public:
    void* handle;
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    unsigned int nPayloadSize;

    // 构造函数：初始化摄像头
    Camera(const std::string& deviceIp, const std::string& netIp);
    
    // 析构函数：释放资源
    ~Camera();

    // IP地址解析函数
    static void parseIp(const std::string& ip, unsigned int& parsedIp);

    // 摄像头取流线程
    static void* workThread(void* pUser);
};

#endif // CAMERA_H
